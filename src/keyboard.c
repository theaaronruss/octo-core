#include "keyboard.h"
#include "SDL3/SDL.h" // IWYU pragma: keep

 const SDL_Scancode scan_codes[NUM_KEYS] = {
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

bool is_key_pressed(int scan_code) {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[scan_code]) {
        return true;
    }
    return false;
}

int current_key() {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < NUM_KEYS; i++) {
        if (key_states[scan_codes[i]]) {
        }
    }
    return -1;
}

