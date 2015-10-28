#include <iostream>

using namespace std;

#define MAX 50

bool sonIdenticos(int cont1[], int cont2[], int tam, int tam2);
int crearArray(int cont[]);

int main()
{
    int aray1[MAX], aray2[MAX], tam1, tam2;
    bool sonIdent;

    tam1 = crearArray(aray1);
    tam2 = crearArray(aray2);

    sonIdent = sonIdenticos(aray1, aray2, tam1, tam2);

    if(sonIdent == true)
    {
        cout << "Los arreglos son Identicos." << endl;
    }
    else
    {
        cout << "Los arreglos NO son identicos." << endl;
    }
}

int crearArray(int cont[])
{
    cout << "Inicia la creacion del array." << endl;

    char conf;
    bool termino = false;
    int tam = 0;

    while(termino == false)
    {
        cout << "Quiere agregar un nuevo objeto? (S/N)" << endl;
        cin >> conf;
        if(conf == 'S' || conf == 's')
        {
            int temp;
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

    cout << "Termina la creacion del array." << endl;
    return tam;
}

bool sonIdenticos(int cont1[], int cont2[], int tam, int tam2)
{
    bool resp = true;

    if(tam == tam2)
    {
        for(int i = 0; i < tam && resp == true; i++)
        {
            if(cont1[i] != cont2[i])
            {
                resp = false;
            }
        }
    }
    else
    {
        resp = false;
    }

    return resp;
}
