#include <stdio.h>
#include <stdint.h>

#include "cordic.h"

const int16_t cordic_z_table[15] = { 6433, 3218, 1634, 820, 410, 205, 102, 51, 26, 13, 6, 3, 1, 1, 0};

#define CORDIC_NUM_ITERATIONS 15 // 15 iterations are needed

void cordic_v_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z)
{
    int32_t x_temp_1 = *p_x;
    int32_t y_temp_1 = *p_y;
    int32_t z_temp   = 0;
    int32_t x_shift, y_shift, z_angle;
    int i;
    
    /** Prologue: prepare last loop iteration **/
    y_shift = y_temp_1 >> (CORDIC_NUM_ITERATIONS - 1);
    x_shift = x_temp_1 >> (CORDIC_NUM_ITERATIONS - 1);
    z_angle = cordic_z_table[CORDIC_NUM_ITERATIONS - 1];
    
    /** Main loop: runs from i = 13 to 1, processing 2 iterations per loop **/
    for (i = CORDIC_NUM_ITERATIONS - 2; i >= 1; i -= 2)
    {
        // First iteration (i)
        if (y_temp_1 > 0)
        {
            x_temp_1 = x_temp_1 + y_shift;
            y_temp_1 = y_temp_1 - x_shift;
            z_temp   = z_temp + z_angle;
        }
        else
        {
            x_temp_1 = x_temp_1 - y_shift;
            y_temp_1 = y_temp_1 + x_shift;
            z_temp   = z_temp - z_angle;
        }
        
        // Prepare values for next iteration (i-1)
        y_shift = y_temp_1 >> (i - 1);
        x_shift = x_temp_1 >> (i - 1);
        z_angle = cordic_z_table[i - 1];
        
        // Second iteration (i-1)
        if (y_temp_1 > 0)
        {
            x_temp_1 = x_temp_1 + y_shift;
            y_temp_1 = y_temp_1 - x_shift;
            z_temp   = z_temp + z_angle;
        }
        else
        {
            x_temp_1 = x_temp_1 - y_shift;
            y_temp_1 = y_temp_1 + x_shift;
            z_temp   = z_temp - z_angle;
        }
        
        // Prepare values for next loop iteration (i-2)
        if (i - 2 >= 0)
        {
            y_shift = y_temp_1 >> (i - 2);
            x_shift = x_temp_1 >> (i - 2);
            z_angle = cordic_z_table[i - 2];
        }
    }
    
    /** Handle remaining iteration if CORDIC_NUM_ITERATIONS is odd **/
    if (i == 0)
    {
        if (y_temp_1 > 0)
        {
            x_temp_1 = x_temp_1 + y_shift;
            y_temp_1 = y_temp_1 - x_shift;
            z_temp   = z_temp + z_angle;
        }
        else
        {
            x_temp_1 = x_temp_1 - y_shift;
            y_temp_1 = y_temp_1 + x_shift;
            z_temp   = z_temp - z_angle;
        }
    }
    
    *p_x = x_temp_1;
    *p_y = y_temp_1;
    *p_z = z_temp;
}