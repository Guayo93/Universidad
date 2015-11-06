#include <vector>
#include "Arista.h"

template< class T >
Vertice< T >::Vertice()
{
  std::vector< Arista< T >* > preds;
  std::vector< Arista< T >* > sus;
  this->predecesores = preds;
  this->sucesores = sus;
}

template< class T >
Vertice< T >::~Vertice()
{

}

template< class T >
T Vertice< T >::darInfo()
{
  return this->info;
}

template< class T >
void Vertice< T >::setInfo( T nInfo )
{
  this->info = nInfo;
}

template< class T >
std::vector< Arista< T >* > Vertice< T >::darPredecesores()
{
  return this->predecesores;
}

template< class T >
void Vertice< T >::setPredecesores( std::vector< Arista< T >* > nAris )
{
  this->predecesores = nAris;
}

template< class T >
std::vector< Arista< T >* > Vertice< T >::darSucesores()
{
  return this->sucesores;
}

template< class T >
void Vertice< T >::setSucesores( std::vector< Arista< T >* > nAris )
{
  this->sucesores = nAris;
}

template< class T >
bool Vertice< T >::darMarca()
{
  return this->marca;
}

template< class T >
void Vertice< T >::marcar()
{
  this->marca = true;
}

template< class T >
void Vertice< T >::desmarcar()
{
  this->marca = false;
}

template< class T >
Arista< T >* Vertice< T >::buscarArista( T infOri, T infDes )
{
  Arista< T >* a = NULL;

  for(int i = 0; i < predecesores.size(); i++)
  {
    if(predecesores[i]->darOrigen() == infOri && predecesores[i]->darDestino() == infDes)
    {
      a = predecesores[i];
    }
  }

  if(a != NULL)
  {
    return a;
  }

  for(int i = 0; i < sucesores.size(); i++)
  {
    if(sucesores[i]->darOrigen() == infOri && sucesores[i]->darDestino() == infDes)
    {
      a = sucesores[i];
    }
  }

  if(a != NULL)
  {
    return a;
  }
  else
  {
    return NULL;
  }
}

template< class T >
bool Vertice< T >::agregarArista( Arista< T >* ar )
{
  if(this->buscarArista(ar->darOrigen(), ar->darDestino()) == NULL)
  {
    if(ar->darOrigen() == this->info)
    {
      this->sucesores.push_back(ar);
      return true;
    }

    if(ar->darDestino() == this->info)
    {
      this->predecesores.push_back(ar);
      return true;
    }
  }

  return false;
}

//template< class T >
//bool Vertice< T >::eliminarArista(); Reformular

/*void Vertice< T >::marcarAdyacentes( )
{
  this->marcar();

  for(int i = 0; i < this->sucesores.size(); i++)
  {
    T sus = this->sucesores[i];
    if(g->buscarVertice(sus)->darMarca() == false)
    {
      g->buscarVertice(sus)->marcar();
      g->buscarVertice(sus)->marcarAdyacentes(g);
    }
  }
}*/
