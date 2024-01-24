from cs50 import get_int

while True:
    try:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break
    except ValueError:
        pass

for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1), end="")
    print()
