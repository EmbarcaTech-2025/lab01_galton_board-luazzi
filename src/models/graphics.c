#include "graphics.h"
#include <string.h>

void draw_canaletas_graph(uint8_t *buffer, int *canaletas, int max_value) {
    const int graph_x = 0;
    const int graph_y = 0;
    const int graph_width = 40;
    const int graph_height = 20;
    const int bar_width = 3;
    const int bar_spacing = 1;
    
    for (int y = graph_y; y < graph_y + graph_height; y++) {
        for (int x = graph_x; x < graph_x + graph_width; x++) {
            ssd1306_set_pixel(buffer, x, y, false);
        }
    }
    
    if (max_value <= 0) return;
    
    for (int i = 0; i < NUM_CANALETAS && i < 10; i++) {
        int bar_height = (canaletas[i] * graph_height) / max_value;
        if (bar_height > graph_height) bar_height = graph_height;
        
        int x_start = graph_x + i * (bar_width + bar_spacing);
        
        for (int x = x_start; x < x_start + bar_width; x++) {
            for (int y = graph_y + graph_height - bar_height; y < graph_y + graph_height; y++) {
                ssd1306_set_pixel(buffer, x, y, true);
            }
        }
    }
}

void draw_fullscreen_graph(uint8_t *buffer, int *canaletas, int max_value) {
    memset(buffer, 0, ssd1306_buffer_length);
    
    if (max_value <= 0) return;
    
    const int margin = 2;
    const int bar_width = (ssd1306_width - 2 * margin) / NUM_CANALETAS - 1;
    const int graph_height = ssd1306_height - 10;
    
    for (int i = 0; i < NUM_CANALETAS; i++) {
        int bar_height = (canaletas[i] * graph_height) / max_value;
        if (bar_height > graph_height) bar_height = graph_height;
        
        int x_start = margin + 1 + i * (bar_width + 1);
        
        for (int x = x_start; x < x_start + bar_width; x++) {
            for (int y = ssd1306_height - margin - 1; y >= ssd1306_height - margin - bar_height; y--) {
                ssd1306_set_pixel(buffer, x, y, true);
            }
        }
    }
}