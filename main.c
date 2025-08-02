#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "cordic.h"
#include "cordic_horizontal_firmware.h"

void verify(int32_t x_i_init, int32_t y_i_init, int32_t z_i_init, int32_t x_i, int32_t y_i, int32_t z_i) 
{
    double x_d_init, y_d_init, z_d_init, x_d, y_d, z_d;
    x_d_init = (double)x_i_init / ( 1 << 13); // float image of x_i_init (Q2.13)
    y_d_init = (double)y_i_init / ( 1 << 13); // float image of y_i_init (Q2.13)
    z_d_init = (double)z_i_init / ( 1 << 13); // float image of z_i_init (Q2.13)

    printf( "x_i_init = %5i\tx_d_init = %f\n", x_i_init, x_d_init);
    printf( "y_i_init = %5i\ty_d_init = %f\n", y_i_init, y_d_init);
    printf( "z_i_init = %5i\tz_d_init = %f (rad)\n\n", z_i_init, z_d_init);
    
    x_d = (double)x_i / (1 << 13); // Q2.13
    y_d = (double)y_i / (1 << 13); // Q2.13
    z_d = (double)z_i / (1 << 13); // Q2.13
    
    printf( "x_i_calc = %5i\tx_d_calc = %f\n", x_i, x_d);
    printf( "y_i_calc = %5i\ty_d_calc = %f\n", y_i, y_d);
    printf( "z_i_calc = %5i\tz_d_calc = %f (rad)\n\n", z_i, z_d);
    printf( "Modulus input = SQRT(x_d_init^2 + y_d_init^2) = %f\n",
    sqrt(x_d_init*x_d_init+y_d_init*y_d_init));
    printf( "Modulus output = SQRT(x_d^2 + y_d^2) = %f\n",
    sqrt(x_d*x_d+y_d*y_d));

} /** END of verify() function */

void execute_cordic_vector_fixed_point() {
    int x_i_init, y_i_init, z_i_init; // initial 
    int x_i, y_i, z_i; // integer (fixed-point) variables
    x_i = (x_i_init = (int)(0.85 * (1 << 13))); // Adjusted for Q2.13
    y_i = (y_i_init = (int)(0.76 * (1 << 13))); // Adjusted for Q2.13
    z_i_init = 0; // In vectoring mode, should be 0

    printf( "Vectoring CORDIC:\n\n");
    cordic_v_fixed_point( &x_i, &y_i, &z_i);
    verify( x_i_init, y_i_init, z_i_init, x_i, y_i, z_i);
}

void execute_horizontal_firmware_simulation() {
    RegisterFile regs = {
        .x = (int32_t)(0.85 * (1 << 13)), // Q2.13
        .y = (int32_t)(0.85 * (1 << 13)),
        .z = 0
    };

    simulate_cordic_cycle(&regs, cordic_z_table);

    printf("\nFinal values:\n");
    printf("x = %d\ny = %d\nz = %d\n", regs.x, regs.y, regs.z);
}

int main( void) 
{
    execute_cordic_vector_fixed_point();


    // execute_horizontal_firmware_simulation();
    
    return 0;
} /** END of main() function */
