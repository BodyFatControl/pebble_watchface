#include "pebble.h"
#include "pebble_fonts.h"
#include "main.h"

static Window *s_main_window;
static GBitmap *s_bitmap;
static BitmapLayer *s_background_layer;
static RotBitmapLayer *s_hours_hand_layer;
static RotBitmapLayer *s_minutes_hand_layer;

static void handleTick(struct tm *t, TimeUnits units_changed) {
  GRect rectangle;
  int32_t minute_angle = t->tm_sec * TRIG_MAX_ANGLE / 60;
  int32_t hour_angle = ((t->tm_min%12)*60 + t->tm_sec) * TRIG_MAX_ANGLE / (12 * 60);



//  APP_LOG(APP_LOG_LEVEL_DEBUG, "rectangle.size.h: %d", rectangle.size.h);
//  APP_LOG(APP_LOG_LEVEL_DEBUG, "rectangle.size.w: %d", rectangle.size.w);
//  APP_LOG(APP_LOG_LEVEL_DEBUG, "rectangle.origin.x: %d", rectangle.origin.x);
//  APP_LOG(APP_LOG_LEVEL_DEBUG, "rectangle.origin.y: %d", rectangle.origin.y);
//
//  rectangle = layer_get_frame((Layer *)s_minutes_hand_layer);
//  rectangle.origin.x = (PBL_DISPLAY_WIDTH_HALF - rectangle.size.w/2);
//  rectangle.origin.y = PBL_DISPLAY_HEIGHT_HALF - 68 + 6;
//
//  rectangle.size.w = rectangle.size.w + rectangle.size.w;
//  rectangle.size.h = rectangle.size.h + rectangle.size.h;
//
//  layer_set_frame((Layer *)s_minutes_hand_layer, rectangle);

  rot_bitmap_layer_set_angle(s_minutes_hand_layer, minute_angle);

//  rectangle.origin.x = PBL_DISPLAY_WIDTH_HALF - rectangle.size.w/2 + 56 * cos_lookup((minuteAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
//  rectangle.origin.y = PBL_DISPLAY_HEIGHT_HALF - rectangle.size.h/2 + 56 * sin_lookup((minuteAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
//  layer_set_frame((Layer *)minuteHandLayer, r);
//  rot_bitmap_layer_set_angle(minuteHandLayer, minuteAngle);
//
//  rectangle = layer_get_frame((Layer *)hourHandLayer);
//  rectangle.origin.x = 72 - rectangle.size.w/2 + 57 * cos_lookup((hourAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
//  rectangle.origin.y = 84 - rectangle.size.h/2 + 57 * sin_lookup((hourAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
//  layer_set_frame((Layer *)hourHandLayer, r);
//  rot_bitmap_layer_set_angle(hourHandLayer, hourAngle);
}

static void push_background (Window *window) {
  time_t t = time(NULL);

  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Prepare background image layer
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND);
  s_background_layer = bitmap_layer_create(GRect(0, 0, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT));
  //bitmap_layer_set_compositing_mode(s_background_layer, GCompOpAssign);
  bitmap_layer_set_bitmap(s_background_layer, s_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));

  // Prepare  minutes hand layer
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MINUTES_HAND);
  s_minutes_hand_layer = rot_bitmap_layer_create(s_bitmap);
  rot_bitmap_set_compositing_mode(s_minutes_hand_layer, GCompOpSet);

  GRect rectangle = layer_get_frame((Layer *)s_minutes_hand_layer);
  rectangle.origin.x = (PBL_DISPLAY_WIDTH_HALF - rectangle.size.w/2);
  rectangle.origin.y = PBL_DISPLAY_HEIGHT_HALF - 68 + 6;
  layer_set_frame((Layer *)s_minutes_hand_layer, rectangle);

  layer_add_child(window_get_root_layer(window), (Layer *)s_minutes_hand_layer);

  // Prepare  hour hand layer
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_HOURS_HAND);
  s_hours_hand_layer = rot_bitmap_layer_create(s_bitmap);
  rot_bitmap_set_compositing_mode(s_hours_hand_layer, GCompOpSet);
//  layer_add_child(window_get_root_layer(window), (Layer *)s_hours_hand_layer);

  // Draw the handles now
  handleTick(localtime(&t), SECOND_UNIT|MINUTE_UNIT|HOUR_UNIT);

  tick_timer_service_subscribe(SECOND_UNIT, handleTick);
}

static void main_window_load(Window *window) {
  // Draw the background
  push_background(window);
}

static void main_window_unload(Window *window) {
  gbitmap_destroy(s_bitmap);
  bitmap_layer_destroy(s_background_layer);
  rot_bitmap_layer_destroy(s_hours_hand_layer);
  rot_bitmap_layer_destroy(s_minutes_hand_layer);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
