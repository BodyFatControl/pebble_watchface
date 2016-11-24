#include "pebble.h"
#include "pebble_fonts.h"
#include "main.h"

static Window *s_main_window;
static Layer *s_background1_layer;
static Layer *s_background2_layer;
static TextLayer *s_one_text_layer;
static TextLayer *s_two_text_layer;
static TextLayer *s_three_text_layer;

static void background1_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(s_background1_layer);

  // Draw the black rectangle background
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);

  // Draw the white rectangle background with round corners
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_width(ctx, 0);
  graphics_fill_rect(ctx, bounds, 12, GCornersAll);


  /* *************************************************
   * Draw the 12 circles */
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);
  // Draw the outline of a circle
  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_ONE_POS_X, CIRCLE_ONE_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_TWO_POS_X, CIRCLE_TWO_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_THREE_POS_X, CIRCLE_THREE_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_FOUR_POS_X, CIRCLE_FOUR_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_FIVE_POS_X, CIRCLE_FIVE_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_SIX_POS_X, CIRCLE_SIX_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_SEVEN_POS_X, CIRCLE_SEVEN_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_EIGHT_POS_X, CIRCLE_EIGHT_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_NINE_POS_X, CIRCLE_NINE_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_TEN_POS_X, CIRCLE_TEN_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_ELEVEN_POS_X, CIRCLE_ELEVEN_POS_Y),
		       CIRCLE_RADIUS);

  graphics_draw_circle(ctx,
		       GPoint(CIRCLE_TWELVE_POS_X, CIRCLE_TWELVE_POS_Y),
		       CIRCLE_RADIUS);

}

static void push_background (Window *window) {
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




//  s_one_text_layer = text_layer_create(GRect(1, 1, 8, 15));
//  text_layer_set_text_color(s_one_text_layer, GColorBlack);
//  text_layer_set_background_color(s_one_text_layer, GColorWhite);
//  text_layer_set_text_color(s_one_text_layer, GColorWhite);
//  text_layer_set_background_color(s_one_text_layer, GColorBlack);
//  text_layer_set_overflow_mode(s_one_text_layer, GTextOverflowModeWordWrap);
//  //text_layer_set_alignment(s_one_text_layer, GTextAlignmentCenter);
//  text_layer_set_text(s_one_text_layer, "1");

//  s_three_text_layer = text_layer_create(GRect(50 /*136 */, 75, 20, 30));
//  text_layer_set_text_color(s_three_text_layer, GColorBlack);
//  text_layer_set_background_color(s_three_text_layer, GColorWhite);
////  text_layer_set_text_color(s_three_text_layer, GColorWhite);
////  text_layer_set_background_color(s_three_text_layer, GColorBlack);
//  text_layer_set_overflow_mode(s_three_text_layer, GTextOverflowModeWordWrap);
//  //text_layer_set_alignment(s_one_text_layer, GTextAlignmentCenter);
//  text_layer_set_font(s_three_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
//  text_layer_set_text(s_three_text_layer, "3");

  // Add to the Window
  layer_add_child(window_layer, s_background1_layer);
  layer_add_child(window_layer, s_background2_layer);
//  layer_add_child(window_layer, text_layer_get_layer(s_three_text_layer));





}

static void main_window_load(Window *window) {
  // Draw the background
  push_background(window);
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_background1_layer);
  text_layer_destroy(s_one_text_layer);
  text_layer_destroy(s_two_text_layer);
  text_layer_destroy(s_three_text_layer);
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
