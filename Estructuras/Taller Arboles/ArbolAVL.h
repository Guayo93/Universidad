#ifndef __ARBOLAVL__H__
#define __ARBOLAVL__H__

#include "NodoAVL.h"

template <class T>
class ArbolAVL
{
    protected:
        NodoAVL<T>* raiz;

    public:
        ArbolAVL();
        ArbolAVL(T& dato);
        ~ArbolAVL();
        bool esVacio();
        void fijarRaiz(NodoAVL<T>* nRaiz);
        NodoAVL<T>* darRaiz();
        bool agregarNodo(T& dato);
        NodoAVL<T>* necesitaRotacion();
        int darAltura();
        void recPreOrden();
        void recInOrden();
        void recPosOrden();
};

#include "ArbolAVL.hxx"

#endif // __ARBOLAVL__H__
