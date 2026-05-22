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

/**
 * Clear the display.
 */
void clear_display(struct cpu *cpu);

/**
 * Return from a subroutine. Set program counter to the value at the top of stack.
 */
void subroutine_return(struct cpu *cpu);

/**
 * Jump to an address by setting the program counter to a given value.
 */
void jump(struct cpu *cpu);

/**
 * Call subroutine at an address.
 */
void call(struct cpu *cpu);

/**
 * Skip next instruction if Vx = kk.
 */
void skip_equal_value(struct cpu *cpu);

/**
 * Skip next instruction if Vx != kk.
 */
void skip_not_equal_value(struct cpu *cpu);

/**
 * Skip next instruction if Vx = Vy.
 */
void skip_equal_register(struct cpu *cpu);

/**
 * Load byte into a register.
 */
void load_value_to_register(struct cpu *cpu);

/**
 * Add value to register.
 */
void add_value_to_register(struct cpu *cpu);

/**
 * Store the value of one register into another.
 */
void load_register_to_register(struct cpu *cpu);

/**
 * OR two registers and store the result into a register.
 */
void or_registers(struct cpu *cpu);

/**
 * AND two registers and store the result into a register.
 */
void and_registers(struct cpu *cpu);

/**
 * XOR two registers and store the result into a register.
 */
void xor_registers(struct cpu *cpu);

/**
 * Add two registers and store the result into a register. Set the vF register
 * if there is a carry.
 */
void add_registers(struct cpu *cpu);

/**
 * Subtract two registers and store the result into a register. Set the vF
 * register if there is no borrow.
 */
void sub_registers(struct cpu *cpu);

/**
 * Shift a register to the right.
 */
void shift_register_right(struct cpu *cpu);

/**
 * Subtract two registers and store the result into a register.
 */
void sub_registers_reverse(struct cpu *cpu);

/**
 * Shift a register to the left.
 */
void shift_register_left(struct cpu *cpu);

/**
 * Skip next instruction if Vx != Vy.
 */
void skip_not_equal_register(struct cpu *cpu);

/**
 * Set the index register to a given value.
 */
void load_index(struct cpu *cpu);

/**
 * Set the program counter to a given value plus a given offset.
 */
void jump_offset(struct cpu *cpu);

/**
 * Set register to random value AND with a given value.
 */
void random(struct cpu *cpu);

/**
 * Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
 */
void draw(struct cpu *cpu);

/**
 * Skip next instruction if key with the value in given register is pressed.
 */
void skip_key_pressed(struct cpu *cpu);

/**
 * Skip next instruction if key with the value in given register is not pressed.
 */
void skip_key_not_pressed(struct cpu *cpu);

/**
 * Set delay timer to a given value.
 */
void load_delay_timer(struct cpu *cpu);

/**
 * Wait for a key press, store the value of the key in a register.
 */
void load_key(struct cpu *cpu);

/**
 * Set delay timer to a value in a given register.
 */
void set_delay_timer(struct cpu *cpu);

/**
 * Set sound timer to a value in a given register.
 */
void set_sound_timer(struct cpu *cpu);

/**
 * Add the value stored in a register to the index register.
 */
void add_index(struct cpu *cpu);

/**
 * Store the location of a sprite into the index register.
 */
void load_sprite(struct cpu *cpu);

/**
 * Store BCD representation of a register in memory locations I, I+1, and I+2.
 */
void load_bcd(struct cpu *cpu);

/**
 * Store values of registers into memory starting at location stored in index
 * register.
 */
void save_registers(struct cpu *cpu);

/**
 * Read memory starting at location I and store the values into all of the
 * registers.
 */
void load_registers(struct cpu *cpu);

#endif

