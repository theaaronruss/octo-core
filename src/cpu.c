#include "cpu.h"
#include "display.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 4096

#define CHAR_ADDR 0x050
#define ROM_ADDR 0x200
#define ROM_SIZE 3584

static uint8_t char_data[] = {
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

bool cpu_init(struct cpu *cpu) {
    cpu->memory = (uint8_t *) malloc(MEM_SIZE);
    if (cpu->memory == NULL) {
        printf("Failed to allocate memory\n");
        return false;
    }
    cpu->sp = 0;
    cpu->pc = ROM_ADDR;
    memcpy(cpu->memory + CHAR_ADDR, char_data, 5 * 16);
    return true;
}

void cpu_free(struct cpu *cpu) {
    if (cpu == NULL) {
        return;
    }
    free(cpu->memory);
}

bool cpu_load_rom(struct cpu *cpu, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return false;
    }
    fread(cpu->memory + ROM_ADDR, 1, ROM_SIZE, file);
    fclose(file);
    return true;
}

void cpu_clock_cycle(struct cpu *cpu) {
    uint8_t msb = cpu->memory[cpu->pc];
    uint8_t lsb = cpu->memory[cpu->pc + 1];
    uint16_t instruction = (msb << 8) | lsb;
    cpu->pc += 2;

    if (instruction == 0x00E0) {
        display_clear();
    } else if (instruction == 0x00EE) {
        subroutine_return(cpu);
    } else if ((instruction & 0xF000) == 0x1000) {
        jump(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x2000) {
        subroutine_call(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x3000) {
        skip_equal_value(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x4000) {
        skip_not_equal_value(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x5000) {
        skip_equal_register(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x6000) {
        load_value_to_register(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x7000) {
        // TODO: Set Vx += kk
        printf("Set Vx += kk\n");
    } else if ((instruction & 0xF000) == 0x8000) {
        uint16_t last_nibble = instruction & 0x000F;
        if (last_nibble == 0x0000) {
            load_register_to_register(cpu, instruction);
        } else if (last_nibble == 0x0001) {
            // TODO: Set Vx = Vx OR Vy
            printf("Set Vx = Vx OR Vy\n");
        } else if (last_nibble == 0x0002) {
            // TODO: Set Vx = Vx AND Vy
            printf("Set Vx = Vx AND Vy\n");
        } else if (last_nibble == 0x0003) {
            // TODO: Set Vx = Vx XOR Vy
            printf("Set Vx = Vx XOR Vy\n");
        } else if (last_nibble == 0x0004) {
            // TODO: Set Vx = Vx + Vy
            printf("Set Vx = Vx + Vy\n");
        } else if (last_nibble == 0x0005) {
            // TODO: Set Vx = Vx - Vy
            printf("Set Vx = Vx - Vy\n");
        } else if (last_nibble == 0x0006) {
            // TODO: Shift Vx right
            printf("Shift Vx right\n");
        } else if (last_nibble == 0x0007) {
            // TODO: Set Vx = Vy - Vx
            printf("Set Vx = Vy - Vx\n");
        } else if (last_nibble == 0x000E) {
            // TODO: Shift Vx left
            printf("Shift Vx left\n");
        }
    } else if ((instruction & 0xF000) == 0x9000) {
        skip_not_equal_register(cpu, instruction);
    } else if ((instruction & 0xF000) == 0xA000) {
        // TODO: Set index register
        printf("Set index register\n");
    } else if ((instruction & 0xF000) == 0xB000) {
        // TODO: Jummp to location + V0
        printf("Jummp to location + V0\n");
    } else if ((instruction & 0xF000) == 0xC000) {
        // TODO: Set Vx = random byte
        printf("Set Vx = random byte\n");
    } else if ((instruction & 0xF000) == 0xD000) {
        // TODO: Draw sprite
        printf("Draw sprite\n");
    } else if ((instruction & 0xF000) == 0xE000) {
        uint16_t last_byte = instruction & 0x00FF;
        if (last_byte == 0x009E) {
            // TODO: Skip instruction if key Vx is pressed
            printf("Skip instruction if key Vx is pressed\n");
        } else if (last_byte == 0x00A1) {
            // TODO: Skip instruction if key Vx is not pressed
            printf("Skip instruction if key Vx is not pressed\n");
        }
    } else if ((instruction & 0xF000) == 0xF000) {
        uint16_t last_byte = instruction & 0x00FF;
        if (last_byte == 0x0007) {
            // TODO: Set Vx = delay timer
            printf("Set Vx = delay timer\n");
        } else if (last_byte == 0x000A) {
            // TODO: Wait for keypress
            printf("Wait for keypress\n");
        } else if (last_byte == 0x0015) {
            // TODO: Set delay timer = Vx
            printf("Set delay timer = Vx\n");
        } else if (last_byte == 0x0018) {
            // TODO: Set sound timer = Vx
            printf("Set sound timer = Vx\n");
        } else if (last_byte == 0x001E) {
            // TODO: Add Vx to index register
            printf("Add Vx to index register\n");
        } else if (last_byte == 0x0029) {
            // TODO: Set index register to sprite location
            printf("Set index register to sprite location\n");
        } else if (last_byte == 0x0033) {
            // TODO: Store BCD Vx to memory
            printf("Store BCD Vx to memory\n");
        } else if (last_byte == 0x0055) {
            // TODO: Store registers in memory
            printf("Store registers in memory\n");
        } else if (last_byte == 0x0065) {
            // TODO: Read registers from memory
            printf("Read registers from memory\n");
        }
    }
}

void clear_display(struct cpu *cpu) {
    display_clear();
}

void subroutine_return(struct cpu *cpu) {
    cpu->sp--;
    cpu->pc = cpu->stack[cpu->sp];
}

void jump(struct cpu *cpu, uint16_t instruction) {
    cpu->pc = instruction & 0x0FFF;
}

void subroutine_call(struct cpu *cpu, uint16_t instruction) {
    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp++;
    cpu->pc = instruction & 0xFFF;
}

void skip_equal_value(struct cpu *cpu, uint16_t instruction) {
    uint8_t value = instruction & 0x00FF;
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t reg_value = cpu->registers[reg];
    if (reg_value == value) {
        cpu->pc += 2;
    }
}

void skip_not_equal_value(struct cpu *cpu, uint16_t instruction) {
    uint8_t value = instruction & 0x00FF;
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t reg_value = cpu->registers[reg];
    if (reg_value != value) {
        cpu->pc += 2;
    }
}

void skip_equal_register(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    if (value_x == value_y) {
        cpu->pc += 2;
    }
}

void load_value_to_register(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t value = instruction & 0x00FF;
    cpu->registers[reg] = value;
}

void add_value_to_register(struct cpu *cpu) {
    // TODO: Implement
}

void load_register_to_register(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    cpu->registers[reg_x] = cpu->registers[reg_y];
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

void skip_not_equal_register(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    if (value_x != value_y) {
        cpu->pc += 2;
    }
}

void load_index(struct cpu *cpu) {
    // TODO: Implement
}

void jump_offset(struct cpu *cpu) {
    // TODO: Implement
}

void random_value(struct cpu *cpu) {
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
