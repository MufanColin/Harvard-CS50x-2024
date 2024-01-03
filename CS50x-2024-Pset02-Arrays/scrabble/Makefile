# Makefile for compiling C source files using C11

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -lcs50

# Source files and executable names
SOURCES = $(wildcard *.c)
EXECUTABLES = $(SOURCES:.c=)

# Default target
all: $(EXECUTABLES)

# Rule to build executables
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove the executables
clean:
	rm -f $(EXECUTABLES)
