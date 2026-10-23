#include <stdio.h>
#include "leds.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#define LED_SPEED_MODE LEDC_LOW_SPEED_MODE
#define LED_CHANNEL LEDC_CHANNEL_0

esp_err_t initialize_led(int LED_PIN);
esp_err_t set_led_brightness(uint8_t brightness);


esp_err_t initialize_led(int LED_PIN)
{
    

    const ledc_timer_config_t timer_config = {
        .speed_mode = LED_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
        .deconfigure = false
    };

    const ledc_channel_config_t led_config = {
        .gpio_num = LED_PIN,                  
        .speed_mode = LED_SPEED_MODE,        
        .channel = LED_CHANNEL,      
        .intr_type = LEDC_INTR_DISABLE,  
        .timer_sel = LEDC_TIMER_0,         
        .duty = 0,                  
        .hpoint = 0,                   
        .sleep_mode = 0,  
        .flags.output_invert = 0
    };

    
    ledc_timer_config(&timer_config);
    ledc_channel_config(&led_config);

    
    return ESP_OK;

}

esp_err_t set_led_brightness(uint8_t brightness){
    ledc_set_duty(LED_SPEED_MODE, LED_CHANNEL, brightness);
    ledc_update_duty(LED_SPEED_MODE, LED_CHANNEL);
    return ESP_OK;

}



