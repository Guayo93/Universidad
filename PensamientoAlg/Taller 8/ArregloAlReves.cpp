#include <iostream>

using namespace std;

#define MAX 50

int main()
{
    char cont[MAX];
    char conf;
    bool termino = false;
    int tam = 0;

    while(termino == false)
    {
        cout << "Quiere agregar un nuevo objeto? (S/N)" << endl;
        cin >> conf;
        if(conf == 'S' || conf == 's')
        {
            char temp;
            cout << "Que elemento quiere guardar en la posicion " << tam << "?" << endl;
            cin >> temp;
            cont[tam] = temp;
            tam++;
        }
        else
        {
            termino = true;
        }
    }

    cout << "Los objetos agregados de atras para adelante son: " << endl;
    for(int i = tam-1; i >= 0; i--)
    {
        cout << cont[i] << " ";
    }
}
