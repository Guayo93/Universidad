#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
    LLena el Vector
*/
void llenarVector(int * vect, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        *(vect + i) = rand()%500;
    }
}

/*
    Imprime el Vector
*/
void imprimirVector(int * vect, int tam)
{
    cout << endl << "Los numeros aleatorios son los siguientes:" << endl;

    for(int i = 0; i < tam; i++)
    {
        cout << *(vect + i) << " | ";
    }

    cout << endl;
}

/*
    Imprime los factores binarios del numero entregado
*/
void factoresBinarios(int num)
{
    int cont = 0;
    while(num != 0)
    {
        if(num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            cout << "2^" << cont << "  ";
            num /= 2;
        }
        cont++;
    }
}

/*
    Libera la memoria utilizada por el vector
*/
void liberarVector(int * &vect)
{
    delete vect;
    vect = NULL;
}

int main()
{
    ///Semilla del Random
    srand(time(NULL));

    ///Declaracion variables
    int tam;
    int * vect;

    ///Pedida de datos
    cout << "Cuantos numero aleatorios desea imprimir?" << endl;
    cin >> tam;

    ///Creacion del Vector
    vect = new int [tam];

    ///Llenado del Vector
    llenarVector(vect, tam);

    ///Impresion del Vector
    imprimirVector(vect, tam);

    system("PAUSE");
    system("CLS");

    ///Mensaje Final
    cout << "A continuacion encontrara los factores binarios de cada numero:" << endl;

    ///Ciclo que calcula los factores binarios para cada posicion del vector
    for(int i = 0; i < tam; i++)
    {
        cout << endl << *(vect + i) << ": ";
        factoresBinarios(*(vect + i));
        cout << endl;
    }

    ///Liberar Vector
    liberarVector(vect);
}
