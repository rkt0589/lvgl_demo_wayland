CSRCS += win32drv.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_drivers/win32drv 
VPATH += :$(LVGL_DIR)/lv_drivers/win32drv

CFLAGS += "-I$(LVGL_DIR)/lv_drivers/win32drv"