#include <iostream>
#include "ListaNARecursion.cpp"

using namespace std;

struct Info
{
    char* nombre;
    char* apellido1;
    char* apellido2;
};

Info* crearInfo(char* nombre, char* apellido1, char* apellido2)
{
    Info* info = new Info;

    info->nombre = nombre;
    info->apellido1 = apellido1;
    info->apellido2 = apellido2;

    return info;
}

void imprimirListaNombre(Lista<Info>* lista)
{
    if(listaNombreEstaVacia(lista))
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Nodo<Info>* nodo = lista->cabN;

        while(esColaNombre<Info>(nodo)== false)
        {
            cout << "Nombre: " << nodo->info->nombre << endl;
            cout << "Apellido 1: " << nodo->info->apellido1 << endl;
            cout << "Apellido 2: " << nodo->info->apellido2 << endl;

            nodo = nodo->sigN;
        }

        cout << "Nombre: " << nodo->info->nombre << endl;
        cout << "Apellido 1: " << nodo->info->apellido1 << endl;
        cout << "Apellido 2: " << nodo->info->apellido2 << endl;
    }
}

void imprimirListaApellido1(Lista<Info>* lista)
{
    if(listaApellido1EstaVacia(lista))
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Nodo<Info>* nodo = lista->cabA1;

        while(esColaApellido1<Info>(nodo) == false)
        {
            cout << "Nombre: " << nodo->info->nombre << endl;
            cout << "Apellido 1: " << nodo->info->apellido1 << endl;
            cout << "Apellido 2: " << nodo->info->apellido2 << endl;

            nodo = nodo->sigA1;
        }

        cout << "Nombre: " << nodo->info->nombre << endl;
        cout << "Apellido 1: " << nodo->info->apellido1 << endl;
        cout << "Apellido 2: " << nodo->info->apellido2 << endl;
    }
}

void imprimirListaApellido2(Lista<Info>* lista)
{
    if(listaApellido2EstaVacia(lista))
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Nodo<Info>* nodo = lista->cabA2;

        while(esColaApellido2<Info>(nodo) == false)
        {
            cout << "Nombre: " << nodo->info->nombre << endl;
            cout << "Apellido 1: " << nodo->info->apellido1 << endl;
            cout << "Apellido 2: " << nodo->info->apellido2 << endl;

            nodo = nodo->sigA2;
        }

        cout << "Nombre: " << nodo->info->nombre << endl;
        cout << "Apellido 1: " << nodo->info->apellido1 << endl;
        cout << "Apellido 2: " << nodo->info->apellido2 << endl;
    }
}

void imprimirLista(Lista<Info>* lista)
{
    cout << "Lista por Nombre" << endl ;
    imprimirListaNombre(lista);
    cout << endl << "Lista por Apellido 1" << endl;
    imprimirListaApellido1(lista);
    cout << endl << "Lista por Apellido 2" << endl;
    imprimirListaApellido2(lista);
}

int main()
{
    Lista<Info>* lista = crearLista<Info>();

    Info* info = crearInfo("Paula", "Arango", "Sanchez");
    cout << "sali" << endl;
    agregarNodo<Info>(lista, info);

    info = crearInfo("Manuel", "Ruiz", "Torres");
    cout << "sali" << endl;
    agregarNodo<Info>(lista, info);

    info = crearInfo("Ricardo", "Monnet", "Arguello");
    cout << "sali" << endl;
    agregarNodo<Info>(lista, info);

    info = crearInfo("Liliana", "Bohorquez", "Silva");
    cout << "sali" << endl;
    agregarNodo<Info>(lista, info);

    imprimirLista(lista);
}
