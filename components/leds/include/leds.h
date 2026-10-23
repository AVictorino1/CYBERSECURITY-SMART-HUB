#pragma once

#include "esp_err.h"

esp_err_t initialize_led(int LED_PIN);
esp_err_t set_led_brightness(uint8_t brightness);
