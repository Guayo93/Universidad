#include <iostream>

NodoEx::NodoEx()
{
    this->der = NULL;
    this->izq = NULL;
}

NodoEx::~NodoEx()
{

}

void NodoEx::fijarDato(std::string nDato)
{
    this->dato = nDato;
}

std::string NodoEx::darDato()
{
    return this->dato;
}

void NodoEx::fijarDerecho(NodoEx* nDer)
{
    this->der = nDer;
}

NodoEx* NodoEx::darDerecho()
{
    return this->der;
}

void NodoEx::fijarIzquierdo(NodoEx* nIzq)
{
    this->izq = nIzq;
}

NodoEx* NodoEx::darIzquierdo()
{
    return this->izq;
}

bool NodoEx::esNumero()
{
    std::string d = this->darDato();

    if(d[0] <= 57 && d[0] >= 48)
    {
        return true;
    }
    else
    {
        return false;
    }
}

NodoEx* NodoEx::buscarPadre(NodoEx* n)
{
    NodoEx* resp = NULL;

    if(this->izq != NULL)
    {
        if(this->izq == n)
        {
            resp = this;
        }
        else
        {
            resp = this->izq->buscarPadre(n);
        }
    }

    if(this->der != NULL && resp == NULL)
    {
        if(this->der == n)
        {
            resp = this;
        }
        else
        {
            resp = this->der->buscarPadre(n);
        }
    }

    return resp;
}

std::string NodoEx::generarExpresionPrefija()
{
    std::string resp = "";

    resp += this->dato;

    if(this->izq != NULL)
    {
        resp += this->izq->generarExpresionPrefija();
    }

    if(this->der != NULL)
    {
        resp += this->der->generarExpresionPrefija();
    }

    return resp;
}

std::string NodoEx::generarExpresionPosfija()
{
    std::string resp = "";

    if(this->izq != NULL)
    {
        resp += std::string(this->izq->generarExpresionPosfija());
    }

    if(this->der != NULL)
    {
        resp += std::string(this->der->generarExpresionPosfija());
    }

    resp += this->dato;

    return resp;
}

std::string NodoEx::generarExpresionInfija()
{
    std::string resp = "";

    if(this->izq != NULL)
    {
        resp += this->izq->generarExpresionInfija();
    }

    resp += this->dato;

    if(this->der != NULL)
    {
        resp += this->der->generarExpresionInfija();
    }

    return resp;
}

//int NodoEx::evaluarExpresion();
