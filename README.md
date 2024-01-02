# Harvard-CS50x-2024

My Harvard CS50x-2024 study journey.

## 注意事项

如果想在本地运行含有 `#include <cs50.h>` 的代码，可以从[这个链接](https://github.com/cs50/libcs50)下载 `libcs50`，并按照上面的提示进行安装。

### Mac OS

1. 在 .zshrc 中添加 `export DYLD_LIBRARY_PATH=/usr/local/lib`。

2. 在 Makefile 中添加 `-lcs50`，下面给出了一个可行的 Makefile。

    ```makefile
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
    ```