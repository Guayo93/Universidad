#ifndef ARBOLEX_H_INCLUDED
#define ARBOLEX_H_INCLUDED

#include "NodoEx.h"
#include <iostream>

class ArbolEx
{
    protected:
        NodoEx* raiz;
        NodoEx* ultAgregado;
    public:
        ArbolEx();
        ~ArbolEx();
        void fijarRaiz(NodoEx* nRaiz);
        NodoEx* darRaiz();
        void fijarUltAgregado(NodoEx* nUltAregado);
        NodoEx* darUltAgregado();
        void agregarNodoPrefijo(std::string dato);
        void agregarNodoPosfijo(std::string dato);
        void generarExpresionPrefija();
        void generarExpresionPosfija();
        void generarExpresionInfija();
        void evaluarExpresion();
};

#include "ArbolEx.hxx"

#endif // ARBOLEX_H_INCLUDED
