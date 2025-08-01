# Compiler and Flags
CC = gcc
BUILD ?= opt # Set BUILD=noopt to use -O0
LDFLAGS = -lm

# Optimization flags depending on BUILD
ifeq ($(BUILD),noopt)
    CFLAGS = -Wall -Wextra -std=c99 -O0 -Iinclude
else
    CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude
endif

# Main Program and Files
TARGET = cordic_run
SRCS = main.c src/cordic_v_fixed_point.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET) cordic_benchmark

# Benchmarks
benchmark: BUILD=opt
benchmark: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c $(LDFLAGS)

benchmark_noopt: BUILD=noopt
benchmark_noopt: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c $(LDFLAGS)

# Optional: run the main app with -O0
all_noopt: BUILD=noopt
all_noopt: $(TARGET)
