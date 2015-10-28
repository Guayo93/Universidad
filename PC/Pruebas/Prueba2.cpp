#include <iostream>
#include <cstdlib>
#define MAX 100

using namespace std;

void ordenar(int * vectorApunts[], int tam)
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

int main()
{
    int vect[MAX], tam;
    int * vectorApunts[MAX];

    cout << "Cual sera el tamaño del vector?" << endl;
    cin >> tam;

    for(int i = 0; i < tam; i++)
    {
        cout << "Digite el numero." << endl;
        cin >> vect[i];
    }

    system("CLS");

    cout << "De esta manera quedo el vector de enteros sin ordenar." << endl;

    for(int i = 0; i < tam; i++)
    {
        cout << vect[i] << " ";
    }

    cout << endl;

    system("PAUSE");
    system("CLS");

    for(int i = 0; i < tam; i++)
    {
        ///ARITMETICA DE APUNTADORES -- Es mas eficiente que: vectorApunts[i] = &vect[i]
        vectorApunts[i] = vect+i;
    }

    ordenar(vectorApunts, tam);

    cout << "De esta manera quedo el vector de enteros." << endl;

    for(int i = 0; i < tam; i++)
    {
        cout << vect[i] << " ";
    }

    cout << endl << "De esta manera quedo el vector de apuntadores despues de ordenarlo." << endl;

    for(int i = 0; i < tam; i++)
    {
        cout << *vectorApunts[i] << " ";
    }

    cout << endl;
}
