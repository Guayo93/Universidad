#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

using namespace std;

struct Snodo
{
    int dato;
    Snodo* sig;
};

struct Slista
{
    Snodo* cabeza;
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

void agregarNodo(Slista &lista, int dato)
{
    Snodo* nodo = crearNodo(dato);

    if(listaEstaVacia(lista) == true)
    {
        lista.cabeza = nodo;
        lista.tam++;
    }
    else
    {
        Snodo* temp = lista.cabeza;

        while(esCola(temp) == false)
        {
            temp = temp->sig;
        }

        temp->sig = nodo;
        lista.tam++;
    }
}

void imprimirLista(Slista lista)
{
    if(listaEstaVacia(lista) == true)
    {
        cout << "La lista esta vacia." << endl;
    }
    else
    {
        Snodo* nodo = lista.cabeza;

        while(esCola(nodo) == false)
        {
            cout << nodo->dato << endl;
            nodo = nodo->sig;
        }

        cout << nodo->dato << endl;

    }
}

#endif // LISTA_H_INCLUDED
