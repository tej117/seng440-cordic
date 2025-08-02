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
    int32_t x_temp_1, y_temp_1, z_temp;
    int32_t x_temp_2, y_temp_2;

    register i;
    x_temp_1 = *p_x;
    y_temp_1 = *p_y;
    z_temp = 0;


    // Iteration 0
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 0);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 0);
            z_temp += cordic_z_table[0];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 0);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 0);
            z_temp -= cordic_z_table[0];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 1
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 1);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 1);
            z_temp += cordic_z_table[1];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 1);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 1);
            z_temp -= cordic_z_table[1];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 2
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 2);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 2);
            z_temp += cordic_z_table[2];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 2);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 2);
            z_temp -= cordic_z_table[2];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 3
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 3);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 3);
            z_temp += cordic_z_table[3];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 3);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 3);
            z_temp -= cordic_z_table[3];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 4
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 4);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 4);
            z_temp += cordic_z_table[4];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 4);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 4);
            z_temp -= cordic_z_table[4];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 5
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 5);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 5);
            z_temp += cordic_z_table[5];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 5);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 5);
            z_temp -= cordic_z_table[5];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 6
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 6);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 6);
            z_temp += cordic_z_table[6];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 6);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 6);
            z_temp -= cordic_z_table[6];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 7
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 7);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 7);
            z_temp += cordic_z_table[7];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 7);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 7);
            z_temp -= cordic_z_table[7];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 8
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 8);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 8);
            z_temp += cordic_z_table[8];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 8);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 8);
            z_temp -= cordic_z_table[8];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 9
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 9);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 9);
            z_temp += cordic_z_table[9];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 9);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 9);
            z_temp -= cordic_z_table[9];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 10
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 10);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 10);
            z_temp += cordic_z_table[10];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 10);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 10);
            z_temp -= cordic_z_table[10];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 11
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 11);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 11);
            z_temp += cordic_z_table[11];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 11);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 11);
            z_temp -= cordic_z_table[11];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 12
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 12);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 12);
            z_temp += cordic_z_table[12];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 12);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 12);
            z_temp -= cordic_z_table[12];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 13
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 13);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 13);
            z_temp += cordic_z_table[13];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 13);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 13);
            z_temp -= cordic_z_table[13];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

    // Iteration 14
    if( y_temp_1 > 0) 
        {
            x_temp_2 = x_temp_1 + (y_temp_1 >> 14);
            y_temp_2 = y_temp_1 - (x_temp_1 >> 14);
            z_temp += cordic_z_table[14];
        }
        else 
        {
            x_temp_2 = x_temp_1 - (y_temp_1 >> 14);
            y_temp_2 = y_temp_1 + (x_temp_1 >> 14);
            z_temp -= cordic_z_table[14];
        }
        
    x_temp_1 = x_temp_2;
    y_temp_1 = y_temp_2;

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
