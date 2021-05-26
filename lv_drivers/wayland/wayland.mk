CSRCS += wayland.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_drivers/wayland 
VPATH += :$(LVGL_DIR)/lv_drivers/wayland

CFLAGS += "-I$(LVGL_DIR)/lv_drivers/wayland"