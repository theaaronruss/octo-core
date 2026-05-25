#include "cpu.h"
#include "display.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
    srand(time(NULL));
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
        add_value_to_register(cpu, instruction);
    } else if ((instruction & 0xF000) == 0x8000) {
        uint16_t last_nibble = instruction & 0x000F;
        if (last_nibble == 0x0000) {
            load_register_to_register(cpu, instruction);
        } else if (last_nibble == 0x0001) {
            or_registers(cpu, instruction);
        } else if (last_nibble == 0x0002) {
            and_registers(cpu, instruction);
        } else if (last_nibble == 0x0003) {
            xor_registers(cpu, instruction);
        } else if (last_nibble == 0x0004) {
            add_registers(cpu, instruction);
        } else if (last_nibble == 0x0005) {
            sub_registers(cpu, instruction);
        } else if (last_nibble == 0x0006) {
            shift_register_right(cpu, instruction);
        } else if (last_nibble == 0x0007) {
            sub_registers_reverse(cpu, instruction);
        } else if (last_nibble == 0x000E) {
            shift_register_left(cpu, instruction);
        }
    } else if ((instruction & 0xF000) == 0x9000) {
        skip_not_equal_register(cpu, instruction);
    } else if ((instruction & 0xF000) == 0xA000) {
        load_index(cpu, instruction);
    } else if ((instruction & 0xF000) == 0xB000) {
        jump_offset(cpu, instruction);
    } else if ((instruction & 0xF000) == 0xC000) {
        random_value(cpu, instruction);
    } else if ((instruction & 0xF000) == 0xD000) {
        draw(cpu, instruction);
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
            load_delay_timer(cpu, instruction);
        } else if (last_byte == 0x000A) {
            // TODO: Wait for keypress
            printf("Wait for keypress\n");
        } else if (last_byte == 0x0015) {
            set_delay_timer(cpu, instruction);
        } else if (last_byte == 0x0018) {
            set_sound_timer(cpu, instruction);
        } else if (last_byte == 0x001E) {
            add_index(cpu, instruction);
        } else if (last_byte == 0x0029) {
            load_sprite(cpu, instruction);
        } else if (last_byte == 0x0033) {
            load_bcd(cpu, instruction);
        } else if (last_byte == 0x0055) {
            save_registers(cpu, instruction);
        } else if (last_byte == 0x0065) {
            load_registers(cpu, instruction);
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

void add_value_to_register(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t value = instruction & 0x00FF;
    cpu->registers[reg] += value;
}

void load_register_to_register(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    cpu->registers[reg_x] = cpu->registers[reg_y];
}

void or_registers(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    cpu->registers[reg_x] = value_x | value_y;
}

void and_registers(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    cpu->registers[reg_x] = value_x & value_y;
}

void xor_registers(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    cpu->registers[reg_x] = value_x ^ value_y;
}

void add_registers(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    if (value_x + value_y > 0xFF) {
        cpu->registers[0xF] = 1;
    } else {
        cpu->registers[0xF] = 0;
    }
    cpu->registers[reg_x] = value_x + value_y;
}

void sub_registers(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    if (value_x > value_y) {
        cpu->registers[0xF] = 1;
    } else {
        cpu->registers[0xF] = 0;
    }
    cpu->registers[reg_x] = value_x - value_y;
}

void shift_register_right(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t value = cpu->registers[reg];
    cpu->registers[0xF] = value & 0x01;
    cpu->registers[reg] >>= 1;
}

void sub_registers_reverse(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    uint8_t value_x = cpu->registers[reg_x];
    uint8_t value_y = cpu->registers[reg_y];
    if (value_y > value_x) {
        cpu->registers[0xF] = 1;
    } else {
        cpu->registers[0xF] = 0;
    }
    cpu->registers[reg_x] = value_y - value_x;
}

void shift_register_left(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t value = cpu->registers[reg];
    cpu->registers[0xF] = value & 0x80;
    cpu->registers[reg] <<= 1;
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

void load_index(struct cpu *cpu, uint16_t instruction) {
    uint16_t value = instruction & 0x0FFF;
    cpu->i = value;
}

void jump_offset(struct cpu *cpu, uint16_t instruction) {
    uint16_t address = instruction & 0x0FFF;
    address += cpu->registers[0];
    cpu->pc = address;
}

void random_value(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t mask = instruction & 0x00FF;
    uint8_t value = rand() % 255;
    cpu->registers[reg] = value & mask;
}

void draw(struct cpu *cpu, uint16_t instruction) {
    int reg_x = (instruction & 0x0F00) >> 8;
    int reg_y = (instruction & 0x00F0) >> 4;
    int bytes = instruction & 0x000F;
    uint16_t offset = cpu->i;
    int x = cpu->registers[reg_x];
    int y = cpu->registers[reg_y];
    bool collision = display_draw_sprite(cpu->memory + offset, bytes, x, y);
    if (collision) {
        cpu->registers[0xF] = 1;
    } else {
        cpu->registers[0xF] = 0;
    }
}

void skip_key_pressed(struct cpu *cpu) {
    // TODO: Implement
}

void skip_key_not_pressed(struct cpu *cpu) {
    // TODO: Implement
}

void load_delay_timer(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    cpu->registers[reg] = cpu->dt;
}

void load_key(struct cpu *cpu) {
    // TODO: Implement
}

void set_delay_timer(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    cpu->dt = cpu->registers[reg];
}

void set_sound_timer(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    cpu->st = cpu->registers[reg];
}

void add_index(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    cpu->i += cpu->registers[reg];
}

void load_sprite(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    int digit = cpu->registers[reg];
    cpu->i = CHAR_ADDR + 5 * digit;
}

void load_bcd(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    uint8_t value = cpu->registers[reg];
    cpu->memory[cpu->i] = value / 100;
    cpu->memory[cpu->i + 1] = (value / 10) % 10;
    cpu->memory[cpu->i + 2] = value % 10;
}

void save_registers(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    memcpy(cpu->memory + cpu->i, cpu->registers, reg);
}

void load_registers(struct cpu *cpu, uint16_t instruction) {
    int reg = (instruction & 0x0F00) >> 8;
    memcpy(cpu->registers, cpu->memory + cpu->i, reg);
}

