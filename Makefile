
CC = gcc # Compiler
CFLAGS = -Wall -Wextra -std=c99 -O2 # Compiler Flags
LDFLAGS = -lm # Library Flags

TARGET = cordic_run # Output File Name
SRCS = main.c cordic_v_fixed_point.c # Files to Compile
OBJS = $(SRCS:.c=.o) # Compile Setup

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)


