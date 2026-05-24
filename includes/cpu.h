#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

struct cpu {
    // Registers
    uint8_t registers[16];
    int16_t i;
    uint8_t dt;
    uint8_t st;

    // Program counter
    uint16_t pc;

    // Stack pointer
    uint8_t sp;

    // Stack
    uint16_t stack[16];

    // Memory (4K)
    uint8_t *memory;
};

/**
 * Initialize the CPU.
 *
 * @return true if successful, otherwise false
 */
bool cpu_init(struct cpu *cpu);

/**
 * Free the resources from the CPU. Does nothing if cpu is NULL.
 */
void cpu_free(struct cpu *cpu);

/**
 * Load ROM contents into memory at 0x200.
 *
 * @param filename Filename of the ROM to load.
 * @return true if successful, otherwise false
 */
bool cpu_load_rom(struct cpu *cpu, const char *filename);

/**
 * Retrieve next instruction and execute it.
 */
void cpu_clock_cycle(struct cpu *cpu);

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
void jump(struct cpu *cpu, uint16_t instruction);

/**
 * Call subroutine at an address.
 */
void subroutine_call(struct cpu *cpu, uint16_t instruction);

/**
 * Skip next instruction if Vx = kk.
 */
void skip_equal_value(struct cpu *cpu, uint16_t instruction);

/**
 * Skip next instruction if Vx != kk.
 */
void skip_not_equal_value(struct cpu *cpu, uint16_t instruction);

/**
 * Skip next instruction if Vx = Vy.
 */
void skip_equal_register(struct cpu *cpu, uint16_t instruction);

/**
 * Load byte into a register.
 */
void load_value_to_register(struct cpu *cpu, uint16_t instruction);

/**
 * Add value to register.
 */
void add_value_to_register(struct cpu *cpu, uint16_t instruction);

/**
 * Store the value of one register into another.
 */
void load_register_to_register(struct cpu *cpu, uint16_t instruction);

/**
 * OR two registers and store the result into a register.
 */
void or_registers(struct cpu *cpu, uint16_t instruction);

/**
 * AND two registers and store the result into a register.
 */
void and_registers(struct cpu *cpu, uint16_t instruction);

/**
 * XOR two registers and store the result into a register.
 */
void xor_registers(struct cpu *cpu, uint16_t instruction);

/**
 * Add two registers and store the result into a register. Set the vF register
 * if there is a carry.
 */
void add_registers(struct cpu *cpu, uint16_t instruction);

/**
 * Subtract two registers and store the result into a register. Set the vF
 * register if there is no borrow.
 */
void sub_registers(struct cpu *cpu, uint16_t instruction);

/**
 * Shift a register to the right.
 */
void shift_register_right(struct cpu *cpu, uint16_t instruction);

/**
 * Subtract two registers and store the result into a register.
 */
void sub_registers_reverse(struct cpu *cpu, uint16_t instruction);

/**
 * Shift a register to the left.
 */
void shift_register_left(struct cpu *cpu, uint16_t instruction);

/**
 * Skip next instruction if Vx != Vy.
 */
void skip_not_equal_register(struct cpu *cpu, uint16_t instruction);

/**
 * Set the index register to a given value.
 */
void load_index(struct cpu *cpu, uint16_t instruction);

/**
 * Set the program counter to a given value plus a given offset.
 */
void jump_offset(struct cpu *cpu, uint16_t instruction);

/**
 * Set register to random value AND with a given value.
 */
void random_value(struct cpu *cpu);

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
 * Load delay timer value into a register.
 */
void load_delay_timer(struct cpu *cpu, uint16_t instruction);

/**
 * Wait for a key press, store the value of the key in a register.
 */
void load_key(struct cpu *cpu);

/**
 * Set delay timer to a value in a given register.
 */
void set_delay_timer(struct cpu *cpu, uint16_t instruction);

/**
 * Set sound timer to a value in a given register.
 */
void set_sound_timer(struct cpu *cpu, uint16_t instruction);

/**
 * Add the value stored in a register to the index register.
 */
void add_index(struct cpu *cpu, uint16_t instruction);

/**
 * Store the location of a sprite into the index register.
 */
void load_sprite(struct cpu *cpu, uint16_t instruction);

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

