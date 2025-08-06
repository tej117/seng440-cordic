# Embedded Systems Project - CORDIC

This project we are building CORDIC in C that we run on a Raspberry Pi 4b.
The purpose of this project is to gain a strong understanding of embedded-level math optimizations and how low-level systems solve high-level problems like trigonometric computation.

# Code Base

When looking at `src\` it has cordic_v_fixed_point.c which is the most optimized software version of CORDIC. And when going into `src\raw_files\`, these files contain other optimization versions (and the baseline version) which were tested and benchmarked to find the most optimal solution.

`src\vhdl_files` contains the design of CORDIC in VHDL.

`src\benchmark` contains the benchmark files that were used to test performance of the different optimization levels for CORDIC.