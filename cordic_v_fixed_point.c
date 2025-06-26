#include <stdio.h>
#include <stdint.h>

static const int16_t cordic_z_table[15] = { 25735, 15192, 8027, 4074, 2045, 1023,
511, 255, 127, 63, 31, 15, 7, 3, 1};

#define CORDIC_NUM_ITERATIONS 15 // 15 iterations are needed

void cordic_v_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z)
{
    int x_temp_1, y_temp_1, z_temp;
    int x_temp_2, y_temp_2;
    int i;
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

/** void HW_cordic_V_fixed_point( int *x, int *y, int *z) {
    register int x_temp, y_temp, z_temp;
    register int xz_temp;
    x_temp = *x;
    y_temp = *y;
    __asm__ __volatile__ ( "CORDIC_V %0, %1, %2" : "=r" (xz_temp) : "r" (x_temp), "r" (y_temp));
    *x = xz_temp >> 16;
    z_temp = (xz_temp << 16) >> 16; // what is this ?!
    *z = z_temp;
}*/
