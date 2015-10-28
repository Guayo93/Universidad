#include "Nodo.h"
#include <vector>

template <class T>
Nodo<T>::Nodo()
{
  this->hijos.clear();
}

template <class T>
Nodo<T>::~Nodo()
{
  this.hijos.clear();
}

template <class T>
bool Nodo<T>::esHoja()
{
  if(this->hijos.empty() == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <class T>
T& Nodo<T>::obtenerDato()
{
  return this->dato;
}

template <class T>
void Nodo<T>::fijarDato(T& nDato)
{
  this->dato = nDato;
}

template <class T>
std::vector< Nodo<T>* > Nodo<T>::obtenerHijos()
{
  return this->hijos;
}

template <class T>
void Nodo<T>::limpiarHijos()
{
  this.hijos.clear();
}

template <class T>
void Nodo<T>::adicionarHijo(T& dato)
{
  Nodo<T>* n = new Nodo<T>();
  n->fijarDato(dato);

  this->hijos.push_back(n);
}

template <class T>
void Nodo<T>::eliminarHijo(T& dato)
{
  typename std::vector< Nodo<T> >::iterator it = this.hijos.begin();
  int i = 0;
  bool elimino = false;

  for(; it != this.hijos.end() && elimino == false; ++it)
  {
    if(it->obtnerDato() == *dato)
    {
      elimino = true;
    }
    else
    {
      i++;
    }
  }

  this.hijos.erase(this.hijos.begin() + i);
}

template <class T>
Nodo<T>* Nodo<T>::buscarHijo(T& dato)
{
  Nodo<T>* n;

  if(this->obtenerDato() == dato)
  {
    n = this;
  }
  else
  {
    if(this->esHoja() == false)
    {
      std::vector< Nodo<T>* > hs = this->obtenerHijos();
      typename std::vector< Nodo<T>* >::iterator it = hs.begin();
      bool encontro = false;

      for(; it != hs.end() && encontro == false; ++it)
      {
        n = (*it)->buscarHijo(dato);

        if(n != NULL)
        {
          encontro = true;
        }
      }
    }
  }

  return n;
}

template <class T>
void Nodo<T>::recorrerHijos()
{
  std::cout << this->obtenerDato() << std::endl;

  if(this->esHoja() != true)
  {
    std::vector< Nodo<T>* > hs = this->obtenerHijos();
    typename std::vector< Nodo<T>* >::iterator it = hs.begin();

    for(; it != hs.end(); ++it)
    {
      (*it)->recorrerHijos();
    }
  }
}
