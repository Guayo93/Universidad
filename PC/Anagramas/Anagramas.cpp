#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

char* revesarCadena(char* cadena, int i, int j)
{
    if(i <= (strlen(cadena)/2) && j >= (strlen(cadena)/2))
    {
        char temp = *(cadena + i);
        *(cadena + i) = *(cadena + j);
        *(cadena + j) = temp;

        i++;
        j--;
        return revesarCadena(cadena, i, j);
    }
    else
    {
        return cadena;
    }
}

void anagramas(char* cadena, char* cadTemp, int cont, int posCambio, char* orig)
{
    if(cont < (strlen(cadena) - 1))
    {
        if(posCambio >= 0)
        {
            char temp = *(cadTemp + posCambio);
            *(cadTemp + posCambio) = *(cadTemp + (strlen(cadena) - 1));
            *(cadTemp + (strlen(cadena) - 1)) = temp;

            cout << cadTemp << endl;

            char* temporal = new char [50];
            strcpy(temporal, cadTemp);

            cout << revesarCadena(temporal, 0, strlen(orig) - 1) << endl;

            strcpy(cadTemp, cadena);

            posCambio--;
            anagramas(cadena, cadTemp, cont, posCambio, orig);
        }

        else
        {
            cont++;

            if(cont < (strlen(cadena) - 1))
            {
                strcpy(cadTemp, orig);

                char temp = *(cadTemp + cont);
                *(cadTemp + cont) = *(cadTemp + 0);
                *(cadTemp + 0) = temp;

                cout << cadTemp << endl;

                char* temporal = new char [50];
                strcpy(temporal, cadTemp);

                cout << revesarCadena(temporal, 0, strlen(orig) - 1) << endl;

                strcpy(cadena, cadTemp);

                posCambio = strlen(cadena) - 2;
                anagramas(cadena, cadTemp, cont, posCambio, orig);
            }
        }
    }
}

int main()
{
    char* cadena = new char [50];

    cout << "Introdusca una palabra" << endl;
    cin >> cadena;

    char* copia = new char [50];
    strcpy(copia, cadena);

    char* copia2 = new char [50];
    strcpy(copia2, cadena);

    cout << "A continuacion apareceran todos los posibles anagramas de " << cadena << ":" << endl << endl;

    cout << cadena << endl;
    char* temporal = new char [50];
    strcpy(temporal, cadena);

    cout << revesarCadena(temporal, 0, strlen(cadena) - 1) << endl;

    anagramas(cadena, copia, 0, (strlen(cadena) - 2), copia2);
}
