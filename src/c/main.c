#include "pebble.h"
#include "pebble_fonts.h"
#include "main.h"

static Window *s_main_window;
static Layer *s_background1_layer;
static Layer *s_background2_layer;

static void background1_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(s_background1_layer);

  // Draw the black background
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);

  // Draw the white rectangle with round corners
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_width(ctx, 0);
  graphics_fill_rect(ctx, bounds, 12, GCornersAll);
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Properly create a full-screen Layer
  s_background1_layer = layer_create(bounds);
  s_background2_layer = layer_create(bounds);

  // Assign the custom drawing procedure
  layer_set_update_proc(s_background1_layer, background1_layer_update_proc);

  // Redraw this as soon as possible
  layer_mark_dirty(s_background1_layer);

  // Add to the Window
  layer_add_child(window_layer, s_background1_layer);
  layer_add_child(window_layer, s_background2_layer);
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_background1_layer);
  layer_destroy(s_background2_layer);
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
