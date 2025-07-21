#ifndef CORDIC_H
#define CORDIC_H

#include <stdint.h>

extern const int16_t cordic_z_table[15];

void cordic_v_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z);
void cordic_r_fixed_point(int32_t *p_x, int32_t *p_y, int32_t *p_z);

#endif // CORDIC_H
