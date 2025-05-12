#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "../drivers/ssd1306.h"

#define MAX_BOLAS 20

// Estrutura para representar a bolinha
typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int radius;
} Ball;

extern Ball bolas[MAX_BOLAS];
extern int num_bolas;

// Inicializa o array de bolas
void init_balls();

// Cria uma nova bola no centro
void spawn_ball_center();

// Desenha ou apaga uma bola no buffer
void draw_ball(uint8_t *buffer, Ball ball, bool set);
#endif // BALL_H