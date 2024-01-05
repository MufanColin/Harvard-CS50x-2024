# Source files and executable names
SOURCES = $(wildcard *.c)

EXECUTABLES = $(SOURCES:.c=)

filter:
	clang -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o filter filter.c helpers.c

# Clean target to remove the executables
clean:
	rm -f $(EXECUTABLES)
