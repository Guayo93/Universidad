#ifndef MULTILISTA_H_INCLUDED
#define MULTILISTA_H_INCLUDED
#include <string.h>
#include <cstdlib>

/**
    Por ahora solo es 2D
*/

using namespace std;

struct Snodo
{
    char* dato;
    Snodo* sig;
    Snodo* cabeza;
    Snodo* cola;
    int tamNLista;
};

struct Slista
{
    Snodo* cabeza;
    Snodo* cola;
    int tam;
};

Snodo* crearNodo(char* dato)
{
    Snodo* nodo = new Snodo;

    nodo->dato = new char [10];
    strcpy(nodo->dato, dato);
    nodo->sig = NULL;
    nodo->cabeza = NULL;
    nodo->cola = NULL;
    nodo->tamNLista = 0;

    return nodo;
}

Slista crearMultilista()
{
    Slista lista;
    lista.cabeza = NULL;
    lista.cola = NULL;
    lista.tam = 0;

    return lista;
}

bool listaEstaVacia(Slista lista)
{
    if(lista.tam == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sublistaEstaVacia(Snodo* nodo)
{
    if(nodo->tamNLista == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool esCola(Snodo* nodo)
{
    if(nodo->sig == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Snodo* buscarNodo(Slista lista, char* dato)
{
    Snodo* resp = NULL;
    Snodo* nodo = lista.cabeza;

    while(esCola(nodo) == false)
    {
        if(strcmp(nodo->dato,dato) == 0)
        {
            resp = nodo;
        }

        nodo = nodo->sig;
    }

    if(resp == NULL && strcmp(lista.cola->dato,dato) == 0)
    {
        resp = lista.cola;
    }

    return resp;
}

/**
    Agrega solo al final
*/
void agregarNodo(Slista &lista, char* dato)
{
    Snodo* nodo = crearNodo(dato);

    if(listaEstaVacia(lista) == true)
    {
        lista.cabeza = nodo;
        lista.cola = nodo;
        lista.tam++;
    }
    else
    {
        Snodo* temp = lista.cola;

        temp->sig = nodo;
        lista.cola = nodo;
        lista.tam++;
    }
}

void agregarNodoSublista(Slista &lista, char* datoNodo, char* dato)
{
    Snodo* nLista = buscarNodo(lista, datoNodo);
    Snodo* nodo = crearNodo(dato);

    if(sublistaEstaVacia(nLista) == true)
    {
        nLista->cabeza = nodo;
        nLista->cola = nodo;
        nLista->tamNLista++;
    }
    else
    {
        Snodo* temp = nLista->cola;

        temp->sig = nodo;
        nLista->cola = nodo;
        nLista->tamNLista++;
    }
}

void imprimirSublista(Snodo* nodo)
{
    if(sublistaEstaVacia(nodo) == true)
    {
        cout << "Sublista vacia" << endl;
    }
    else
    {
        Snodo* temp = nodo->cabeza;

        while(esCola(temp) == false)
        {
            cout << temp->dato << endl;
            temp = temp->sig;
        }
        cout << nodo->cola->dato << endl;
    }
}

void imprimirLista(Slista lista)
{
    if(listaEstaVacia(lista) == true)
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Snodo* nodo = lista.cabeza;

        while(esCola(nodo) == false)
        {
            cout << nodo->dato << endl;
            cout << "Sublista: " << endl;
            imprimirSublista(nodo);
            cout << endl;
            nodo = nodo->sig;
        }
        cout << lista.cola->dato << endl;
        cout << "Sublista: " << endl;
        imprimirSublista(nodo);
        cout << endl;
    }
}

#endif // MULTILISTA_H_INCLUDED
