#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int N = 26;
bool visited[N];

bool validKey(string key);
string plainToCipher(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
    }

    if (!validKey(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: %s\n", plainToCipher(plaintext, argv[1]));

    return 0;
}

bool validKey(string key)
{
    int n = strlen(key);
    if (n != 26)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(key[i]) || visited[tolower(key[i]) - 'a'])
        {
            return false;
        }
        visited[tolower(key[i]) - 'a'] = true;
    }
    return true;
}

string plainToCipher(string plaintext, string key)
{
    string ciphertext = plaintext;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = toupper(key[plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        }
    }
    return ciphertext;
}
