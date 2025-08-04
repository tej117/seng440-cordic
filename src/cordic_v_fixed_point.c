// Software Optimized CORDIC Code 

#include <stdio.h>
#include <stdint.h>

#include "cordic.h"

/*
Applied Q2.13 format: (atan(2^-i) * 2^13) to the following table.

const int16_t cordic_z_table[15] = { 25735, 15192, 8027, 4074, 2045, 1023,
511, 255, 127, 63, 31, 15, 7, 3, 1};
*/

const int16_t cordic_z_table[15] = { 6433, 3218, 1634, 820, 410, 205, 102, 51, 26, 13, 6, 3, 1, 1, 0 };

#define CORDIC_NUM_ITERATIONS 15 // 15 iterations are needed

void cordic_v_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z)
{
    register x_temp_1, y_temp_1, z_temp;
    register x_temp_2, y_temp_2;
    register i;

    x_temp_1 = *p_x;
    y_temp_1 = *p_y;
    z_temp = 0;

    for( i=0; i<CORDIC_NUM_ITERATIONS; i++) 
    { 
	    if( y_temp_1 > 0) 
        {
	        x_temp_2 = x_temp_1 + (y_temp_1 >> i);
	        y_temp_2 = y_temp_1 - (x_temp_1 >> i);
	        z_temp += cordic_z_table[i];
        }
        else 
        {
	        x_temp_2 = x_temp_1 - (y_temp_1 >> i);
	        y_temp_2 = y_temp_1 + (x_temp_1 >> i);
	        z_temp -= cordic_z_table[i];
        }
        
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;

        printf("%4d | %6d | %6d | %6d\n", i, x_temp_1, y_temp_1, z_temp);
    }
    
    *p_x = x_temp_1;
    *p_y = y_temp_1;
    *p_z = z_temp;
}

