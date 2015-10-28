#include "NodoBinario.h"

template <class T>
ArbolBinario<T>::ArbolBinario()
{
    this->raiz = NULL;
}

template <class T>
ArbolBinario<T>::ArbolBinario(T& dato)
{
    NodoBinario<T>* n = new NodoBinario<T>();
    n->fijarDato(dato);

    this.fijarRaiz(n);
}

template <class T>
ArbolBinario<T>::~ArbolBinario()
{

}

template <class T>
bool ArbolBinario<T>::esVacio()
{
    if(this->darRaiz() == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void ArbolBinario<T>::fijarRaiz(NodoBinario<T>* nRaiz)
{
    this->raiz = nRaiz;
}

template <class T>
NodoBinario<T>* ArbolBinario<T>::darRaiz()
{
    return this->raiz;
}

template <class T>
bool ArbolBinario<T>::agregarNodo(T& dato)
{
    NodoBinario<T>* n = new NodoBinario<T>();
    n->fijarDato(dato);
    bool resp = false;

    if(this->esVacio() == true)
    {
        this->fijarRaiz(n);
        resp = true;
    }
    else
    {
        NodoBinario<T>* r = this->darRaiz();

        if(dato < r->darDato())
        {
            if(r->tieneHijoIzquierdo() == true)
            {
                resp = r->darHijoIzquierdo()->agregarHijo(n);
            }
            else
            {
                r->fijarHijoIzquierdo(n);
                resp = true;
            }
        }
        else if(dato > r->darDato())
        {
            if(r->tieneHijoDerecho() == true)
            {
                resp = r->darHijoDerecho()->agregarHijo(n);
            }
            else
            {
                r->fijarHijoDerecho(n);
                resp = true;
            }
        }
    }

    return resp;
}

template <class T>
void ArbolBinario<T>::recPreOrden()
{
    if(this->esVacio() == false)
    {
        NodoBinario<T>* r = this->darRaiz();

        std::cout << r->darDato() << std::endl;

        if(r->tieneHijoIzquierdo() == true)
        {
            r->darHijoIzquierdo()->recPreOrden();
        }

        if(r->tieneHijoDerecho() == true)
        {
            r->darHijoDerecho()->recPreOrden();
        }
    }
    else
    {
        std::cout << "El ArbolBinario esta vacio." << std::endl;
    }
}

template <class T>
void ArbolBinario<T>::recInOrden()
{
    if(this->esVacio() == false)
    {
        NodoBinario<T>* r = this->darRaiz();

        if(r->tieneHijoIzquierdo() == true)
        {
            r->darHijoIzquierdo()->recInOrden();
        }

        std::cout << r->darDato() << std::endl;

        if(r->tieneHijoDerecho() == true)
        {
            r->darHijoDerecho()->recInOrden();
        }
    }
    else
    {
        std::cout << "El ArbolBinario esta vacio." << std::endl;
    }
}

template <class T>
void ArbolBinario<T>::recPosOrden()
{
    if(this->esVacio() == false)
    {
        NodoBinario<T>* r = this->darRaiz();

        if(r->tieneHijoIzquierdo() == true)
        {
            r->darHijoIzquierdo()->recPosOrden();
        }

        if(r->tieneHijoDerecho() == true)
        {
            r->darHijoDerecho()->recPosOrden();
        }

        std::cout << r->darDato() << std::endl;
    }
    else
    {
        std::cout << "El ArbolBinario esta vacio." << std::endl;
    }
}
