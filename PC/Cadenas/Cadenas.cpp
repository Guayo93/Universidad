#include <iostream>
#include <string.h>

using namespace std;

int convertirCadenaAEntero(char * cad)
{
    int acum = 0, p = 1;

    for(int i = strlen(cad)-1; i >= 0; i--)
    {
        acum += p * (*(cad+i) - '0');
        p *= 10;
    }

    return acum;
}

char* convertirEnteroACadena(int num)
{
    int num2 = num, cont = 0;

    while(num2 != 0)
    {
        num2 /= 10;
        cont++;
    }

    char * cad = new char [cont+1];
    int i = cont - 1;

    while(i >= 0)
    {
        *(cad + i) = '0' + (num % 10);
        num /= 10;
        i--;
    }

    *(cad+cont) = '\0';

    return cad;
}

void concatenarCadena(char* &cad1, char* cad2)
{
    int i = strlen(cad1), cont = 0;

    while(i < ((strlen(cad1) + strlen(cad2)) - 1))
    {
        *(cad1+i) = *(cad2+cont);
        cont++;
        i++;
    }

    *(cad1+i) =  '\0';
}

char* cadenaEnCadena(char* cad1, char* cad2)
{
    bool sent = false;
    char* resp = NULL;
    int cont = 0;
    for(int i = 0; i < strlen(cad1) && sent == false; i++)
    {
        if(*(cad1+i) == *(cad2+cont))
        {
            cont++;
        }
        else
        {
            cont = 0;
        }

        if(cont == strlen(cad2))
        {
            resp = (cad1+i) - (cont-1);
            sent = true;
        }
    }

    return resp;
}

int compararCadenas(char* cad1, char* cad2)
{
    int resp = 0;
    bool sent = false;

    if(strlen(cad1) == strlen(cad2))
    {
        for(int i = 0; i < strlen(cad1) && sent == false; i++)
        {
            if(*(cad1+i) < *(cad2+i))
            {
                resp = -1;
                sent = true;
            }

            if(*(cad1+i) > *(cad2+i))
            {
                resp = 1;
                sent = true;
            }
        }
    }
    else
    {
        cout << "Las cadenas no tienen el mismo tamaño." << endl;
    }

    return resp;
}
int main()
{
    char * cad = new char[50];
    int a = 123;
    strcpy(cad, "1133");

    cout << compararCadenas(cad, convertirEnteroACadena(a)) << endl;

    delete cad;
}
