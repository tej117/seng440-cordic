#include <stdint.h>

uint64_t cordic_custom_instruction(int x, int y) {
    static const int16_t cordic_z_table[] = {
        6433, 3218, 1634, 820, 410, 205, 102, 51,
        26, 13, 6, 3, 1, 1, 0
    };

    uint64_t result;
    __asm__ __volatile__ (
        "mov w3, wzr\n\t"         // i = 0
        "mov w10, %w[xin]\n\t"    // x local copy
        "mov w11, %w[yin]\n\t"    // y local copy
        "mov w12, wzr\n\t"        // z accumulator

        "mov x13, %[zt]\n\t"      // load address of z_table

        "loop_start:\n\t"
        "cmp w11, #0\n\t"
        "bgt loop_pos\n\t"
        "beq loop_zero\n\t"
        "blt loop_neg\n\t"

        "loop_zero:\n\t"
        "b loop_neg\n\t"  // or b loop_pos, depending on your logic

        "loop_neg:\n\t"
        "asr w4, w11, w3\n\t"
        "sub w5, w10, w4\n\t"
        "asr w6, w10, w3\n\t"
        "add w7, w11, w6\n\t"
        "mov w17, w3\n\t"
        "uxtw x17, w17\n\t"
        "ldrsh w9, [x13, x17, lsl #1]\n\t"
        "sub w12, w12, w9\n\t"
        "mov w10, w5\n\t"
        "mov w11, w7\n\t"
        "b loop_continue\n\t"

        "loop_pos:\n\t"
        "asr w4, w11, w3\n\t"
        "add w5, w10, w4\n\t"
        "asr w6, w10, w3\n\t"
        "sub w7, w11, w6\n\t"
        "mov w17, w3\n\t"
        "uxtw x17, w17\n\t"
        "ldrsh w9, [x13, x17, lsl #1]\n\t"
        "add w12, w12, w9\n\t"
        "mov w10, w5\n\t"
        "mov w11, w7\n\t"
        "b loop_continue\n\t"

        "loop_continue:\n\t"
        "add w3, w3, #1\n\t"
        "cmp w3, #15\n\t"
        "blt loop_start\n\t"

        // pack results into one 64-bit register:
        "sxtw x14, w10\n\t"
        "sxtw x15, w11\n\t"
        "sxtw x16, w12\n\t"

        "lsl x15, x15, #16\n\t"
        "lsl x16, x16, #32\n\t"

        "orr x14, x14, x15\n\t"
        "orr x14, x14, x16\n\t"

        "mov %0, x14\n\t"

        :
          [out] "=r" (result)
        :
          [xin] "r" (x),
          [yin] "r" (y),
          [zt] "r" (cordic_z_table)
        :
        "x0", "x1", "x2", "x3", "x13",
        "w3", "w4", "w5", "w6", "w7", "w9",
        "w10", "w11", "w12", "w14", "w15", "w16",
        "x14", "x15", "x16",
        "memory"
    );
    return result;
}