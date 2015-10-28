#ifndef __ARBOL__H__
#define __ARBOL__H__

#include "NodoBinario.h"

template <class T>
class ArbolBinario
{
    protected:
        NodoBinario<T>* raiz;

    public:
        ArbolBinario();
        ArbolBinario(T& dato);
        ~ArbolBinario();
        bool esVacio();
        void fijarRaiz(NodoBinario<T>* nRaiz);
        NodoBinario<T>* darRaiz();
        bool agregarNodo(T& dato);
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "ArbolBinario.hxx"

#endif // __ARBOL__H__
