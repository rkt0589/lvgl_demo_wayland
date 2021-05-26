CSRCS += gtkdrv.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_drivers/gtkdrv 
VPATH += :$(LVGL_DIR)/lv_drivers/gtkdrv

CFLAGS += "-I$(LVGL_DIR)/lv_drivers/gtkdrv"