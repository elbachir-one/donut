# Makefile for the Spinning 3D Donut Program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2 -lm

# Executable name
TARGET = donut

# Source files
SRCS = donut.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build directory
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
