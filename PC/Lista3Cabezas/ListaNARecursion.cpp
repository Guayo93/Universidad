#include <iostream>
#include <string.h>
#include "ListaNA.h"

template <class T>
Nodo<T>* crearNodo(T* info)
{
    Nodo<T>* nodo = new Nodo<T>;

    nodo->info = info;

    nodo->sigN = NULL;
    nodo->sigA1 = NULL;
    nodo->sigA2 = NULL;

    return nodo;
}

template <class T>
Lista<T>* crearLista()
{
    Lista<T>* lista = new Lista<T>;

    lista->cabN = NULL;
    lista->tamN = 0;

    lista->cabA1 = NULL;
    lista->tamA1 = 0;

    lista->cabA2 = NULL;
    lista->tamA2 = 0;

    return lista;
}

template <class T>
bool listaNombreEstaVacia(Lista<T>* lista)
{
    if(lista->tamN == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool listaApellido1EstaVacia(Lista<T>* lista)
{
    if(lista->tamA1 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool listaApellido2EstaVacia(Lista<T>* lista)
{
    if(lista->tamA2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool esColaNombre(Nodo<T>* nodo)
{
    if(nodo->sigN == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool esColaApellido1(Nodo<T>* nodo)
{
    if(nodo->sigA1 == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool esColaApellido2(Nodo<T>* nodo)
{
    if(nodo->sigA2 == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void agregarNodoNombre(Lista<T>* lista, Nodo<T>* nodo, Nodo<T>* actual)
{
    if(listaNombreEstaVacia(lista))
    {
        lista->cabN = nodo;
        lista->tamN++;
    }
    else
    {
        if(strcmp(actual->info->nombre, nodo->info->nombre) > 0)
        {
            nodo->sigN = actual;

            lista->cabN = nodo;
            lista->tamN++;
        }
        else
        {
            if(actual->sigN == NULL)
            {
                actual->sigN = nodo;
                lista->tamN++;
            }

            if(strcmp(actual->sigN->info->nombre, nodo->info->nombre) > 0)
            {
                nodo->sigN = actual->sigN;

                actual->sigN = nodo;
                lista->tamN++;
            }
            else
            {
                actual = actual->sigN;
                agregarNodoNombre(lista, nodo, actual);
            }
        }
    }
}

template <class T>
void agregarNodoApellido1(Lista<T>* lista, Nodo<T>* nodo)
{
    if(listaApellido1EstaVacia(lista))
    {
        lista->cabA1 = nodo;
        lista->tamA1++;
    }
    else
    {
        Nodo<T>* temp = lista->cabA1;

        if(strcmp(temp->info->apellido1, nodo->info->apellido1) > 0)
        {
            nodo->sigA1 = temp;

            lista->cabA1 = nodo;
            lista->tamA1++;
        }
        else
        {
            bool ingreso = false;

            while(ingreso == false)
            {
                if(temp->sigA1 == NULL)
                {
                    temp->sigA1 = nodo;
                    lista->tamA1++;

                    ingreso = true;
                }

                if(strcmp(temp->sigA1->info->apellido1, nodo->info->apellido1) > 0 && ingreso == false)
                {
                    nodo->sigA1 = temp->sigA1;

                    temp->sigA1 = nodo;
                    lista->tamA1++;

                    ingreso = true;
                }
                else
                {
                    temp = temp->sigA1;
                }
            }
        }
    }
}

template <class T>
void agregarNodoApellido2(Lista<T>* lista, Nodo<T>* nodo)
{
    if(listaApellido2EstaVacia(lista))
    {
        lista->cabA2 = nodo;
        lista->tamA2++;
    }
    else
    {
        Nodo<T>* temp = lista->cabA2;

        if(strcmp(temp->info->apellido2, nodo->info->apellido2) > 0)
        {
            nodo->sigA2 = temp;

            lista->cabA2 = nodo;
            lista->tamA2++;
        }
        else
        {
            bool ingreso = false;

            while(ingreso == false)
            {
                if(temp->sigA2 == NULL)
                {
                    temp->sigA2 = nodo;
                    lista->tamA2++;

                    ingreso = true;
                }

                if(strcmp(temp->sigA2->info->apellido2, nodo->info->apellido2) > 0 && ingreso == false)
                {
                    nodo->sigA2 = temp->sigA2;

                    temp->sigA2 = nodo;
                    lista->tamA2++;

                    ingreso = true;
                }
                else
                {
                    temp = temp->sigA2;
                }
            }
        }
    }
}

template <class T>
void agregarNodo(Lista<T>* lista, T* info)
{
    Nodo<T>* nodo = crearNodo<T>(info);

    ///Agregacion por nombre
    agregarNodoNombre(lista, nodo, lista->cabN);
    ///Agregacion por Apellido 1
    agregarNodoApellido1(lista, nodo);
    ///Agregacion por Apellido 2
    agregarNodoApellido2(lista, nodo);
}
