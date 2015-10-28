#include <iostream>
#include <string.h>

using namespace std;

char* esPalindrome(char* cadena, int i)
{
    if(strstr(cadena, " ") != NULL)
    {
        char* nueva = new char [100];
        char* copia = new char [100];
        char* temp;

        strcpy(copia, cadena);

        temp = strtok(copia, " ");
        strcpy(nueva, temp);
        strcat(nueva, strpbrk(cadena, " ")+1);

        return esPalindrome(nueva, i);
    }

    else
    {
        if(i >= strlen(cadena))
        {
            return "Es Palindrome";
        }
        else
        {
            if(*(cadena + i) == *((cadena + (strlen(cadena) - 1))- i))
            {
                return esPalindrome(cadena, i+1);
            }
            else
            {
                return "No es Palindrome";
            }
        }
    }
}

int main()
{
    cout << esPalindrome("añora la roña", 0);
}
