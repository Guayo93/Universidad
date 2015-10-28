#ifndef NODOEX_H_INCLUDED
#define NODOEX_H_INCLUDED

#include <iostream>

class NodoEx
{
    protected:
        std::string dato;
        NodoEx* der;
        NodoEx* izq;
    public:
        NodoEx();
        ~NodoEx();
        void fijarDato(std::string nDato);
        std::string darDato();
        void fijarDerecho(NodoEx* nDer);
        NodoEx* darDerecho();
        void fijarIzquierdo(NodoEx* nIzq);
        NodoEx* darIzquierdo();
        bool esNumero();
        NodoEx* buscarPadre(NodoEx* n);
        std::string generarExpresionPrefija();
        std::string generarExpresionPosfija();
        std::string generarExpresionInfija();
        int evaluarExpresion();
};

#include "NodoEx.hxx"

#endif // NODOEX_H_INCLUDED
