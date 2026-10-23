#include <stdio.h>
#include "dht.h"

#define SENSOR_PIN 4


void read_data(float *humidity, float *temperature) {
    gpio_set_pull_mode(SENSOR_PIN, GPIO_PULLUP_ONLY);
    dht_read_float_data(DHT_TYPE_DHT11, SENSOR_PIN, humidity, temperature);
    printf("Temperatura: %.1f°C | Humedad: %.1f%%\n", *temperature, *humidity);
}