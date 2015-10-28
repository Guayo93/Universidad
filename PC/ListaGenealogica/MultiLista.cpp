#include <iostream>
#include <string.h>
#include <cstdlib>
#include <typeinfo>
#include "MultiLista.h"

template <class T, class U>
Snodo<T>* crearNodo(U info)
{
    Snodo<T>* nodo = new Snodo<T>;

    nodo->info = info;
    nodo->sig = NULL;

    return nodo;
}

template <class T>
Slista<T>* crearLista()
{
    Slista<T>* lista = new Slista<T>;

    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->tam = 0;

    return lista;
}

template <class T>
bool listaEstaVacia(Slista<T>* lista)
{
    if(lista->tam == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool esCola(Snodo<T>* nodo)
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

template <class T>
Snodo<T>* buscarNodo(Slista<T>* lista, T info)
{
    Snodo<T>* resp = NULL;
    Snodo<T>* nodo = lista.cabeza;

    while(esCola(nodo) == false)
    {
        if(nodo->info == info)
        {
            resp = nodo;
        }

        nodo = nodo->sig;
    }

    if(resp == NULL && lista->cola->info == info)
    {
        resp = lista.cola;
    }

    return resp;
}

/**
    Agrega solo al final
*/
template <class T, class U>
void agregarNodo(Slista<U>* lista, T info)
{
    Snodo<U>* nodo = crearNodo<U>(info);

    if(listaEstaVacia(lista) == true)
    {
        lista->cabeza = nodo;
        lista->cola = nodo;
        lista->tam++;
    }
    else
    {
        Snodo<U>* temp = lista->cola;

        temp->sig = nodo;
        lista->cola = nodo;
        lista->tam++;
    }
}
