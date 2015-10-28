#include "NodoAVL.h"

template <class T>
ArbolAVL<T>::ArbolAVL()
{
  this->raiz = NULL;
}

template <class T>
ArbolAVL<T>::ArbolAVL(T& dato)
{
  NodoAVL<T>* n = new NodoAVL<T>();
  n->fijarDato(dato);

  this.fijarRaiz(n);
}

template <class T>
ArbolAVL<T>::~ArbolAVL()
{

}

template <class T>
bool ArbolAVL<T>::esVacio()
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
void ArbolAVL<T>::fijarRaiz(NodoAVL<T>* nRaiz)
{
  this->raiz = nRaiz;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::darRaiz()
{
  return this->raiz;
}

template <class T>
bool ArbolAVL<T>::agregarNodo(T& dato)
{
  NodoAVL<T>* n = new NodoAVL<T>();
  n->fijarDato(dato);
  bool resp = false;

  if(this->esVacio() == true)
  {
    this->fijarRaiz(n);
    resp = true;
  }
  else
  {
    NodoAVL<T>* r = this->darRaiz();

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

  if(this->necesitaRotacion() != NULL)
  {
      NodoAVL<T>* n = this->necesitaRotacion();

      if(n->darDato() == this->darRaiz()->darDato())
      {
          this->fijarRaiz(n->rotar());
      }
      else
      {
          NodoAVL<T>* padre = this->darRaiz()->buscarPadre(n);

          if(padre->darHijoIzquierdo()->darDato() == n->darDato())
          {
              padre->fijarHijoIzquierdo(n->rotar());
          }

          if(padre->darHijoDerecho()->darDato() == n->darDato())
          {
              padre->fijarHijoDerecho(n->rotar());
          }
      }
  }

  return resp;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::necesitaRotacion()
{
  if(this->esVacio() == true)
  {
     return NULL;
  }
  else
  {
     return this->darRaiz()->necesitaRotacion();
  }
}

template <class T>
int ArbolAVL<T>::darAltura()
{
  if(this->esVacio() == true)
  {
     return -1;
  }
  else
  {
     return this->darRaiz()->darAltura();
  }
}

template <class T>
void ArbolAVL<T>::recPreOrden()
{
  if(this->esVacio() == false)
  {
    NodoAVL<T>* r = this->darRaiz();

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
void ArbolAVL<T>::recInOrden()
{
  if(this->esVacio() == false)
  {
    NodoAVL<T>* r = this->darRaiz();

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
void ArbolAVL<T>::recPosOrden()
{
  if(this->esVacio() == false)
  {
    NodoAVL<T>* r = this->darRaiz();

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
