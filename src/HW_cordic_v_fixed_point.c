#include <stdio.h>
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
        "blt loop_neg\n\t"

        // y > 0 case
        "asr w4, w11, w3\n\t" // arithmetic right shift on 32 bit registers
        "add w5, w10, w4\n\t"
        "asr w6, w10, w3\n\t"
        "sub w7, w11, w6\n\t"
        "uxtw x3, w3\n\t"                  // zero extend w3 -> x3
        "ldrsh w9, [x13, x3, lsl #1]\n\t"
        "add w12, w12, w9\n\t"
        "mov w10, w5\n\t"
        "mov w11, w7\n\t"
        "b loop_continue\n\t"

        // y <= 0 case
        "loop_neg:\n\t"
        "asr w4, w11, w3\n\t"
        "sub w5, w10, w4\n\t"
        "asr w6, w10, w3\n\t"
        "add w7, w11, w6\n\t"
        "uxtw x3, w3\n\t"                  // zero extend w3 -> x3
        "ldrsh w9, [x13, x3, lsl #1]\n\t"
        "sub w12, w12, w9\n\t"
        "mov w10, w5\n\t"
        "mov w11, w7\n\t"

        "loop_continue:\n\t"
        "add w3, w3, #1\n\t"
        "cmp w3, #15\n\t"
        "blt loop_start\n\t"

        // pack results into one 64-bit register:
        "and w14, w10, #0xFFFF\n\t"
        "and w15, w11, #0xFFFF\n\t"
        "and w16, w12, #0xFFFF\n\t"

        "uxtw x14, w14\n\t"
        "uxtw x15, w15\n\t"
        "uxtw x16, w16\n\t"

        "lsl x15, x15, #16\n\t"
        "lsl x16, x16, #32\n\t"

        "orr x14, x14, x15\n\t"
        "orr x14, x14, x16\n\t"

        "mov %x[out], x14\n\t"

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
          "memory"
    );
    return result;
}

int main() {
    int x = (int)(0.85 * (1 << 13));
    int y = (int)(0.76 * (1 << 13));
    uint64_t packed_result = cordic_custom_instruction(x, y);

    int16_t out_z = (packed_result >> 32) & 0xFFFF;
    int16_t out_y = (packed_result >> 16) & 0xFFFF;
    int16_t out_x = packed_result & 0xFFFF;

    printf("CORDIC Result:\n");
    printf("x: %d\ny: %d\nz: %d\n", out_x, out_y, out_z);

    return 0;
}


// #include <stdio.h>
// #include <stdint.h>

// static const int16_t cordic_z_table[] = {
//     6433, 3218, 1634, 820, 410, 205, 102, 51,
//     26, 13, 6, 3, 1, 1, 0
// };

// // Helper: single CORDIC iteration step in asm
// void cordic_step(int *x, int *y, int *z, int i) {
//     int x_val = *x;
//     int y_val = *y;
//     int z_val = *z;

//     __asm__ __volatile__ (
//         "mov w3, %w[i]\n\t"           // i = loop index
//         "mov w10, %w[x_val]\n\t"      // x local copy
//         "mov w11, %w[y_val]\n\t"      // y local copy
//         "mov w12, %w[z_val]\n\t"      // z accumulator

//         "mov x13, %x[zt]\n\t"         // load address of z_table

//         "cmp w11, #0\n\t"
//         "blt 1f\n\t"

//         // y > 0
//         "asr w4, w11, w3\n\t"
//         "add w5, w10, w4\n\t"
//         "asr w6, w10, w3\n\t"
//         "sub w7, w11, w6\n\t"
//         "uxtw x3, w3\n\t"
//         "ldrsh w9, [x13, x3, lsl #1]\n\t"
//         "add w12, w12, w9\n\t"
//         "mov w10, w5\n\t"
//         "mov w11, w7\n\t"
//         "b 2f\n\t"

//         // y <= 0
//         "1:\n\t"
//         "asr w4, w11, w3\n\t"
//         "sub w5, w10, w4\n\t"
//         "asr w6, w10, w3\n\t"
//         "add w7, w11, w6\n\t"
//         "uxtw x3, w3\n\t"
//         "ldrsh w9, [x13, x3, lsl #1]\n\t"
//         "sub w12, w12, w9\n\t"
//         "mov w10, w5\n\t"
//         "mov w11, w7\n\t"

//         "2:\n\t"

//         // Return updated values to C variables
//         "mov %w[x_val], w10\n\t"
//         "mov %w[y_val], w11\n\t"
//         "mov %w[z_val], w12\n\t"

//         : [x_val] "+r" (x_val),
//           [y_val] "+r" (y_val),
//           [z_val] "+r" (z_val)
//         : [i] "r" (i),
//           [zt] "r" (cordic_z_table)
//         : "w3", "w4", "w5", "w6", "w7", "w9", "x3", "x13", "w10", "w11", "w12"
//     );

//     *x = x_val;
//     *y = y_val;
//     *z = z_val;
// }

// uint64_t cordic_custom_instruction_debug(int x, int y) {
//     int z = 0;
//     printf("Iter | x     | y     | z\n");
//     printf("-------------------------\n");
//     for (int i = 0; i < 15; ++i) {
//         cordic_step(&x, &y, &z, i);
//         printf("%3d | %5d | %5d | %5d\n", i, x, y, z);
//     }

//     // pack x,y,z into 64-bit output as before
//     uint64_t result = 0;
//     uint64_t ux = (uint16_t)(x & 0xFFFF);
//     uint64_t uy = (uint16_t)(y & 0xFFFF);
//     uint64_t uz = (uint16_t)(z & 0xFFFF);

//     result = (ux << 32) | (uy << 16) | uz;
//     return result;
// }

// int main() {
//     int x = (int)(0.85 * (1 << 13));
//     int y = (int)(0.76 * (1 << 13));
//     uint64_t packed_result = cordic_custom_instruction_debug(x, y);

//     int16_t out_x = (packed_result >> 32) & 0xFFFF;
//     int16_t out_y = (packed_result >> 16) & 0xFFFF;
//     int16_t out_z = packed_result & 0xFFFF;

//     printf("CORDIC Result:\n");
//     printf("x: %d\ny: %d\nz: %d\n", out_x, out_y, out_z);

//     return 0;
// }