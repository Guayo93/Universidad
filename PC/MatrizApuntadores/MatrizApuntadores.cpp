#include <iostream>
#include <cstdlib>
#include "Ordenamientos.h"
#define MAX 3

using namespace std;

int main()
{
    int m[MAX][MAX], fil, col;
    int * mp[MAX][MAX];

    cout << "Cual es el numero de filas?" << endl;
    cin >> fil;

    cout << "Cual es el numero de columnas?" << endl;
    cin >> col;

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << "Diite el numero en la posicion (" << i << "," << j << ")" << endl;
            cin >> m[i][j];
        }
    }

    cout << "la matriz a ordenar por punteros es la siguiente:" << endl;

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    system("PAUSE");
    system("CLS");

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            mp[i][j] = (*(m+i)+j);
        }
    }

    cout << "La matriz de punteros es la siguiente:" << endl;

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << *mp[i][j] << " ";
        }
        cout << endl;
    }

    ordenarMatrizPunteros(mp, 3, 3);

    system("PAUSE");
    system("CLS");

    cout << "La matriz original no la tocamos:" << endl;

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Pero la siguiente es la matriz de punteros ordenada:" << endl;

    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << *mp[i][j] << " ";
        }
        cout << endl;
    }
}
