#ifndef HARDWARE_H
#define HARDWARE_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define ADC_TEMPERATURE_CHANNEL 4
#define BUTTON_PIN 5

void hardware_init();
uint16_t read_temperature_adc();

#endif // HARDWARE_H