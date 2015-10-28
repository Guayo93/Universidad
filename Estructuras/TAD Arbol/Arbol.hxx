#include "Nodo.h"
#include <vector>

template <class T>
Arbol<T>::Arbol()
{
  this->raiz = NULL;
}

template <class T>
Arbol<T>::Arbol(T& dato)
{
  Nodo<T> n;
  n.fijarDato(dato);
  this.fijarRaiz(&n);
}

template <class T>
Arbol<T>::~Arbol()
{
}

template <class T>
bool Arbol<T>::esVacio()
{
  if(this->obtenerRaiz() == NULL)
  {
     return true;
  }
  else
  {
    return false;
  }
}

template <class T>
Nodo<T>* Arbol<T>::obtenerRaiz()
{
  return this->raiz;
}

template <class T>
void Arbol<T>::fijarRaiz(Nodo<T>* nRaiz)
{
  this->raiz = nRaiz;
}

template <class T>
bool Arbol<T>::insertarNodo(T& padre, T& hijo)
{
  Nodo<T>* n = this->obtenerRaiz()->buscarHijo(padre);

  if(n == NULL)
  {
    return false;
  }
  else
  {
    n->adicionarHijo(hijo);
    return true;
  }
}

template <class T>
void Arbol<T>::recorrido()
{
  Nodo<T>* n = this->obtenerRaiz();

  std::cout << n->obtenerDato() << std::endl;

  std::vector< Nodo<T>* > hs = n->obtenerHijos();
  typename std::vector< Nodo<T>* >::iterator it = hs.begin();

  for(; it!= hs.end(); ++it)
  {
    (*it)->recorrerHijos();
  }
}
