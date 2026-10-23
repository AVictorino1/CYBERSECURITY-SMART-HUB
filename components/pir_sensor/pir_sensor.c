#include <stdio.h>
#include "pir_sensor.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#define PIR_PIN GPIO_NUM_26

bool installed = false;

void isr_handler_function(void *arg);
int get_level_pir(void);
void config_pir(void);
void pir_task(void *arg);
void isr_handler_function(void *arg);
void callback_register(pir_callback_type callback);
SemaphoreHandle_t xSemaphore = NULL;

volatile bool motion_detected = false;
static pir_callback_type on_motion;
void callback_register(pir_callback_type callback){
    on_motion = callback;
}
void config_pir(void)
{   
    xSemaphore = xSemaphoreCreateBinary();

    const gpio_config_t config = {
    .pin_bit_mask = (1ULL << PIR_PIN),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type =  GPIO_INTR_POSEDGE
    };

    gpio_config(&config);
    if (!installed){
        gpio_install_isr_service(0);
        installed = true;
    }
    

    gpio_isr_t isr_handler = isr_handler_function;
 
    gpio_isr_handler_add(PIR_PIN, isr_handler, NULL);
    
}

IRAM_ATTR void isr_handler_function(void *arg) {
    xSemaphoreGiveFromISR(xSemaphore, NULL);
    
}


int get_level_pir(void){
    int result = gpio_get_level(PIR_PIN);
    return result;
}

void pir_task(void *arg){
    while(1){
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        printf("MOTION DETECTED\n");
        vTaskDelay(pdMS_TO_TICKS(100));
        if (on_motion != NULL){
            on_motion();
        }
    }
}










