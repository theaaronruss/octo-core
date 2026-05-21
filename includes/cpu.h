#ifndef CPU_H
#define CPU_H

#include <stdint.h>

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
    int16_t stack[];
};

void load_char_data();

#endif

