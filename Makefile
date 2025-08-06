# Compiler and Flags
CC = gcc
LDFLAGS = -lm
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -march=armv8-a


# Targets
TARGETS = cordic_run inline_debugger

# Source Files
CORDIC_SRC = src/cordic_v_fixed_point.c
HORIZ_SRC = src/horizontal_firmware_simulation.c
INLINE_DEBUGGER_SRC = src/cordic_inline_debugger.c
ASM_CORDIC = asm/cordic_custom_instruction.c

# Default target
all: $(TARGETS)

# Build cordic_run
cordic_run: main.c $(CORDIC_SRC) $(HORIZ_SRC) $(ASM_CORDIC)
	$(CC) $(CFLAGS) -o $@ main.c $(CORDIC_SRC) $(HORIZ_SRC) $(ASM_CORDIC) $(LDFLAGS)

# Build inline_debugger
inline_debugger: $(INLINE_DEBUGGER_SRC)
	$(CC) $(CFLAGS) -o $@ $(INLINE_DEBUGGER_SRC) $(LDFLAGS)

# Clean
clean:
	rm -f $(OBJS) $(TARGETS) cordic_benchmark cordic_benchmark_firmware cordic_benchmark_inline

# Benchmark - Software CORDIC
benchmark: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c $(LDFLAGS)

# Benchmark - Firmware CORDIC
benchmark_firmware: cordic_benchmark_firmware.c src/horizontal_firmware_simulation.c
	$(CC) $(CFLAGS) -o cordic_benchmark_firmware cordic_benchmark_firmware.c src/horizontal_firmware_simulation.c $(LDFLAGS)

# Benchmark - ASM CORDIC
cordic_benchmark_inline: cordic_benchmark_inline.c $(ASM_CORDIC)
	$(CC) $(CFLAGS) -o $@ cordic_benchmark_inline.c $(ASM_CORDIC) $(LDFLAGS)