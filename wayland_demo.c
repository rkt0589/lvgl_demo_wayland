
#include "lvgl/lvgl.h"
#include "lv_drivers/wayland/wayland.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/mousewheel.h"
#include "lv_drivers/indev/keyboard.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define DISP_BUF_SIZE (LV_HOR_RES_MAX * LV_VER_RES_MAX)

lv_obj_t *screen;               
lv_obj_t *screen_cont0;
lv_obj_t *screen_btn0;
lv_obj_t *screen_lbl_hello_world;

/* Button event handler */
static void screen_btn0event_handler(lv_obj_t *obj, lv_event_t event)
{
  switch (event)
  {
  case LV_EVENT_CLICKED:
  {
    lv_obj_set_style_local_bg_color(screen_cont0, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0xbf, 0xff));
    lv_label_set_text(screen_lbl_hello_world, "Welcome to Lvgl Wayland Basic Demo");
  }
  break;
  default:
    break;
  }
}

/* Baisc Ui showing one button and one container */
void setup_ui()
{
  screen = lv_obj_create(NULL, NULL);
  screen_cont0 = lv_cont_create(screen, NULL);
  screen_btn0 = lv_btn_create(screen, NULL);
  lv_obj_set_pos(screen_btn0, 200, 159);
  lv_obj_set_size(screen_btn0, 400, 50);
  screen_lbl_hello_world = lv_label_create(screen_btn0, NULL);
  lv_label_set_text(screen_lbl_hello_world, "Click");
  lv_obj_set_style_local_text_color(screen_lbl_hello_world, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0xbf, 0xff));
  lv_obj_set_event_cb(screen_btn0, screen_btn0event_handler);

  //Write style LV_CONT_PART_MAIN for screen_cont0
  static lv_style_t style_screen_cont0;
  lv_style_set_radius(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_style_set_bg_color(&style_screen_cont0, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
  lv_style_set_bg_grad_color(&style_screen_cont0, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x3d, 0x3d));
  lv_style_set_bg_grad_dir(&style_screen_cont0, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
  lv_style_set_bg_opa(&style_screen_cont0, LV_STATE_DEFAULT, 248);
  lv_style_set_border_color(&style_screen_cont0, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
  lv_style_set_border_width(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_style_set_border_opa(&style_screen_cont0, LV_STATE_DEFAULT, 255);
  lv_style_set_pad_left(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_right(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_top(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_bottom(&style_screen_cont0, LV_STATE_DEFAULT, 0);
  lv_obj_add_style(screen_cont0, LV_CONT_PART_MAIN, &style_screen_cont0);
  lv_obj_set_pos(screen_cont0, 0, 0);
  lv_obj_set_size(screen_cont0, 800, 480);
  lv_obj_set_click(screen_cont0, false);
  lv_cont_set_layout(screen_cont0, LV_LAYOUT_OFF);
  lv_cont_set_fit(screen_cont0, LV_FIT_NONE);
  lv_scr_load(screen);
}


int main(int argc, char **argv)
{
  /*LittlevGL init*/
  lv_init();

  /*wayland device init*/
  wayland_init();

  /*A small buffer for LittlevGL to draw the screen's content*/
  static lv_color_t buf[DISP_BUF_SIZE];

  /*Initialize a descriptor for the buffer*/
  static lv_disp_buf_t disp_buf;
  lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

  /*Initialize and register a display driver*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.buffer = &disp_buf;
  disp_drv.flush_cb = wayland_flush;
  lv_disp_drv_register(&disp_drv);

  /* Initialize and register a mouse driver */
  lv_indev_drv_t indev_drv_mouse;
  lv_indev_drv_init(&indev_drv_mouse);
  indev_drv_mouse.type = LV_INDEV_TYPE_POINTER;
  indev_drv_mouse.read_cb = wayland_pointer_read;
  lv_indev_drv_register(&indev_drv_mouse);

  /* Setup ui here */
  setup_ui();
  
  /*Handle LitlevGL tasks (tickless mode)*/
  while (1)
  {
    lv_task_handler();
    usleep(5000);
  }
  return 0;
}

uint32_t custom_tick_get(void)
{
  static uint64_t start_ms = 0;
  if (start_ms == 0)
  {
    struct timeval tv_start;
    gettimeofday(&tv_start, NULL);
    start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
  }
  struct timeval tv_now;
  gettimeofday(&tv_now, NULL);
  uint64_t now_ms;
  now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

  uint32_t time_ms = now_ms - start_ms;
  return time_ms;
}

