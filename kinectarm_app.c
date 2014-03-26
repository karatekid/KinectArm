// General Includes
#include <sys/time.h>
#include <signal.h>

// LCM
#include "lcmtypes/dynamixel_command_list_t.h"
#include "lcmtypes/dynamixel_command_t.h"
#include "lcmtypes/dynamixel_status_list_t.h"
#include "lcmtypes/dynamixel_status_t.h"

// Local Includes
#include "state.h"
#include "eecs467_util.h"
#include "gui.h"
#include "body.h"

static int64_t utime_now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t) tv.tv_sec * 1000000 + tv.tv_usec;
}

static state_t * global_state;
static void terminal_signal_handler(int signum)
{
	switch (signum)
	{
		case SIGINT:
		case SIGQUIT:
			pthread_mutex_lock(&global_state->running_mutex);
			//printf("setting running to 0\n");
			global_state->running = 0;
			pthread_mutex_unlock(&global_state->running_mutex);
			break;
		default:
			break;
	}
}

void* lcm_handle_loop(void *data) {
	state_t *state = data;

	// ..._subscribe(...)

	while (state->running) {
		// Set up the LCM file descriptor for waiting. This lets us monitor it
		// until somethign is "ready" to happen. In this case, we are ready to
		// receive a message.
		lcm_handle(state->lcm);
	}

	//clean up
	// ..._unsubscribe(...)

	return NULL;
}

void* arm_commander(void *data) {
	int hz = 30;
	state_t *state = data;

	dynamixel_command_list_t cmds;
    cmds.len = NUM_SERVOS;
    cmds.commands = malloc(sizeof(dynamixel_command_t)*NUM_SERVOS);

    while (state->running) {
    	if (state->update_arm) {
    		state->update_arm = 0;
		    for (int id = 0; id < NUM_SERVOS; id++) {
				cmds.commands[id].utime = utime_now();
				cmds.commands[id].position_radians = state->target_servo_angles[id];
				cmds.commands[id].speed = 0.5;
				cmds.commands[id].max_torque = 0.7;
		    }

		    pthread_mutex_lock(&state->lcm_mutex);
		    dynamixel_command_list_t_publish(state->lcm, state->arm_command_channel, &cmds);
		    pthread_mutex_unlock(&state->lcm_mutex);
	    }
	    usleep(1000000/hz);
	}

	free(cmds.commands);

	return NULL;
}

int main(int argc, char ** argv)
{
	eecs467_init(argc, argv);

	state_t * state = calloc(1, sizeof(state_t));
	global_state = state;
	state->gopt = getopt_create();
	state->app.display_finished = display_finished;
	state->app.display_started = display_started;
	state->app.impl = state;
	state->update_arm_cont = 0;
	state->update_arm = 0;
	state->arm_command_channel = "ARM_COMMAND";

	state->running = 1;

	lcm_t * lcm = lcm_create (NULL);
	state->lcm = lcm;

	signal(SIGINT, terminal_signal_handler);

	pthread_mutex_init(&state->layer_mutex, NULL);
	pthread_mutex_init(&state->lcm_mutex, NULL);
	pthread_mutex_init(&state->running_mutex, NULL);

	state->layer_map = zhash_create(sizeof(vx_display_t*), sizeof(vx_layer_t*), zhash_uint64_hash, zhash_uint64_equals);

	getopt_add_bool(state->gopt, 'h', "help", 0, "Show this help");
	//getopt_add_bool(state->gopt, 'v', "verbose", 0, "Show extra debugging output");
	//getopt_add_int (state->gopt, 'l', "limitKBs", "-1", "Remote display bandwidth limit. < 0: unlimited.");
	//getopt_add_double (state->gopt, 'd', "decimate", "0", "Decimate image by this amount before showing in vx");

	if (!getopt_parse(state->gopt, argc, argv, 0) ||
		getopt_get_bool(state->gopt,"help")) {
		getopt_do_usage(state->gopt);
		exit(-1);
	}

	pthread_create(&state->lcm_handle_thread, NULL, lcm_handle_loop, state);
	pthread_create(&state->gui_thread,  NULL, gui_create, state);
	pthread_create(&state->arm_commander_thread, NULL, arm_commander, state);
	pthread_join(state->gui_thread, NULL);

	// clean up
	vx_global_destroy();
    getopt_destroy(state->gopt);

    printf("Exited Cleanly!\n");
    return 0;
}
