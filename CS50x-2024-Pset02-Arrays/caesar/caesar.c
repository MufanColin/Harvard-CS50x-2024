#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string plainToCipher(string plaintext, int key);
bool onlyDigits(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (!onlyDigits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: %s\n", plainToCipher(plaintext, key));
    return 0;
}

bool onlyDigits(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

string plainToCipher(string plaintext, int key)
{
    string ciphertext = plaintext;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ('A' + (plaintext[i] - 'A' + key) % 26);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = ('a' + (plaintext[i] - 'a' + key) % 26);
        }
    }
    return ciphertext;
}
