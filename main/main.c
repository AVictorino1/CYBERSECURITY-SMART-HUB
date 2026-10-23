
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "leds.h"
#include "dht_sensor.h"
#include "display.h"
#include "pir_sensor.h"
#include "obstacles_sensor.h"
#define LED_PIN 13

void dht_task(void *pvParameters);
void turn_led_pir(bool detected);

float humidity;
float temperature;
void app_main(void)
{
    initialize_led(LED_PIN);
    init_display();
    xTaskCreate(dht_task, "dht_task", 2048, NULL, 5, NULL);

    /*
    config_pir();
    xTaskCreate(pir_task, "pir_task", 2048, NULL, 5, NULL);
    
    */
    osm_callback_register(turn_led_pir);
    osm_pin_config();
    xTaskCreate(osm_task, "osm_task", 2048, NULL, 5, NULL);
    
}
void turn_led_pir(bool detected){
    set_led_brightness(detected ? 0: 255);
    
}

void dht_task(void *pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(2000)); 
    while(1) {

       
        read_data(&humidity, &temperature);
        char h_text[32];
        snprintf(h_text, sizeof(h_text), "%.1f%%", humidity);

        char t_text[32];
        snprintf(t_text, sizeof(h_text), "%.1f °C", temperature);

        show_text(0,"Humidity:");
        show_text(1,h_text);
        show_text(2,"Temperature:");
        show_text(3,t_text);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


