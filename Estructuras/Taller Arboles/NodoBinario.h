#ifndef __NODO__H__
#define __NODO__H__

template <class T>
class NodoBinario
{
    protected:
        T dato;
        NodoBinario<T>* izq;
        NodoBinario<T>* der;

    public:
        NodoBinario();
        NodoBinario(T& dato, NodoBinario<T>* izq, NodoBinario<T>* der);
        ~NodoBinario();
        bool esHoja();
        bool tieneHijoIzquierdo();
        bool tieneHijoDerecho();
        void fijarDato(T& nDato);
        T& darDato();
        void fijarHijoIzquierdo(NodoBinario<T>* nIzq);
        NodoBinario<T>* darHijoIzquierdo();
        void fijarHijoDerecho(NodoBinario<T>* nDer);
        NodoBinario<T>* darHijoDerecho();
        bool agregarHijo(NodoBinario<T>* n);
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "NodoBinario.hxx"

#endif // __NODO__H__
