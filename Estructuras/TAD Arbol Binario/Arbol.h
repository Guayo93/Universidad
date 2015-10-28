#ifndef __ARBOL__H__
#define __ARBOL__H__

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
        void fijarRaiz(Nodo<T>* nRaiz);
        Nodo<T>* darRaiz();
        bool agregarNodo(T& dato);
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "Arbol.hxx"

#endif // __ARBOL__H__
