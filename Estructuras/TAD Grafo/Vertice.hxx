#include <vector>
#include <iostream>

template< class T >
Vertice< T >::Vertice()
{
  std::vector< Vertice< T >* > conexs;
  this->conexiones = conexs;
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
std::vector< Vertice< T >* > Vertice< T >::darConexiones()
{
  return this->conexiones;
}

template< class T >
void Vertice< T >::setConexiones( std::vector< Vertice< T >* > nAris )
{
  this->predecesores = nAris;
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
Vertice< T >* Vertice< T >::buscarArista( T infDes )
{
  Vertice< T >* a = NULL;

  for(int i = 0; i < conexiones.size(); i++)
  {
    if(conexiones[i]->darInfo() == infDes)
    {
      a = conexiones[i];
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
bool Vertice< T >::agregarArista( Vertice< T >* ar )
{
  if(this->buscarArista(ar->darInfo()) == NULL)
  {
    this->conexiones.push_back(ar);
    return true;
  }

  return false;
}

template< class T >
//bool Vertice< T >::eliminarArista(); Reformular

void Vertice< T >::marcarAdyacentes( bool esBusqueda )
{
  this->marcar();

  if(esBusqueda == true)
  {
    std::cout << this->darInfo() << std::endl;
  }

  for(int i = 0; i < this->conexiones.size(); i++)
  {
    if(this->conexiones[i]->darMarca() == false)
    {
      this->conexiones[i]->marcarAdyacentes(esBusqueda);
    }
  }
}
