#include "hardware.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "include/drivers/ssd1306.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;


void hardware_init() {
    stdio_init_all();
    
    // Inicializações de hardware
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(ADC_TEMPERATURE_CHANNEL);
    
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

uint16_t read_temperature_adc() {
    adc_select_input(ADC_TEMPERATURE_CHANNEL);
    return adc_read();
}