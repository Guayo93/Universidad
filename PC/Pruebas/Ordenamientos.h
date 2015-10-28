#include <iostream>

#ifndef ORDENAMIENTOS_H_INCLUDED
#define ORDENAMIENTOS_H_INCLUDED

#define MAX 3

using namespace std;

class Ordenamientos
{
    public:
        void ordenarVectorPunteros(int * vectorApunts[], int tam);
        void ordenarMatriz(int matriz[MAX][MAX], const int n, const int m);
        void ordenarMatrizPunteros(int * mat[MAX][MAX], const int n, const int m);
};

void ordenarVectorPunteros(int * vectorApunts[], int tam)
{
    int * temp = NULL;

    for(int i = 0; i < tam-1; i++)
    {
        for(int j = i+1; j < tam; j++)
        {
            if(*vectorApunts[j] < *vectorApunts[i])
            {
                temp = vectorApunts[i];
                vectorApunts[i] = vectorApunts[j];
                vectorApunts[j] = temp;
            }
        }
    }
}

void ordenarMatriz(int mat[MAX][MAX], const int n, const int m)
{
    int aux = 0;

    for(int i = 0; i < (n*m) - 1; i++)
    {
        for(int j = i + 1; j < (n*m); j++)
        {
            if(mat[i/m][i%m] > mat[j/m][j%m])
            {
                aux = mat[i/m][i%m];
                mat[i/m][i%m] = mat[j/m][j%m];
                mat[j/m][j%m] = aux;
            }
        }
    }
}

void ordenarMatrizPunteros(int * mat[MAX][MAX], const int n, const int m)
{
    int * aux = NULL;

    for(int i = 0; i < (n*m) - 1; i++)
    {
        for(int j = i + 1; j < (n*m); j++)
        {
            if(*(*(*(mat+(i/m))+(i%m))) > *(*(*(mat+(j/m))+(j%m)))) ///*mat[i/m][i%m] > *mat[j/m][j%m]
            {
                aux = *(*(mat+(i/m))+(i%m));
                *(*(mat+(i/m))+(i%m)) = *(*(mat+(j/m))+(j%m));
                *(*(mat+(j/m))+(j%m)) = aux;
            }
        }
    }
}

#endif // ORDENAMIENTOS_H_INCLUDED
