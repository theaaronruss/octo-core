#include "SDL3/SDL.h" // IWYU pragma: keep
#include "display.h"
#include <stdbool.h>

#define WIDTH 64
#define HEIGHT 32
#define DISPLAY_WIDTH WIDTH * 10
#define DISPLAY_HEIGHT HEIGHT * 10

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static uint8_t pixels[WIDTH * HEIGHT];

static SDL_FRect tex_bounds = { 0, 0, WIDTH, HEIGHT };
static SDL_FRect display_bounds = { 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT };

static SDL_Color off_color = { 0x1C, 0x1D, 0x1E, 0xFF };
static SDL_Color on_color = { 0xA7, 0xC9, 0xA1, 0xFF };

bool window_closing = false;

bool display_init() {
    // Make sure window isn't already initialized
    if (window != NULL) {
        return true;
    }

    window = SDL_CreateWindow("OctoCore", DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    if (window == NULL) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
        return false;
    }
    SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);

    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGB24,
            SDL_TEXTUREACCESS_TARGET,
            64,
            32
    );
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

static void update_texture() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        int x = i % WIDTH;
        int y = i / WIDTH;
        if (pixels[i]) {
            SDL_SetRenderDrawColor(
                renderer,
                on_color.r,
                on_color.g,
                on_color.b,
                on_color.a
            );
        } else {
            SDL_SetRenderDrawColor(
                renderer,
                off_color.r,
                off_color.g,
                off_color.b,
                off_color.a
            );
        }
        SDL_RenderPoint(renderer, x, y);
    }
}

void display_update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            window_closing = true;
        }
    }
    update_texture();
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, texture, &tex_bounds, &display_bounds);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);
}

void display_clear() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        pixels[i] = 0;
    }
}

bool display_draw_sprite(uint8_t *memory, int bytes, int draw_x, int draw_y) {
    bool collision = false;
    for (int y = 0; y < bytes; y++) {
        uint8_t row = memory[y];
        for (int x = 0; x < 8; x++) {
            int i = (draw_y + y) * WIDTH + x + draw_x;
            if (pixels[i]) {
                collision = true;
            }
            pixels[i] ^= (row & 0x80);
            row <<= 1;
        }
    }
    return collision;
}

