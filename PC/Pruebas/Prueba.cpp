#include <iostream>
#include "Ordenamientos.h"
#define MAX 3

using namespace std;

int main()
{
    int n = MAX, m = MAX;
    int matriz[3][3] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    ordenarMatriz(matriz, n, m);

    cout << endl;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}
