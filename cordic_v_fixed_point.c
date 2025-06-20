int z_table[15];
void cordic_V_fixed_point( int *x, int *y, int *z) {
    int x_temp_1, y_temp_1, z_temp;
    int x_temp_2, y_temp_2;
    int i;
    x_temp_1 = *x;
    y_temp_1 = *y;
    z_temp = 0;

    for( i=0; i<15; i++) { /* 15 iterations are needed */
        if( y_temp_1 > 0) {
        x_temp_2 = x_temp_1 + (y_temp_1 >> i);
        y_temp_2 = y_temp_1 - (x_temp_1 >> i);
        z_temp += z_table[i];
        }
        else {
        x_temp_2 = x_temp_1 - (y_temp_1 >> i);
        y_temp_2 = y_temp_1 + (x_temp_1 >> i);
        z_temp -= z_table[i];
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }
    
    *x = x_temp_1;
    *y = y_temp_1;
    *z = z_temp;
}

void HW_cordic_V_fixed_point( int *x, int *y, int *z) {
    register int x_temp, y_temp, z_temp;
    register int xz_temp;
    x_temp = *x;
    y_temp = *y;
    __asm__ __volatile__ ( "CORDIC_V %0, %1, %2" : "=r" (xz_temp) : "r" (x_temp), "r" (y_temp));
    *x = xz_temp >> 16;
    z_temp = (xz_temp << 16) >> 16; /* what is this ?! */
    *z = z_temp;
}