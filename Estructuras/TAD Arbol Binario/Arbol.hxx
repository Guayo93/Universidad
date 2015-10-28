#include "Nodo.h"

template <class T>
Arbol<T>::Arbol()
{
    this->raiz = NULL;
}

template <class T>
Arbol<T>::Arbol(T& dato)
{
    Nodo<T>* n = new Nodo<T>();
    n->fijarDato(dato);

    this.fijarRaiz(n);
}

template <class T>
Arbol<T>::~Arbol()
{

}

template <class T>
bool Arbol<T>::esVacio()
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
void Arbol<T>::fijarRaiz(Nodo<T>* nRaiz)
{
    this->raiz = nRaiz;
}

template <class T>
Nodo<T>* Arbol<T>::darRaiz()
{
    return this->raiz;
}

template <class T>
bool Arbol<T>::agregarNodo(T& dato)
{
    Nodo<T>* n = new Nodo<T>();
    n->fijarDato(dato);
    bool resp = false;

    if(this->esVacio() == true)
    {
        this->fijarRaiz(n);
        resp = true;
    }
    else
    {
        Nodo<T>* r = this->darRaiz();

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
void Arbol<T>::recPreOrden()
{
    if(this->esVacio() == false)
    {
        Nodo<T>* r = this->darRaiz();

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
        std::cout << "El Arbol esta vacio." << std::endl;
    }
}

template <class T>
void Arbol<T>::recInOrden()
{
    if(this->esVacio() == false)
    {
        Nodo<T>* r = this->darRaiz();

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
        std::cout << "El Arbol esta vacio." << std::endl;
    }
}

template <class T>
void Arbol<T>::recPosOrden()
{
    if(this->esVacio() == false)
    {
        Nodo<T>* r = this->darRaiz();

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
        std::cout << "El Arbol esta vacio." << std::endl;
    }
}
