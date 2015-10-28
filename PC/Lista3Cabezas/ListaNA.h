#ifndef LISTANA_H_INCLUDED
#define LISTANA_H_INCLUDED

template <class T>
struct Nodo
{
    T* info;

    Nodo<T>* sigN;
    Nodo<T>* sigA1;
    Nodo<T>* sigA2;
};

template <class T>
struct Lista
{
    Nodo<T>* cabN;
    int tamN;

    Nodo<T>* cabA1;
    int tamA1;

    Nodo<T>* cabA2;
    int tamA2;
};

template <class T>
Nodo<T>* crearNodo(T info);

template <class T>
Lista<T>* crearLista();

template <class T>
bool listaNombreEstaVacia(Lista<T>* lista);

template <class T>
bool listaApellido1EstaVacia(Lista<T>* lista);

template <class T>
bool listaApellido2EstaVacia(Lista<T>* lista);

template <class T>
bool esColaNombre(Nodo<T>* nodo);

template <class T>
bool esColaApellido1(Nodo<T>* nodo);

template <class T>
bool esColaApellido2(Nodo<T>* nodo);

template <class T>
void agregarNodo(Lista<T>* lista, T info);

#endif // LISTANA_H_INCLUDED
