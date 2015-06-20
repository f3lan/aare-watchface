#include <pebble.h>

#define KEY_TEMPERATURE 0
#define KEY_A_TEMPERATURE 1
#define KEY_A_FLOW 2
#define KEY_A_HEIGHT 3
#define KEY_LOCATION 4

static Window *s_main_window;

static TextLayer *s_day_layer;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_a_description_layer;
static TextLayer *s_a_temperature_layer;
static TextLayer *s_a_flow_layer;
static TextLayer *s_a_height_layer;
static TextLayer *s_weather_temperature_layer;
static TextLayer *s_location_layer;

static GFont s_time_font;
static GFont s_day_font;
static GFont s_aare_font;
static GFont s_weather_temperature_font;
static GFont s_location_font;

static void update_time() {

  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffers
  static char time_buffer[] = "00:00";
  static char day_buffer[] = "Wednesday";
  static char date_buffer[] = "December 31";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(time_buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(time_buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  strftime(day_buffer, sizeof("Wednesday"), "%A", tick_time);
  strftime(date_buffer, sizeof("December 31"), "%B %d", tick_time);

  // Display this time/date in the TextLayers
  text_layer_set_text(s_time_layer, time_buffer);
  text_layer_set_text(s_day_layer, day_buffer);
  text_layer_set_text(s_date_layer, date_buffer);
}

static void main_window_load(Window *window) {
  window_set_background_color(s_main_window, GColorBlack);

  // Create day TextLayer
  s_day_layer = text_layer_create(GRect(5, 0, 139, 20));
  text_layer_set_background_color(s_day_layer, GColorBlack);
  text_layer_set_text_color(s_day_layer, GColorWhite);
  text_layer_set_text(s_day_layer, "Wednesday");

  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(5, 10, 139, 50));
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");

  // Create date TextLayer
  s_date_layer = text_layer_create(GRect(5, 55, 139, 20));
  text_layer_set_background_color(s_date_layer, GColorBlack);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_text(s_date_layer, "December 31");

  // Create Location TextLayer
  s_location_layer = text_layer_create(GRect(5, 135, 134, 15));
  text_layer_set_background_color(s_location_layer, GColorBlack);
  text_layer_set_text_color(s_location_layer, GColorWhite);
  text_layer_set_text(s_location_layer, "...");

  // Create Weather Temperature TextLayer
  s_weather_temperature_layer = text_layer_create(GRect(100, 4, 39, 15));
  text_layer_set_background_color(s_weather_temperature_layer, GColorBlack);
  text_layer_set_text_color(s_weather_temperature_layer, GColorWhite);
  text_layer_set_text(s_weather_temperature_layer, "...");

  // Create Aare TextLayer
  s_a_description_layer = text_layer_create(GRect(5, 75, 139, 15));
  text_layer_set_background_color(s_a_description_layer, GColorBlack);
  text_layer_set_text_color(s_a_description_layer, GColorWhite);
  text_layer_set_text(s_a_description_layer, "Aare:");

  // Create Aare Temperature TextLayer
  s_a_temperature_layer = text_layer_create(GRect(5, 90, 139, 15));
  text_layer_set_background_color(s_a_temperature_layer, GColorBlack);
  text_layer_set_text_color(s_a_temperature_layer, GColorWhite);
  text_layer_set_text(s_a_temperature_layer, "Temperature: ... °C");

  // Create Aare Flow TextLayer
  s_a_flow_layer = text_layer_create(GRect(5, 105, 139, 15));
  text_layer_set_background_color(s_a_flow_layer, GColorBlack);
  text_layer_set_text_color(s_a_flow_layer, GColorWhite);
  text_layer_set_text(s_a_flow_layer, "Flow: ... m^3/s");

  // Create Aare Height TextLayer
  s_a_height_layer = text_layer_create(GRect(5, 120, 139, 15));
  text_layer_set_background_color(s_a_height_layer, GColorBlack);
  text_layer_set_text_color(s_a_height_layer, GColorWhite);
  text_layer_set_text(s_a_height_layer, "Height: ... m.ü.M");


  //Create GFonts
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COURIER_NEW_BOLD_42));
  s_day_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COURIER_NEW_BOLD_16));
  s_aare_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COURIER_NEW_12));
  s_location_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COURIER_NEW_10));

  //Apply to TextLayers

  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentLeft);

  text_layer_set_font(s_day_layer, s_day_font);
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentLeft);

  text_layer_set_font(s_date_layer, s_day_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentLeft);

  text_layer_set_font(s_a_description_layer, s_aare_font);
  text_layer_set_text_alignment(s_a_description_layer, GTextAlignmentLeft);

  text_layer_set_font(s_a_temperature_layer, s_aare_font);
  text_layer_set_text_alignment(s_a_temperature_layer, GTextAlignmentLeft);

  text_layer_set_font(s_a_flow_layer, s_aare_font);
  text_layer_set_text_alignment(s_a_flow_layer, GTextAlignmentLeft);

  text_layer_set_font(s_a_height_layer, s_aare_font);
  text_layer_set_text_alignment(s_a_height_layer, GTextAlignmentLeft);

  text_layer_set_font(s_weather_temperature_layer, s_aare_font);
  text_layer_set_text_alignment(s_weather_temperature_layer, GTextAlignmentRight);

  text_layer_set_font(s_location_layer, s_location_font);
  text_layer_set_text_alignment(s_location_layer, GTextAlignmentRight);

  // Add all as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_day_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_a_description_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_a_temperature_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_a_flow_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_a_height_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_temperature_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_location_layer));

  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  // Destroy TextLayers
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_day_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_a_description_layer);
  text_layer_destroy(s_a_temperature_layer);
  text_layer_destroy(s_a_flow_layer);
  text_layer_destroy(s_a_height_layer);
  text_layer_destroy(s_weather_temperature_layer);
  text_layer_destroy(s_location_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message!
    app_message_outbox_send();
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
// Store incoming information
  static char temperature_buffer[8];
  static char a_temperature[32];
  static char a_flow_buffer[32];
  static char a_height_buffer[32];
  static char location_buffer[64];

  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d °C", (int)t->value->int32);
      break;
    case KEY_A_TEMPERATURE:
      snprintf(a_temperature, sizeof(a_temperature), "Temperature: %d °C", (int)t->value->int32);
      break;
    case KEY_A_HEIGHT:
      snprintf(a_height_buffer, sizeof(a_height_buffer), "Height: %d m.ü.M", (int)t->value->int32);
      break;
    case KEY_A_FLOW:
      snprintf(a_flow_buffer, sizeof(a_flow_buffer), "Flow: %d m^3/s", (int)t->value->int32);
      break;
    case KEY_LOCATION:
      snprintf(location_buffer, sizeof(location_buffer), "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }

  // Assemble full string and display
  text_layer_set_text(s_weather_temperature_layer, temperature_buffer);
  text_layer_set_text(s_location_layer, location_buffer);
  text_layer_set_text(s_a_temperature_layer, a_temperature);
  text_layer_set_text(s_a_height_layer, a_height_buffer);
  text_layer_set_text(s_a_flow_layer, a_flow_buffer);

}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
	// Destroy Window
	window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
