#include <cs50.h>
#include <stdio.h>

int minCoins(int change);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    printf("%d\n", minCoins(change));
    return 0;
}

int minCoins(int change)
{
    int num25, num10, num5, num1;
    if (change == 0)
    {
        return 0;
    }
    num25 = change / 25;
    change -= num25 * 25;
    num10 = change / 10;
    change -= num10 * 10;
    num5 = change / 5;
    change -= num5 * 5;
    num1 = change;
    change = 0;
    return num25 + num10 + num5 + num1;
}
