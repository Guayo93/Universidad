#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

void llenarArreglo(char** &arreglo)
{
    arreglo = new char* [45];

    for(int i = 0; i < 45; i++)
    {
        switch(i)
        {
            case 0:
            {
                *(arreglo+i) = "Uno ";
            }
            break;

            case 1:
            {
                *(arreglo+i) = "Dos ";
            }
            break;

            case 2:
            {
                *(arreglo+i) = "Tres ";
            }
            break;

            case 3:
            {
                *(arreglo+i) = "Cuatro ";
            }
            break;

            case 4:
            {
                *(arreglo+i) = "Cinco ";
            }
            break;

            case 5:
            {
                *(arreglo+i) = "Seis ";
            }
            break;

            case 6:
            {
                *(arreglo+i) = "Siete ";
            }
            break;

            case 7:
            {
                *(arreglo+i) = "Ocho ";
            }
            break;

            case 8:
            {
                *(arreglo+i) = "Nueve ";
            }
            break;

            case 9:
            {
                *(arreglo+i) = "Diez ";
            }
            break;

            case 10:
            {
                *(arreglo+i) = "Veinte ";
            }
            break;

            case 11:
            {
                *(arreglo+i) = "Treinta ";
            }
            break;

            case 12:
            {
                *(arreglo+i) = "Cuarenta ";
            }
            break;

            case 13:
            {
                *(arreglo+i) = "Cincuenta ";
            }
            break;

            case 14:
            {
                *(arreglo+i) = "Sesenta ";
            }
            break;

            case 15:
            {
                *(arreglo+i) = "Setenta ";
            }
            break;

            case 16:
            {
                *(arreglo+i) = "Ochenta ";
            }
            break;

            case 17:
            {
                *(arreglo+i) = "Noventa ";
            }
            break;

            case 18:
            {
                *(arreglo+i) = "Cien ";
            }
            break;

            case 19:
            {
                *(arreglo+i) = "Docientos ";
            }
            break;

            case 20:
            {
                *(arreglo+i) = "Trecientos ";
            }
            break;

            case 21:
            {
                *(arreglo+i) = "Cuatrocientos ";
            }
            break;

            case 22:
            {
                *(arreglo+i) = "Quinientos ";
            }
            break;

            case 23:
            {
                *(arreglo+i) = "Seicientos ";
            }
            break;

            case 24:
            {
                *(arreglo+i) = "Setecientos ";
            }
            break;

            case 25:
            {
                *(arreglo+i) = "Ochocientos ";
            }
            break;

            case 26:
            {
                *(arreglo+i) = "Novecientos ";
            }
            break;

            case 27:
            {
                *(arreglo+i) = "Mil ";
            }
            break;

            case 28:
            {
                *(arreglo+i) = "Dos Mil ";
            }
            break;

            case 29:
            {
                *(arreglo+i) = "Tres Mil ";
            }
            break;

            case 30:
            {
                *(arreglo+i) = "Cuatro Mil ";
            }
            break;

            case 31:
            {
                *(arreglo+i) = "Cinco Mil ";
            }
            break;

            case 32:
            {
                *(arreglo+i) = "Seis Mil ";
            }
            break;

            case 33:
            {
                *(arreglo+i) = "Siete Mil ";
            }
            break;

            case 34:
            {
                *(arreglo+i) = "Ocho Mil ";
            }
            break;

            case 35:
            {
                *(arreglo+i) = "Nueve Mil ";
            }
            break;

            case 36:
            {
                *(arreglo+i) = "Diez Mil ";
            }
            break;

            case 37:
            {
                *(arreglo+i) = "Veinte Mil ";
            }
            break;

            case 38:
            {
                *(arreglo+i) = "Treinta Mil ";
            }
            break;

            case 39:
            {
                *(arreglo+i) = "Cuarenta Mil ";
            }
            break;

            case 40:
            {
                *(arreglo+i) = "Cincuenta Mil ";
            }
            break;

            case 41:
            {
                *(arreglo+i) = "Sesenta Mil ";
            }
            break;

            case 42:
            {
                *(arreglo+i) = "Setenta Mil ";
            }
            break;

            case 43:
            {
                *(arreglo+i) = "Ochenta Mil ";
            }
            break;

            case 44:
            {
                *(arreglo+i) = "Noventa Mil ";
            }
            break;
        }
    }
}

char* convertirNumeroACadena(int num)
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

char* transcribirALetras(char* cadNum, char** arreglo, char* cadenaFinal, int i)
{
    int cont = (strlen(cadNum)-1)-i;
    if(cont >= 0)
    {
        int num = *(cadNum+i) - '0';
        char* cad;

        if((num-1) < 0)
        {
            cad = "";
        }
        else
        {
            cad = *(arreglo + ((9*cont) + (num-1)));
        }

        strcat(cadenaFinal, cad);
        cont--;
        i++;

        return transcribirALetras(cadNum, arreglo, cadenaFinal, i);
    }
    else
    {
        return  cadenaFinal;
    }
}

int main()
{
    char** arregloLetras;
    char* cadenaFinal = new char [250];
    int num;

    llenarArreglo(arregloLetras);

    cout << "Digite un numero para devolverlo en letras (Max 5 Digitos)" << endl;
    cin >> num;

    cout << transcribirALetras(convertirNumeroACadena(num), arregloLetras,cadenaFinal, 0) << endl;
}
