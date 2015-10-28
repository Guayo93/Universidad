#ifndef __NODO__H__
#define __NODO__H__

template <class T>
class Nodo
{
    protected:
        T dato;
        Nodo<T>* izq;
        Nodo<T>* der;

    public:
        Nodo();
        Nodo(T& dato, Nodo<T>* izq, Nodo<T>* der);
        ~Nodo();
        bool esHoja();
        bool tieneHijoIzquierdo();
        bool tieneHijoDerecho();
        void fijarDato(T& nDato);
        T& darDato();
        void fijarHijoIzquierdo(Nodo<T>* nIzq);
        Nodo<T>* darHijoIzquierdo();
        void fijarHijoDerecho(Nodo<T>* nDer);
        Nodo<T>* darHijoDerecho();
        bool agregarHijo(Nodo<T>* n);
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "Nodo.hxx"

#endif // __NODO__H__
