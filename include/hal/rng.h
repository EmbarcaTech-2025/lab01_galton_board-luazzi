#ifndef RNG_H
#define RNG_H

#include <stdint.h>

// Inicializa o gerador de números aleatórios
void init_random();

// Gera um número aleatório de 32 bits
uint32_t generate_random();

// Função para gerar uma direção aleatória
int get_random_direction(int teleport_distance);

#endif // RNG_H