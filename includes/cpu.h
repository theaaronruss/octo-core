#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

struct cpu {
    // Registers
    int8_t v0;
    int8_t v1;
    int8_t v2;
    int8_t v3;
    int8_t v4;
    int8_t v5;
    int8_t v6;
    int8_t v7;
    int8_t v8;
    int8_t v9;
    int8_t vA;
    int8_t vB;
    int8_t vC;
    int8_t vD;
    int8_t vE;
    int8_t vF;
    int16_t i;
    int8_t dt;
    int8_t st;

    // Program counter
    int16_t pc;

    // Stack pointer
    int8_t sp;

    // Stack
    int16_t stack[16];

    // Memory (4K)
    int8_t *memory;
};

/**
 * Initialize the CPU.
 *
 * @return true if successful, otherwise false
 */
bool init_cpu(struct cpu *cpu);

/**
 * Free the resources from the CPU. Does nothing if cpu is NULL.
 */
void free_cpu(struct cpu *cpu);

/**
 * Load ROM contents into memory at 0x200.
 *
 * @param filename Filename of the ROM to load.
 * @return true if successful, otherwise false
 */
bool load_rom(struct cpu *cpu, const char *filename);

#endif

