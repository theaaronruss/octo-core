#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Represents if the display window should close.
 */
extern bool window_closing;

/**
 * Create SDL window.
 */
bool display_init();

/**
 * Destroy window.
 */
void display_free();

/**
 * Update the display.
 */
void display_update();

/**
 * Clear the display.
 */
void display_clear();

/**
 * Display a sprite on the display.
 *
 * @return true if collision occurred, false otherwise.
 */
bool display_draw_sprite(uint8_t *memory, int bytes, int draw_x, int draw_y);

#endif

