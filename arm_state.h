#ifndef STATE_H
#define STATE_H

//////////////
// INCLUDES
//////////////

// C Libraries
#include <pthread.h>
#include "time.h"
#include "vx/vx.h"
#include <stdlib.h>

// EECS 467 Libraries
#include "common/getopt.h"

// LCM
#include <lcm/lcm.h>

// Local Includes
#include "body.h"
#include "rexarm.h"
#include "config_space.h"

//////////////
// CONSTANTS
//////////////
#define NUM_LAYERS 2

#define ARM_STATUS_CHANNEL "ARM_STATUS"
#define ARM_COMMAND_CHANNEL "ARM_COMMAND"
#define SKELETON_DATA_CHANNEL "KA_SKELETON"

//////////////
// STRUCTS
//////////////

typedef struct layer_data_t layer_data_t;
typedef struct state_t state_t;
typedef struct getopt_options_t getopt_options_t;


struct getopt_options_t {
    int verbose, no_video, limitKBs, autoCamera, mouseGuidance;
    double decimate;
};

struct layer_data_t {
    int enable;
    const char* name;
    vx_world_t *world;
    vx_layer_t *layer;
    float position[4];

    int (*init)(state_t *state, layer_data_t *layerData);
    int (*displayInit)(state_t *state, layer_data_t *layerData);
    int (*render)(state_t *state, layer_data_t *layerData);
    int (*destroy)(state_t *state, layer_data_t *layerData);
};

enum FSM_state_t {
	FSM_NONE,
	FSM_ARM,
	FSM_WRIST,
	FSM_GRIP,
	FSM_ROT_LEFT,
	FSM_ROT_RIGHT
};

struct state_t {
    getopt_options_t  getopt_options;
    vx_application_t app;
    vx_event_handler_t veh;

    volatile int running;
    int displayStarted, displayFinished;

    getopt_t * gopt;	

    lcm_t * lcm;
    pthread_mutex_t lcm_mutex;

    pthread_t lcm_handle_thread;
    pthread_t arm_commander_thread;
	pthread_t fsm_thread;
    pthread_mutex_t layer_mutex;
    pthread_mutex_t running_mutex;
    pthread_t gui_thread;

    int layerCount;
    layer_data_t layers[NUM_LAYERS];

    zhash_t *layer_map; // <display, layer>

    pthread_t dmon_thread;

    double current_servo_angles[NUM_SERVOS];
    double target_servo_angles[NUM_SERVOS];
    double gui_servo_angles[NUM_SERVOS];
    int update_arm_cont, update_arm;

    Body *body;
    RexArm *arm;
    ConfigSpace cfs;

	FSM_state_t FSM_state;
	FSM_state_t FSM_next_state;
	bool close_gripper;
	double last_gripper_angle;
};


void* arm_commander(void *data);
#endif
