# Compiler and Flags
CC = gcc
LDFLAGS = -lm
CFLAGS = -Wall -Wextra -std=c99 -Iinclude


# Targets
TARGETS = cordic_run

# Source Files
CORDIC_SRC = src/cordic_v_fixed_point.c
HORIZ_SRC = src/horizontal_firmware_simulation.c

# Default target
all: $(TARGETS)

# Build cordic_run
cordic_run: main.c $(CORDIC_SRC) $(HORIZ_SRC)
	$(CC) $(CFLAGS) -o $@ main.c $(CORDIC_SRC) $(HORIZ_SRC) $(LDFLAGS)

# Clean
clean:
	rm -f $(OBJS) $(TARGET) cordic_benchmark

# Benchmarks
benchmark: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c $(LDFLAGS)