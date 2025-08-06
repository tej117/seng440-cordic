#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define FIXED_POINT_SCALE (1 << 15)
#define NUM_RUNS 1000

uint64_t cordic_custom_instruction(int x, int y);

double get_time_ms() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}

int main(void) {
    FILE *fp = fopen("cordic_benchmark_results.csv", "w");
    if (!fp) {
        perror("Failed to open output CSV file");
        return 1;
    }

    fprintf(fp, "Run,Time_ms\n");

    double total_time = 0.0;

    for (int i = 0; i < NUM_RUNS; i++) {
        int x = (int)(0.85 * (1 << 13));
        int y = (int)(0.76 * (1 << 13));


        double start = get_time_ms();
        
        cordic_custom_instruction(x, y);

        double end = get_time_ms();

        double elapsed = end - start;
        total_time += elapsed;

        fprintf(fp, "%d,%.6f\n", i + 1, elapsed);
    }

    fclose(fp);

    printf("Benchmark complete.\n");
    printf("Output written to: cordic_benchmark_results.csv\n");
    printf("Average time: %.6f ms over %d runs\n", total_time / NUM_RUNS, NUM_RUNS);

    return 0;
}
