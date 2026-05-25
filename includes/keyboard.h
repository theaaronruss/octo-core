#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL3/SDL.h" // IWYU pragma: keep
#include <stdbool.h>

const SDL_Scancode scan_codes[16] = {
    SDL_SCANCODE_X,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_W,
    SDL_SCANCODE_E,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_C,
    SDL_SCANCODE_4,
    SDL_SCANCODE_R,
    SDL_SCANCODE_F,
    SDL_SCANCODE_V,
};

// #define KEY_1 SDL_SCANCODE_1
// #define KEY_2 SDL_SCANCODE_2
// #define KEY_3 SDL_SCANCODE_3
// #define KEY_C SDL_SCANCODE_4
// #define KEY_4 SDL_SCANCODE_Q
// #define KEY_5 SDL_SCANCODE_W
// #define KEY_6 SDL_SCANCODE_E
// #define KEY_D SDL_SCANCODE_R
// #define KEY_7 SDL_SCANCODE_A
// #define KEY_8 SDL_SCANCODE_S
// #define KEY_9 SDL_SCANCODE_D
// #define KEY_E SDL_SCANCODE_F
// #define KEY_A SDL_SCANCODE_Z
// #define KEY_0 SDL_SCANCODE_X
// #define KEY_B SDL_SCANCODE_C
// #define KEY_F SDL_SCANCODE_V

bool is_key_pressed(int scan_code);

#endif

