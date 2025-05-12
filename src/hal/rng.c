#include "rng.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Variável global para manter o estado do gerador
static uint32_t random_state = 0;

// Função de geração de números aleatórios
uint32_t generate_random() {
    // Lê temperatura (varia lentamente)
    uint16_t temp_adc = adc_read(); // Assumindo que o ADC já está configurado
    
    // Tempo em microssegundos (varia rapidamente)
    uint32_t time = to_us_since_boot(get_absolute_time());
    
    // ADC noise (para maior entropia)
    uint16_t adc_noise = adc_read() ^ adc_read();
    
    // Mistura tudo com o estado anterior
    random_state ^= (random_state << 13);
    random_state ^= (random_state >> 17);
    random_state ^= (random_state << 5);
    random_state += temp_adc ^ time ^ adc_noise;
    
    return random_state;
}

// Função para inicializar o gerador
void init_random() {

    random_state = to_us_since_boot(get_absolute_time()) ^ adc_read();
    
    for(int i = 0; i < 10; i++) {
        generate_random();
    }
}

int get_random_direction(int teleport_distance) {
    uint32_t random_value = generate_random();
    return (random_value % 2) ? teleport_distance : -teleport_distance;
}