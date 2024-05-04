CXX = g++
CXX_FLAGS = -std=c++20 -fno-rtti

GENERATOR_DEPS = ${HALIDE_ROOT}/tools/GenGen.cpp
GENERATOR_OUTPUTS = o,h
INCLUDES = -I${HALIDE_ROOT}/include -I${HALIDE_ROOT}/tools -Iinclude -Ibin
LIBS = -L${HALIDE_ROOT}/lib 
LIB_FLAGS = -lHalide -lpthread -ldl -lz -ltinfo
IMAGE_IO_FLAGS = -ljpeg `libpng-config --cflags --ldflags`

TARGET=host

ifndef AUTOSCHEDULER
	AUTOSCHEDULER=false
endif
ifeq ($(AUTO_SCHEDULE), true)
	ifndef AUTO_SCHEDULER
		AUTO_SCHEDULER=mullapudi2016
	endif
	AUTO_SCHEDULER_PARS=auto_schedule=true -p $(HALIDE_ROOT)/lib/libautoschedule_$(AUTO_SCHEDULER).so
	ifdef MACHINE_PARAMS
		AUTO_SCHEDULER_PARS+=machine_params=$(MACHINE_PARAMS)
	endif
endif
GPARS=
ifdef VERSION
	GPARS=version=$(VERSION)
endif

ifndef PATH_IN
	PATH_IN=../inputs/
endif

ifndef OUT_PREFIX
	OUT_PREFIX=outputs/grayscale
endif


all: test

clean:
	@rm -rf bin outputs

	
bin/rgb2gray.generator: src/registration/HalideRGB2Gray.cpp
	@mkdir -p $(@D)
	@$(CXX) $^ $(GENERATOR_DEPS) $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) -o $@

bin/rgb2gray.o: bin/rgb2gray.generator
	@$^ -e $(GENERATOR_OUTPUTS) -o $(@D) -f rgb2gray -g rgb2gray target=$(TARGET) autoscheduler=Mullapudi2016 -p ${HALIDE_ROOT}/lib/libautoschedule_mullapudi2016.so

bin/main: src/main.cpp bin/rgb2gray.o
	@$(CXX) $^ $(CXX_FLAGS) $(INCLUDES) $(LIBS) $(LIB_FLAGS) $(IMAGE_IO_FLAGS) -o $@

test: bin/main
	@mkdir -p outputs
	@for i in `find $(PATH_IN) -type f -name "*.jpg"`; do $^ $$i $(OUT_PREFIX)_`basename $$i`; done
	#@pytest

.PHONY: all clean