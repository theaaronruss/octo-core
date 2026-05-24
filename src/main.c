#include "SDL3/SDL.h" // IWYU pragma: keep
#include "SDL3/SDL_main.h" // IWYU pragma: keep
#include "display.h"
#include <stdbool.h>

int main(int argc, char *byte[]) {
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success) {
        printf("Failed to initialize SDL\n");
        return 1;
    }
    display_init();

    while (!window_closing) {
        display_clear();
        display_update();
    }
    
    display_free();
    SDL_Quit();
    return 0;
}

// void render_texture(SDL_Renderer* renderer, SDL_Texture *texture) {
//     SDL_SetRenderTarget(renderer, texture);
//     bool even = true;
//     for (int i = 0; i < 64 * 32; i++) {
//         if (even) {
//             SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
//         } else {
//             SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
//         }
//         even = !even;
//         int x = i % 64;
//         int y = i / 64;
//         if (x == 63) {
//             even = !even;
//         }
//         SDL_RenderPoint(renderer, x, y);
//     }
//     SDL_SetRenderTarget(renderer, NULL);
// }
//
// int main(int argc, char *argv[]) {
//     bool success = SDL_Init(SDL_INIT_VIDEO);
//     if (!success) {
//         printf("Failed to init SDL: %s\n", SDL_GetError());
//         return 1;
//     }
//
//     SDL_Window *window = SDL_CreateWindow("SDL3", 640, 320, 0);
//     if (window == NULL) {
//         printf("Failed to create window: %s\n", SDL_GetError());
//         return 1;
//     }
//
//     SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
//     if (renderer == NULL) {
//         printf("Failed to create renderer: %s\n", SDL_GetError());
//         return 1;
//     }
//
//     SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, 64, 32);
//     if (texture == NULL) {
//         printf("Failed to create texture: %s\n", SDL_GetError());
//         return 1;
//     }
//
//     SDL_FRect src = { 0, 0, 64, 32 };
//     SDL_FRect dest = { 0, 0, 640, 320 };
//     SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
//     bool quit = false;
//     while (!quit) {
//         SDL_Event e;
//         while (SDL_PollEvent(&e)) {
//             if (e.type == SDL_EVENT_QUIT) {
//                 quit = true;
//             }
//         }
//         render_texture(renderer, texture);
//         SDL_RenderTexture(renderer, texture, &src, &dest);
//         SDL_RenderPresent(renderer);
//     }
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//
//     SDL_Quit();
//     return 0;
// }

