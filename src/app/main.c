#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "include/drivers/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "include/hal/rng.h"
#include "include/models/ball.h"
#include "include/board/collision.h"
#include "include/models/graphics.h"
#include "include/drivers/hardware.h"
#include "include/board/config.h"

int main() {
    stdio_init_all();

    hardware_init();

    ssd1306_init();
    ssd1306_t display;
    ssd1306_init_bm(&display, 128, 64, false, 0x3C, i2c1);

    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    
    // Inicializa o tabuleiro
    init_board(ssd);

    bool pause_simulation = false;
    int canaletas[NUM_CANALETAS] = {0};
    int contador_bolinhas = 0;

    int tick_interval = 1;
    absolute_time_t last_tick_time = get_absolute_time();
    absolute_time_t last_spawn_time = get_absolute_time();

    while (true) {
        absolute_time_t now = get_absolute_time();
        
        // Verifica botão com debounce
        if (!gpio_get(BUTTON_PIN)) {
            sleep_ms(50);
            if (!gpio_get(BUTTON_PIN)) {
                pause_simulation = !pause_simulation;
                while (!gpio_get(BUTTON_PIN)); // Espera soltar o botão
                
                ssd1306_clear_display(ssd);
                
                if (!pause_simulation) {
                    // Redesenha o triângulo de pinos
                    draw_pins_triangle(ssd);
                }
            }
        }
    
        if (pause_simulation) {
            // Modo pausado - mostra gráfico em tela cheia
            int max_canaleta = 1;
            for (int j = 0; j < NUM_CANALETAS; j++) {
                if (canaletas[j] > max_canaleta) {
                    max_canaleta = canaletas[j];
                }
            }
            
            ssd1306_clear_display(ssd);
            draw_fullscreen_graph(ssd, canaletas, max_canaleta);
            render_on_display(ssd, &frame_area);
            sleep_ms(100);
        } else {
            // Modo normal de simulação
            int elapsed = to_ms_since_boot(now) - to_ms_since_boot(last_tick_time);
            int spawn_elapsed = to_ms_since_boot(now) - to_ms_since_boot(last_spawn_time);
    
            if (elapsed >= tick_interval) {
                last_tick_time = now;
    
                // Atualiza posição das bolas
                for (int i = 0; i < num_bolas; i++) {
                    draw_ball(ssd, bolas[i], false);
                }
    
                for (int i = 0; i < num_bolas;) {
                    Ball *ball = &bolas[i];
                    Ball next_pos = *ball;
                    next_pos.y += next_pos.dy;
    
                    if (check_collision(ssd, next_pos.x, next_pos.y, ball->radius)) {
                        int teleport_distance = 6;
                        int direction = get_random_direction(teleport_distance);
                        int new_x = ball->x + direction;
                        if (new_x < ball->radius) new_x = ball->radius;
                        if (new_x >= ssd1306_width - ball->radius) new_x = ssd1306_width - ball->radius - 1;
                        ball->x = new_x;
                    }
    
                    ball->y += ball->dy;
    
                    if (ball->y >= ssd1306_height - ball->radius - 1) {
                        int centro = ssd1306_width / 2;
                        int canaleta_largura = ssd1306_width / NUM_CANALETAS;
                        int desvio = ball->x - centro;
                        int canaleta;
    
                        if (desvio >= 0) {
                            canaleta = NUM_CANALETAS / 2 + desvio / canaleta_largura;
                        } else {
                            canaleta = NUM_CANALETAS / 2 - 1 + desvio / canaleta_largura;
                        }
    
                        if (canaleta < 0) canaleta = 0;
                        if (canaleta >= NUM_CANALETAS) canaleta = NUM_CANALETAS - 1;
    
                        canaletas[canaleta]++;
                        contador_bolinhas++;
    
                        printf("Canaletas: ");
                        for (int j = 0; j < NUM_CANALETAS; j++) {
                            printf("%d ", canaletas[j]);
                        }
                        printf("\n");
    
                        bolas[i] = bolas[num_bolas - 1];
                        num_bolas--;
                        continue;
                    }
    
                    i++;
                }
    
                for (int i = 0; i < num_bolas; i++) {
                    draw_ball(ssd, bolas[i], true);
                }
    
                // Limpa área do texto
                for (int i = 0; i < 128; i++) {
                    ssd[i] = 0;
                }
    
                // Soma total das canaletas
                int soma_total = 0;
                for (int i = 0; i < NUM_CANALETAS; i++) {
                    soma_total += canaletas[i];
                }
    
                // Mostra contador no canto superior direito
                char contador_texto[20];
                snprintf(contador_texto, sizeof(contador_texto), "%d", soma_total);
                int texto_len = strlen(contador_texto);
                int x_offset = ssd1306_width - texto_len * 8;
                for (int i = 0; i < texto_len; i++) {
                    ssd1306_draw_char(ssd, x_offset + i * 8, 0, contador_texto[i]);
                }
    
                // Desenha mini gráfico
                int max_canaleta = 1;
                for (int j = 0; j < NUM_CANALETAS; j++) {
                    if (canaletas[j] > max_canaleta) {
                        max_canaleta = canaletas[j];
                    }
                }
                draw_canaletas_graph(ssd, canaletas, max_canaleta);
                
                render_on_display(ssd, &frame_area);
            }

            if (spawn_elapsed >= 200) {
                spawn_ball_center();
                last_spawn_time = now;
            }

            sleep_ms(1);
        }
    }
}