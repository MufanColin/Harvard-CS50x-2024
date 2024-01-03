#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int wordToPoints(string word);

int main(void)
{
    string wordByPlayer1 = get_string("Player 1: ");
    string wordByPlayer2 = get_string("Player 2: ");
    int pointsOfPlayer1 = wordToPoints(wordByPlayer1);
    int pointsOfPlayer2 = wordToPoints(wordByPlayer2);

    if (pointsOfPlayer1 > pointsOfPlayer2)
    {
        printf("Player 1 wins!\n");
    }
    else if (pointsOfPlayer1 < pointsOfPlayer2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}

int wordToPoints(string word)
{
    int total = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            total += points[tolower(word[i]) - 'a'];
        }
    }
    return total;
}
