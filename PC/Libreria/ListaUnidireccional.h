#ifndef LISTAUNIDIRECCIONAL_H_INCLUDED
#define LISTAUNIDIRECCIONAL_H_INCLUDED

using namespace std;

struct Snodo
{
    int dato;
    Snodo* sig;
};

struct Slista
{
    Snodo* cabeza;
    Snodo* cola;
    int tam;
};

Snodo* crearNodo(int dato)
{
    Snodo* nodo = new Snodo;

    nodo->dato = dato;
    nodo->sig = NULL;

    return nodo;
}

Slista crearLista()
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

/**
    Agrega solo al final
*/
void agregarNodo(Slista &lista, int dato)
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

Snodo* buscarNodo(Slista lista, int dato)
{
    Snodo* resp = NULL;
    Snodo* nodo = lista.cabeza;

    while(esCola(nodo) == false)
    {
        if(nodo->dato == dato)
        {
            resp = nodo;
        }

        nodo = nodo->sig;
    }

    if(lista.cola->dato == dato)
    {
        resp = lista.cola;
    }

    return resp;
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
            nodo = nodo->sig;
        }

        cout << lista.cola->dato << endl;
    }
}

#endif // LISTAUNIDIRECCIONAL_H_INCLUDED
