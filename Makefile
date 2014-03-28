include ../common.mk

CFLAGS = $(CFLAGS_STD) $(CFLAGS_COMMON) $(CFLAGS_VX) $(CFLAGS_GTK) $(CFLAGS_LCMTYPES) $(CFLAGS_LCM) $(CFLAGS_VX) -fPIC -O2
LDFLAGS =  $(LDFLAGS_VX_GTK) $(LDFLAGS_VX) $(LDFLAGS_GTK) $(LDFLAGS_IMAGESOURCE) $(LDFLAGS_COMMON) $(LDFLAGS_LCMTYPES) $(LDFLAGS_LCM) $(LDFLAGS_STD) -lfreenect -L /usr/local/lib64/
CXXFLAGS_STD := -g -D FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D REENTRANT \
	-Wall -Wno-unused-parameter -pthread -Wno-write-strings -Wno-error=switch
CFLAGS_CXX = $(CXXFLAGS_STD) $(CFLAGS_COMMON) $(CFLAGS_VX) $(CFLAGS_GTK) -fPIC -O2 -std=c++0x

BINARIES = ../../bin/kinectarm_app ../../bin/kinectvision_app
LIB = ../../lib

all: $(BINARIES)

arm: ../../bin/kinectarm_app

vision: ../../bin/kinectvision_app

../../bin/kinectarm_app: kinectarm_app.o arm_gui.o body.o pid_ctrl.o eecs467_util.o
	@echo "\t$@"
	@$(CC) -o $@ $^ $(LDFLAGS)

../../bin/kinectvision_app: kinectvision_app.o vision_gui.o disjoint.o blob_detection.o body.o\
	pixel.o eecs467_util.o kinect_handle.o image.o 
	@echo "\t$@"
	@$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	@rm -f *.o *~ *.a
	@rm -f $(BINARIES)
