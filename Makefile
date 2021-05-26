#
# Makefile
#
#CC = ${CC} # exported from terminal from toolchain
APP_NAME = wayland_demo
makefile_name := $(abspath $(lastword $(MAKEFILE_LIST)))
makefile_path := $(strip $(patsubst %/,% , $(dir $(makefile_name))))
PRJ_DIR := $(makefile_path)
LVGL_DIR ?= $(PRJ_DIR)
LVGL_DIR_NAME ?= lvgl
BUILD_DIR := build/
OBJ_DIR := $(BUILD_DIR)temp/
BIN_DIR := $(BUILD_DIR)binary/

CFLAGS = -Wall -Wshadow -Wundef -Wmaybe-uninitialized
CFLAGS += -O3 -g3 -I./ -I$(LVGL_DIR)/ $(DEFINES) $(WARNINGS) $(OPTIMIZATION) -I$(makefile_path)
LDFLAGS += -lm -lwayland-client -lxkbcommon -lpthread
BIN = $(APP_NAME)

#LIBRARIES
-include $(LVGL_DIR)/lvgl/lvgl.mk
-include $(PRJ_DIR)/lv_drivers/lv_drivers.mk

MAINSRC = $(APP_NAME).c

DEPPATH += --dep-path $(makefile_path)/
VPATH += :$(makefile_path)/
CFLAGS += "-I$(makefile_path)/"
MAINOBJ = $(addprefix $(OBJ_DIR),$(MAINSRC:.c=$(OBJEXT)))

OBJEXT ?= .o

AOBJS = $(addprefix $(OBJ_DIR),$(ASRCS:.S=$(OBJEXT)))
COBJS = $(addprefix $(OBJ_DIR),$(CSRCS:.c=$(OBJEXT)))
DEPS = $(addprefix $(OBJ_DIR),$(CSRCS:.c=.d))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

all: env default

env:
	@if [ ! -d "build/binary" ]; then mkdir -p build/binary; fi
	@if [ ! -d "build/temp" ]; then mkdir -p build/temp; fi

$(OBJ_DIR)%.o: %.c
	@echo "Compiling $<"
	@$(CC)  $(CFLAGS) -c $< -o $@

default: $(AOBJS) $(COBJS) $(MAINOBJ)
	@echo "Linking binary $(BIN)"
	$(CC) -o $(BIN_DIR)$(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)

clean: 
	rm -rf build
	