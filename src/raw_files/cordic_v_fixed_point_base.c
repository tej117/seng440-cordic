#include <stdio.h>
#include <stdint.h>

#include "cordic.h"

const int16_t cordic_z_table[15] = { 6433, 3218, 1634, 820, 410, 205, 102, 51, 26, 13, 6, 3, 1, 1, 0};

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
    }
    
    *p_x = x_temp_1;
    *p_y = y_temp_1;
    *p_z = z_temp;
}