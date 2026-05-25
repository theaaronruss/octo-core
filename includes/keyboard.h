#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL3/SDL.h" // IWYU pragma: keep
#include <stdbool.h>

#define NUM_KEYS 16

extern const SDL_Scancode scan_codes[NUM_KEYS];
/**
 * Check if a given key is pressed.
 */
bool is_key_pressed(int scan_code);

/**
 * Get the current key pressed. Returns -1 if no key is pressed.
 */
int current_key();

#endif

