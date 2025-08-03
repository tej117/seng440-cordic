#ifndef CORDIC_HORIZONTAL_FIRMWARE_H
#define CORDIC_HORIZONTAL_FIRMWARE_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_ISSUE_SLOTS 2
#define NUM_ITERATIONS 15

typedef enum {
    NOP,
    ADD,
    SUB,
    UPDATE_Z
} InstructionType;

typedef struct {
    InstructionType type;
    char dest;
    char src1;
    char src2;
    int shift_amount;
    int z_table_val;
    bool issued;
    bool ready;
} Instruction;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
} RegisterFile;

void simulate_cordic_cycle(RegisterFile *regs, const int16_t z_table[]);

#endif // CORDIC_HORIZONTAL_FIRMWARE_H