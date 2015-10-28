#ifndef MULTILISTA_H_INCLUDED
#define MULTILISTA_H_INCLUDED

/**
    Por ahora solo es 2D
*/

using namespace std;

template <class T>
struct Snodo
{
    T* info;
    Snodo<T>* sig;
};

template <class T>
struct Slista
{
    Snodo<T>* cabeza;
    Snodo<T>* cola;
    int tam;
};

template <class T, class U>
Snodo<T>* crearNodo(U info);

template <class T>
Slista<T>* crearLista();

template <class T>
bool listaEstaVacia(Slista<T>* lista);

template <class T>
bool esCola(Snodo<T>* nodo);

template <class T>
Snodo<T>* buscarNodo(Slista<T>* lista, T info);

/**
    Agrega solo al final
*/
template <class T, class U>
void agregarNodo(Slista<U>* lista, T info);

#endif // MULTILISTA_H_INCLUDED
