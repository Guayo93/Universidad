template <class T>
NodoBinario<T>::NodoBinario()
{
    this->izq = NULL;
    this->der = NULL;
}

template <class T>
NodoBinario<T>::NodoBinario(T& dato, NodoBinario<T>* izq, NodoBinario<T>* der)
{
    this.fijarDato(dato);
    this.fijarHijoIzquierdo(izq);
    this.fijarHijoDerecho(der);
}

template <class T>
NodoBinario<T>::~NodoBinario()
{

}

template <class T>
bool NodoBinario<T>::esHoja()
{
    if(this->tieneHijoIzquierdo() == false && this->tieneHijoDerecho() == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool NodoBinario<T>::tieneHijoIzquierdo()
{
    if(this->darHijoIzquierdo() != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool NodoBinario<T>::tieneHijoDerecho()
{
    if(this->darHijoDerecho() != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void NodoBinario<T>::fijarDato(T& nDato)
{
    this->dato = nDato;
}

template <class T>
T& NodoBinario<T>::darDato()
{
    return this->dato;
}

template <class T>
void NodoBinario<T>::fijarHijoIzquierdo(NodoBinario<T>* nIzq)
{
    this->izq = nIzq;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::darHijoIzquierdo()
{
    return this->izq;
}

template <class T>
void NodoBinario<T>::fijarHijoDerecho(NodoBinario<T>* nDer)
{
    this->der = nDer;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::darHijoDerecho()
{
    return this->der;
}

template <class T>
bool NodoBinario<T>::agregarHijo(NodoBinario<T>* n)
{
    bool resp = false;

    if(n->darDato() < this->darDato())
    {
        if(this->tieneHijoIzquierdo() == true)
        {
            resp = this->darHijoIzquierdo()->agregarHijo(n);
        }
        else
        {
            this->fijarHijoIzquierdo(n);
            resp = true;
        }
    }
    else if(n->darDato() > this->darDato())
    {
        if(this->tieneHijoDerecho() == true)
        {
            resp = this->darHijoDerecho()->agregarHijo(n);
        }
        else
        {
            this->fijarHijoDerecho(n);
            resp = true;
        }
    }

    return resp;
}

template <class T>
void NodoBinario<T>::recPreOrden()
{
    std::cout << this->darDato() << std::endl;

    if(this->tieneHijoIzquierdo() == true)
    {
        this->darHijoIzquierdo()->recPreOrden();
    }

    if(this->tieneHijoDerecho() == true)
    {
        this->darHijoDerecho()->recPreOrden();
    }
}

template <class T>
void NodoBinario<T>::recInOrden()
{
    if(this->tieneHijoIzquierdo() == true)
    {
        this->darHijoIzquierdo()->recInOrden();
    }

    std::cout << this->darDato() << std::endl;

    if(this->tieneHijoDerecho() == true)
    {
        this->darHijoDerecho()->recInOrden();
    }
}

template <class T>
void NodoBinario<T>::recPosOrden()
{
    if(this->tieneHijoIzquierdo() == true)
    {
        this->darHijoIzquierdo()->recPosOrden();
    }

    if(this->tieneHijoDerecho() == true)
    {
        this->darHijoDerecho()->recPosOrden();
    }

    std::cout << this->darDato() << std::endl;
}
