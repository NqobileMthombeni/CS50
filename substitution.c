#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_valid_key(string key);
char substitute_char(char plain_char, string key);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (!is_valid_key(key))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitute_char(plaintext[i], key));
    }

    printf("\n");
    return 0;
}

bool is_valid_key(string key)
{
    int length = strlen(key);
    if (length != 26)
    {
        return false;
    }

    bool char_seen[26] = {false};

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';

        if (char_seen[index])
        {
            return false;
        }

        char_seen[index] = true;
    }

    return true;
}

char substitute_char(char plain_char, string key)
{
    if (isalpha(plain_char))
    {
        bool is_upper = isupper(plain_char);
        int index = toupper(plain_char) - 'A';


        char cipher_char = key[index];
        if (is_upper)
        {
            return toupper(cipher_char);
        }
        else
        {
            return tolower(cipher_char);
        }
    }
    else
    {

        return plain_char;
    }
}
