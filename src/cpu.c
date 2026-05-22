#include "cpu.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 4096

#define CHAR_ADDR 0x050
#define ROM_ADDR 0x200
#define ROM_SIZE 3584

static int8_t char_data[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};

bool init_cpu(struct cpu *cpu) {
    cpu->memory = (int8_t *) malloc(MEM_SIZE);
    if (cpu->memory == NULL) {
        printf("Failed to allocate memory\n");
        return false;
    }
    cpu->pc = ROM_ADDR;
    memcpy(cpu->memory + CHAR_ADDR, char_data, 5 * 16);
    return true;
}

void free_cpu(struct cpu *cpu) {
    if (cpu == NULL) {
        return;
    }
    free(cpu->memory);
}

bool load_rom(struct cpu *cpu, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return false;
    }
    fread(cpu->memory + ROM_ADDR, 1, ROM_SIZE, file);
    fclose(file);
    return true;
}

void clear_display(struct cpu *cpu) {
    // TODO: Implement
}

void subroutine_return(struct cpu *cpu) {
    // TODO: Implement
}

void jump(struct cpu *cpu) {
    // TODO: Implement
}

void call(struct cpu *cpu) {
    // TODO: Implement
}

void skip_equal_value(struct cpu *cpu) {
    // TODO: Implement
}

void skip_not_equal_value(struct cpu *cpu) {
    // TODO: Implement
}

void skip_equal_register(struct cpu *cpu) {
    // TODO: Implement
}

void load_value_to_register(struct cpu *cpu) {
    // TODO: Implement
}

void add_value_to_register(struct cpu *cpu) {
    // TODO: Implement
}

void load_register_to_register(struct cpu *cpu) {
    // TODO: Implement
}

void or_registers(struct cpu *cpu) {
    // TODO: Implement
}

void and_registers(struct cpu *cpu) {
    // TODO: Implement
}

void xor_registers(struct cpu *cpu) {
    // TODO: Implement
}

void add_registers(struct cpu *cpu) {
    // TODO: Implement
}

void sub_registers(struct cpu *cpu) {
    // TODO: Implement
}

void shift_register_right(struct cpu *cpu) {
    // TODO: Implement
}

void sub_registers_reverse(struct cpu *cpu) {
    // TODO: Implement
}

void shift_register_left(struct cpu *cpu) {
    // TODO: Implement
}

void skip_not_equal_register(struct cpu *cpu) {
    // TODO: Implement
}

void load_index(struct cpu *cpu) {
    // TODO: Implement
}

void jump_offset(struct cpu *cpu) {
    // TODO: Implement
}

void random(struct cpu *cpu) {
    // TODO: Implement
}

void draw(struct cpu *cpu) {
    // TODO: Implement
}

void skip_key_pressed(struct cpu *cpu) {
    // TODO: Implement
}

void skip_key_not_pressed(struct cpu *cpu) {
    // TODO: Implement
}

void load_delay_timer(struct cpu *cpu) {
    // TODO: Implement
}

void load_key(struct cpu *cpu) {
    // TODO: Implement
}

void set_delay_timer(struct cpu *cpu) {
    // TODO: Implement
}

void set_sound_timer(struct cpu *cpu) {
    // TODO: Implement
}

void add_index(struct cpu *cpu) {
    // TODO: Implement
}

void load_sprite(struct cpu *cpu) {
    // TODO: Implement
}

void load_bcd(struct cpu *cpu) {
    // TODO: Implement
}

void save_registers(struct cpu *cpu) {
    // TODO: Implement
}

void load_registers(struct cpu *cpu) {
    // TODO: Implement
}
