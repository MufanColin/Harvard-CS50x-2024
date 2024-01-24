def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass


def main():
    x = get_int("x: ")
    y = get_int("y: ")
    print(f"x + y = {x + y}")


main()
