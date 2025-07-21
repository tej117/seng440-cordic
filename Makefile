
CC = gcc # Compiler
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude # Compiler Flags
LDFLAGS = -lm # Library Flags

TARGET = cordic_run # Output File Name
SRCS = main.c src/cordic_v_fixed_point.c # Files to Compile
OBJS = $(SRCS:.c=.o) # Compile Setup

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

benchmark: cordic_benchmark.c src/cordic_v_fixed_point.c
	$(CC) $(CFLAGS) -o cordic_benchmark cordic_benchmark.c src/cordic_v_fixed_point.c -lm

