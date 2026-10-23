#pragma once
#include <stdbool.h>
typedef void (*osm_callback_type) (bool detected);
void osm_callback_register(osm_callback_type callback);
void osm_task(void *arg);
void osm_pin_config(void);
