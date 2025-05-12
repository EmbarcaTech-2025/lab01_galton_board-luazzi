#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "../drivers/ssd1306.h"

#define NUM_CANALETAS 10

void draw_canaletas_graph(uint8_t *buffer, int *canaletas, int max_value);
void draw_fullscreen_graph(uint8_t *buffer, int *canaletas, int max_value);

#endif // GRAPHICS_H