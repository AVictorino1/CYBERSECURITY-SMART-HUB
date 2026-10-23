#include <stdio.h>
#include "obstacles_sensor.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define OSM_PIN GPIO_NUM_26


static osm_callback_type obstacle_detected;
void osm_task(void *arg);
int get_level_pin(void);
void osm_pin_config(void);
void osm_callback_register(osm_callback_type callback);

void osm_callback_register(osm_callback_type callback){
    obstacle_detected = callback;
}

void osm_pin_config(void){
    const gpio_config_t config = {
    .pin_bit_mask = (1ULL << OSM_PIN),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type =  GPIO_INTR_POSEDGE
    };
    gpio_config(&config);
}
int get_level_pin(void){
    int result = gpio_get_level(OSM_PIN);
    return result;
}

void osm_task(void *arg){
    while(true){
        int result = get_level_pin();
        if (obstacle_detected != NULL){
            obstacle_detected(result);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}