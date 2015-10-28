#ifndef __NODOAVL__H__
#define __NODOAVL__H__

template <class T>
class NodoAVL
{
    protected:
        T dato;
        NodoAVL<T>* izq;
        NodoAVL<T>* der;

    public:
        NodoAVL();
        NodoAVL(T& dato, NodoAVL<T>* izq, NodoAVL<T>* der);
        ~NodoAVL();
        bool esHoja();
        bool tieneHijoIzquierdo();
        bool tieneHijoDerecho();
        void fijarDato(T& nDato);
        T& darDato();
        void fijarHijoIzquierdo(NodoAVL<T>* nIzq);
        NodoAVL<T>* darHijoIzquierdo();
        void fijarHijoDerecho(NodoAVL<T>* nDer);
        NodoAVL<T>* darHijoDerecho();
        bool agregarHijo(NodoAVL<T>* n);
        NodoAVL<T>* buscarPadre(NodoAVL<T>* n);
        NodoAVL<T>* necesitaRotacion();
        NodoAVL<T>* rotar();
        NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* n);
        NodoAVL<T>* rotacionDerecha(NodoAVL<T>* n);
        NodoAVL<T>* rotacionIzquierdaDerecha(NodoAVL<T>* n);
        NodoAVL<T>* rotacionDerechaIzquierda(NodoAVL<T>* n);
        int darAltura();
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "NodoAVL.hxx"

#endif // __NODOAVL__H__
