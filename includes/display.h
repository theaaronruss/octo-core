#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

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

void display_clear();

#endif

