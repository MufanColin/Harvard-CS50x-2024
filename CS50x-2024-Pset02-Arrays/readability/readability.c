#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);
int calculateIndex(string text);

const float coeffL = 0.0588;
const float coeffS = -0.296;
const float bias = -15.8;

int main(void)
{
    string text = get_string("Text: ");
    // printf("%d\n", calculateIndex(text));
    if (calculateIndex(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (calculateIndex(text) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", calculateIndex(text));
    }
    return 0;
}

int countLetters(string text)
{
    int numLetters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            numLetters++;
        }
    }
    return numLetters;
}

int countWords(string text)
{
    int numWords = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ' || i == n - 1)
        {
            numWords++;
        }
    }
    return numWords;
}

int countSentences(string text)
{
    int numSentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && (i - 1 >= 0 && isalpha(text[i - 1])))
        {
            numSentences++;
        }
    }
    return numSentences;
}

int calculateIndex(string text)
{
    int numLetters = countLetters(text);
    int numWords = countWords(text);
    int numSentences = countSentences(text);
    // return (int) (coeffL * numLetters / numWords * 100 + coeffS * numSentences / numWords * 100 + bias + 0.5);
    return round(coeffL * numLetters / numWords * 100 + coeffS * numSentences / numWords * 100 + bias);
}
