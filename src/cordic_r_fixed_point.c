#include <stdio.h>
#include <stdint.h>

#include "cordic.h"

const int16_t cordic_z_table[15] = { 25735, 15192, 8027, 4074, 2045, 1023,
511, 255, 127, 63, 31, 15, 7, 3, 1};

#define CORDIC_NUM_ITERATIONS 15 // 15 iterations are needed

void cordic_r_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z)
{

    int32_t x = *p_x;
    int32_t y = *p_y;
    int32_t z = *p_z;

    int i;

    for( i=0; i<CORDIC_NUM_ITERATIONS; i++) 
    { 
        
    }
    
    *p_x = x;
    *p_y = y;
    *p_z = z;
}