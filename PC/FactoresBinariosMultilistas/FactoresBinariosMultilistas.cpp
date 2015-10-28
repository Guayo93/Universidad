#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "MultiLista.h"

using namespace std;

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

void factoresBinarios(Slista &lista, Snodo* nodo)
{
    int num = atoi(nodo->dato);
    int copia = num;
    int cont = 0;
    while(num != 0)
    {
        if(num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            char* temp = new char [10];
            strcpy(temp, "2^");
            strcat(temp, convertirEnteroACadena(cont));
            agregarNodoSublista(lista, convertirEnteroACadena(copia), temp);
            num /= 2;
        }
        cont++;
    }
}

void llenarLista(Slista &lista, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        char* cnum = new char [10];
        int num = rand()%500;
        strcpy(cnum, convertirEnteroACadena(num));
        agregarNodo(lista, cnum);
    }
}

void llenarSublistas(Slista &lista)
{
    Snodo* nodo = lista.cabeza;

    while(esCola(nodo) == false)
    {
        factoresBinarios(lista, nodo);
        nodo = nodo->sig;
    }

    nodo = lista.cola;
    factoresBinarios(lista, nodo);
}

int main()
{
    srand(time(NULL));

    Slista lista = crearMultilista();
    int tam;

    cout << "Cuantos numero aleatorios desea imprimir?" << endl;
    cin >> tam;

    llenarLista(lista, tam);

    llenarSublistas(lista);

    imprimirLista(lista);
}
