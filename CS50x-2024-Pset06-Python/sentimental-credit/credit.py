import re
from cs50 import get_int


def check_sum(number):
    number_str = str(number)
    n = len(number_str)
    sum = 0
    for i in range(n - 1, -1, -2):
        sum += int(number_str[i])
    for i in range(n - 2, -1, -2):
        sum += int(number_str[i]) * 2 - 9 * (number_str[i] > "4")

    return True if sum % 10 == 0 else False


def basic_check(number):
    number_str = str(number)
    if re.fullmatch(r'^3[4,7].{13}$', number_str) and check_sum(number):
        print("AMEX")
    elif re.fullmatch(r'^5[12345].{14}$', number_str) and check_sum(number):
        print("MASTERCARD")
    elif re.fullmatch(r'^4(.{12}|.{15})$', number_str) and check_sum(number):
        print("VISA")
    else:
        print("INVALID")


def main():
    # AMEX: start with 34 or 37, 15-digit numbers
    # MASTERCARD: start with 51, 52, 53, 54, or 55, 16-digit number
    # VISA: 13 and 16 digits, start with 4
    number = get_int("Number: ")
    basic_check(number)


main()
