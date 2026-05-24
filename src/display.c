#include "SDL3/SDL.h" // IWYU pragma: keep
#include "display.h"
#include <stdbool.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;

static SDL_FRect tex_bounds = { 0, 0, 64, 32 };
static SDL_FRect display_bounds = { 0, 0, 640, 320 };

bool window_closing = false;

bool display_init() {
    // Make sure window isn't already initialized
    if (window != NULL) {
        return true;
    }

    window = SDL_CreateWindow("OctoCore", 640, 320, 0);
    if (window == NULL) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
        return false;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET,  64, 32);
    if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        return false;
    }
    SDL_SetRenderTarget(renderer, texture);

    return true;
}

void display_free() {
    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
}

void display_update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            window_closing = true;
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, texture, &tex_bounds, &display_bounds);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);
}

void display_clear() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &tex_bounds);
}

