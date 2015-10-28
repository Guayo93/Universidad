#ifndef MULTILISTA_H_INCLUDED
#define MULTILISTA_H_INCLUDED
#include <string.h>
#include <cstdlib>

/**
    Por ahora solo es 2D
*/

using namespace std;

template <typename T>
struct Snodo
{
    T* info;
    Snodo* sig;
};

struct Slista
{
    Snodo* cabeza;
    Snodo* cola;
    int tam;
};

struct SInfoPadre
{
    char* nombre;
    char* cargo;
    Slista* hijos;
};

struct SInfoHijo
{
    char* nombre;
    Slista* nietos;
};

struct SInfoNieto
{
    char* nombre;
};

template <typename T>
Snodo* crearNodo(T info)
{
    Snodo* nodo = new Snodo;

    nodo->info = info;
    nodo->sig = NULL;

    return nodo;
}

Slista* crearLista()
{
    Slista* lista = new Slista;

    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->tam = 0;

    return lista;
}

SInfoPadre* crearInfoPadre(char* nombre, char* cargo)
{
    SInfoPadre* infoPadre = new SInfoPadre;

    infoPadre->nombre = nombre;
    infoPadre->cargo = cargo;
    infoPadre->hijos = crearLista();

    return infoPadre;
}

SInfoHijo* crearInfoHijo(char* nombre)
{
    SInfoHijo* infoHijo = new SInfoHijo;

    infoHijo->nombre = nombre;
    infoHijo->nietos = crearLista();

    return infoHijo;
}

SInfoNieto* crearInfoNieto(char* nombre)
{
    SInfoNieto* infoNieto = new SInfoNieto;

    infoNieto->nombre = nombre;

    return infoNieto;
}

bool listaEstaVacia(Slista* lista)
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

template <typename T>
Snodo* buscarNodo(Slista* lista, T info)
{
    Snodo* resp = NULL;
    Snodo* nodo = lista.cabeza;

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
template <typename T>
void agregarNodo(Slista* lista, T info)
{
    Snodo* nodo = crearNodo(info);

    if(listaEstaVacia(lista) == true)
    {
        lista->cabeza = nodo;
        lista->cola = nodo;
        lista->tam++;
    }
    else
    {
        Snodo* temp = lista.cola;

        temp->sig = nodo;
        lista->cola = nodo;
        lista->tam++;
    }
}

void imprimirLista(Slista* lista)
{
    if(listaEstaVacia(lista) == true)
    {
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        Snodo* nodo = lista->cabeza;

        while(esCola(nodo) == false)
        {
            if(typeid(nodo->info) != typeid(SInfoPadre))
            {
                cout << nodo->info->nombre << endl;
                cout << nodo->info->cargo << endl;
            }
            else
            {
                cout << nodo->info->nombre << endl;
            }

            if(typeid(nodo->info) != typeid(SInfoNieto))
            {
                cout << "Hijos: " << endl;
                imprimirLista(nodo->info);
                cout << endl;
            }

            nodo = nodo->sig;
        }

        if(typeid(lista->cola->info) != typeid(SInfoPadre))
        {
            cout << lista->cola->info->nombre << endl;
            cout << lista->cola->info->cargo << endl;
        }
        else
        {
            cout << lista->cola->info->nombre << endl;
        }

        if(typeid(lista->cola->info) != typeid(SInfoNieto))
        {
            cout << "Hijos: " << endl;
            imprimirLista(lista->cola->info);
            cout << endl;
        }
    }
}

#endif // MULTILISTA_H_INCLUDED
