template <class T>
NodoAVL<T>::NodoAVL()
{
  this->izq = NULL;
  this->der = NULL;
}

template <class T>
NodoAVL<T>::NodoAVL(T& dato, NodoAVL<T>* izq, NodoAVL<T>* der)
{
  this.fijarDato(dato);
  this.fijarHijoIzquierdo(izq);
  this.fijarHijoDerecho(der);
}

template <class T>
NodoAVL<T>::~NodoAVL()
{

}

template <class T>
bool NodoAVL<T>::esHoja()
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
bool NodoAVL<T>::tieneHijoIzquierdo()
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
bool NodoAVL<T>::tieneHijoDerecho()
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
void NodoAVL<T>::fijarDato(T& nDato)
{
  this->dato = nDato;
}

template <class T>
T& NodoAVL<T>::darDato()
{
  return this->dato;
}

template <class T>
void NodoAVL<T>::fijarHijoIzquierdo(NodoAVL<T>* nIzq)
{
  this->izq = nIzq;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::darHijoIzquierdo()
{
  return this->izq;
}

template <class T>
void NodoAVL<T>::fijarHijoDerecho(NodoAVL<T>* nDer)
{
  this->der = nDer;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::darHijoDerecho()
{
  return this->der;
}

template <class T>
bool NodoAVL<T>::agregarHijo(NodoAVL<T>* n)
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
NodoAVL<T>* NodoAVL<T>::buscarPadre(NodoAVL<T>* n)
{
    if(this->tieneHijoIzquierdo() == true)
    {
        if(this->darHijoIzquierdo()->darDato() == n->darDato())
        {
            return this;
        }
        else
        {
            this->darHijoIzquierdo()->buscarPadre(n);
        }
    }

    if(this->tieneHijoDerecho() == true)
    {
        if(this->darHijoDerecho()->darDato() == n->darDato())
        {
            return this;
        }
        else
        {
            this->darHijoDerecho()->buscarPadre(n);
        }
    }
}

template <class T>
NodoAVL<T>* NodoAVL<T>::necesitaRotacion()
{
  if(this->esHoja() == true)
  {
    return NULL;
  }
  else
  {
    int aI = -1;
    int aD = -1;

    if(this->tieneHijoIzquierdo() == true)
    {
      aI = this->darHijoIzquierdo()->darAltura();
    }

    if(this->tieneHijoDerecho() == true)
    {
      aD = this->darHijoDerecho()->darAltura();
    }

    if((aI - aD) >= 2 || (aI - aD) <= -2)
    {
      return this;
    }
    else
    {
      NodoAVL<T>* n = NULL;

      if(this->tieneHijoIzquierdo() == true)
      {
        n = this->darHijoIzquierdo()->necesitaRotacion();
      }
      if(n != NULL)
      {
        return n;
      }

      if(this->tieneHijoDerecho() == true)
      {
        n = this->darHijoDerecho()->necesitaRotacion();
      }
      if(n != NULL)
      {
        return n;
      }

      return NULL;
    }
  }
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rotar()
{
  int aI = -1;
  int aD = -1;

  if(this->tieneHijoIzquierdo() == true)
  {
    aI = this->darHijoIzquierdo()->darAltura();
  }

  if(this->tieneHijoDerecho() == true)
  {
    aD = this->darHijoDerecho()->darAltura();
  }

  if((aI - aD) >= 2)
  {
    NodoAVL<T>* hI = this->darHijoIzquierdo();

    int aII = -1;
    int aID = -1;

    if(hI->tieneHijoIzquierdo() == true)
    {
      aII = hI->darHijoIzquierdo()->darAltura();
    }

    if(hI->tieneHijoDerecho() == true)
    {
      aID = hI->darHijoDerecho()->darAltura();
    }

    if((aII - aID) > 0)
    {
      return this->rotacionDerecha(this);
    }

    if((aII - aID) < 0)
    {
      return this->rotacionIzquierdaDerecha(this);
    }
  }

  if((aI - aD) <= -2)
  {
    NodoAVL<T>* hD = this->darHijoDerecho();

    int aDI = -1;
    int aDD = -1;

    if(hD->tieneHijoIzquierdo() == true)
    {
      aDI = hD->darHijoIzquierdo()->darAltura();
    }

    if(hD->tieneHijoDerecho() == true)
    {
      aDD = hD->darHijoDerecho()->darAltura();
    }

    if((aDI - aDD) > 0)
    {
      return this->rotacionDerechaIzquierda(this);
    }

    if((aDI - aDD) < 0)
    {
      return this->rotacionIzquierda(this);
    }
  }
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rotacionIzquierda(NodoAVL<T>* n)
{
    NodoAVL<T>* padre = n->darHijoDerecho();
    n->fijarHijoDerecho(padre->darHijoIzquierdo());
    padre->fijarHijoIzquierdo(n);
    return padre;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rotacionDerecha(NodoAVL<T>* n)
{
    NodoAVL<T>* padre = n->darHijoIzquierdo();
    n->fijarHijoIzquierdo(padre->darHijoDerecho());
    padre->fijarHijoDerecho(n);
    return padre;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rotacionIzquierdaDerecha(NodoAVL<T>* n)
{
    NodoAVL<T>* aux = rotacionIzquierda(n->darHijoIzquierdo());
    n->fijarHijoIzquierdo(aux);
    return rotacionDerecha(n);
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rotacionDerechaIzquierda(NodoAVL<T>* n)
{
    NodoAVL<T>* aux = rotacionDerecha(n->darHijoDerecho());
    n->fijarHijoDerecho(aux);
    return rotacionIzquierda(n);
}

template <class T>
int NodoAVL<T>::darAltura()
{
  if(this->esHoja() == true)
  {
     return 0;
  }
  else
  {
    int aI = -1;
    int aD = -1;

    if(this->tieneHijoIzquierdo() == true)
    {
      aI = this->darHijoIzquierdo()->darAltura() + 1;
    }

    if(this->tieneHijoDerecho() == true)
    {
      aD = this->darHijoDerecho()->darAltura() + 1;
    }

    return aI > aD ? aI : aD;
  }
}

template <class T>
void NodoAVL<T>::recPreOrden()
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
void NodoAVL<T>::recInOrden()
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
void NodoAVL<T>::recPosOrden()
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
