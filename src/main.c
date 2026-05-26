#include "SDL3/SDL.h" // IWYU pragma: keep
#include "SDL3/SDL_main.h" // IWYU pragma: keep
#include "cpu.h"
#include "display.h"
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *byte[]) {
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success) {
        printf("Failed to initialize SDL\n");
        return 1;
    }
    display_init();
    struct cpu cpu = {};
    cpu_init(&cpu);
    cpu_load_rom(&cpu, "test.ch8");
    int cycle = 0;

    while (!window_closing) {
        cpu_clock_cycle(&cpu);
        if (cycle >= 9) {
            cycle = 0;
            display_update();
        }
        usleep(1700);
        cycle++;
    }
    
    cpu_free(&cpu);
    display_free();
    SDL_Quit();
    return 0;
}

