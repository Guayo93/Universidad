#ifndef ARBOL__H
#define ARBOL__H

#include "Nodo.h"

template <class T>
class Arbol
{
  protected:
    Nodo<T>* raiz;

  public:
    Arbol();
    Arbol(T& dato);
    ~Arbol();
    bool esVacio();
    Nodo<T>* obtenerRaiz();
    void fijarRaiz(Nodo<T>* nRaiz);
    bool insertarNodo(T& padre, T& hijo);
    bool eliminarNodo(T& dato);
    void recorrido();
};

#include "Arbol.hxx"

#endif // ARBOL__H
