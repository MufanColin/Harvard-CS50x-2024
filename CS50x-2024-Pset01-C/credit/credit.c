#include <cs50.h>
#include <stdio.h>
#include <string.h>

int specialSumOfOddDigits(long number);
int sumOfEvenDigits(long number);
int leftMostDigit(long number);
int leftTwoDigits(long number);
int lengthOfNumber(long number);
string validationCheck(long number);

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    printf("%s\n", validationCheck(number));
    return 0;
}

int specialSumOfOddDigits(long number)
{
    int sum = 0;
    while (number > 0)
    {
        number /= 10;
        if (number % 10 * 2 < 10)
        {
            sum += (number % 10) * 2;
        }
        else
        {
            sum += (1 + (number % 10 - 5) * 2);
        }
        number /= 10;
    }
    return sum;
}

int sumOfEvenDigits(long number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 100;
    }
    return sum;
}

int leftMostDigit(long number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    return number;
}

int leftTwoDigits(long number)
{
    // tiny issue for number < 10 but nevermind
    while (number >= 100)
    {
        number /= 10;
    }
    return number;
}

int lengthOfNumber(long number)
{
    int len = 0;
    if (number == 0)
    {
        return 1;
    }
    while (number > 0)
    {
        len++;
        number /= 10;
    }
    return len;
}

string validationCheck(long number)
{
    int x = specialSumOfOddDigits(number);
    int y = sumOfEvenDigits(number);
    if ((x + y) % 10 == 0)
    {
        if (lengthOfNumber(number) == 15 && (leftTwoDigits(number) == 34 || leftTwoDigits(number) == 37))
        {
            return "AMEX";
        }
        else if (lengthOfNumber(number) == 16 &&
                 (leftTwoDigits(number) == 51 || leftTwoDigits(number) == 52 || leftTwoDigits(number) == 53 ||
                  leftTwoDigits(number) == 54 || leftTwoDigits(number) == 55))
        {
            return "MASTERCARD";
        }
        else if ((lengthOfNumber(number) == 16 || lengthOfNumber(number) == 13) && leftMostDigit(number) == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}
