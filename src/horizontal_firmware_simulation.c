#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "cordic_horizontal_firmware.h"

void execute_instruction(Instruction *inst, RegisterFile *in, RegisterFile *out) 
{
    switch (inst->type) 
    {
        case ADD:
            if (inst->dest == 'x') out->x = in->x + (in->y >> inst->shift_amount);
            else if (inst->dest == 'y') out->y = in->y + (in->x >> inst->shift_amount);
            break;

        case SUB:
            if (inst->dest == 'x') out->x = in->x - (in->y >> inst->shift_amount);
            else if (inst->dest == 'y') out->y = in->y - (in->x >> inst->shift_amount);
            break;

        case UPDATE_Z:
            out->z = in->z + inst->z_table_val;
            break;

        case NOP:
        default:
            break;
    }
}

void simulate_cordic_cycle(RegisterFile *regs, const int16_t z_table[]) 
{
    for (int i = 0; i < NUM_ITERATIONS; ++i) 
    {
        RegisterFile prev = *regs;
        RegisterFile next = prev;

        // Direction depends on sign of y
        int dir = (prev.y > 0) ? 1 : -1;

        Instruction slot[NUM_ISSUE_SLOTS];
        Instruction z_inst;

        if (dir == 1) {
            slot[0] = (Instruction){ .type = ADD, .dest = 'x', .shift_amount = i };
            slot[1] = (Instruction){ .type = SUB, .dest = 'y', .shift_amount = i };
            z_inst = (Instruction){ .type = UPDATE_Z, .z_table_val = z_table[i] };
        } else {
            slot[0] = (Instruction){ .type = SUB, .dest = 'x', .shift_amount = i };
            slot[1] = (Instruction){ .type = ADD, .dest = 'y', .shift_amount = i };
            z_inst = (Instruction){ .type = UPDATE_Z, .z_table_val = -z_table[i] };
        }

        execute_instruction(&slot[0], &prev, &next);
        execute_instruction(&slot[1], &prev, &next);
        execute_instruction(&z_inst, &prev, &next);

        *regs = next;
    }
}