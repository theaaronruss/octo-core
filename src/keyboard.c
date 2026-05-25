#include "keyboard.h"
#include "SDL3/SDL.h" // IWYU pragma: keep

bool is_key_pressed(int scan_code) {
    const bool *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[scan_code]) {
        return true;
    }
    return false;
}

