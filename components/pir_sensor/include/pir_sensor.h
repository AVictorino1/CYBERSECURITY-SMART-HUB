#pragma once
#include <stdbool.h>
void config_pir(void);
void pir_task(void *arg);
extern volatile bool motion_detected;
typedef void (*pir_callback_type) (void);
void callback_register(pir_callback_type callback);
