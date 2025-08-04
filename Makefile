# Compiler and Flags
CC = gcc
LDFLAGS = -lm
CFLAGS = -Wall -Wextra -std=c99 -Iinclude


# Targets
TARGETS = cordic_run hw_cordic_run

# Source Files
CORDIC_SRC = src/cordic_v_fixed_point.c
HW_CORDIC_SRC = src/HW_cordic_v_fixed_point.c
HORIZ_SRC = src/horizontal_firmware_simulation.c

# Default target
all: $(TARGETS)

# Build cordic_run
cordic_run: main.c $(CORDIC_SRC) $(HORIZ_SRC)
	$(CC) $(CFLAGS) -o $@ main.c $(CORDIC_SRC) $(HORIZ_SRC) $(LDFLAGS)

# Build hw_cordic_run
hw_cordic_run: $(HW_CORDIC_SRC)
	$(CC) $(CFLAGS) -o $@ $(HW_CORDIC_SRC) $(LDFLAGS)

# Clean
clean:
	rm -f $(OBJS) $(TARGETS) cordic_benchmark cordic_benchmark_firmware

# Benchmarks
benchmark: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c $(LDFLAGS)

# Benchmarks
benchmark_firmware: cordic_benchmark_firmware.c src/horizontal_firmware_simulation.c
	$(CC) $(CFLAGS) -o cordic_benchmark_firmware cordic_benchmark_firmware.c src/horizontal_firmware_simulation.c $(LDFLAGS)