#ifndef __VERTICE__H__
#define __VERTICE__H__

#include <vector>

template < class T >
class Vertice
{
  protected:
    T info;
    std::vector< Vertice< T >* > conexiones;
    bool marca;

  public:
    Vertice();
    ~Vertice();
    T darInfo();
    void setInfo( T nInfo );
    std::vector< Vertice< T >* > darConexiones();
    void setConexiones( std::vector< Vertice< T >* > nAris );
    bool darMarca();
    void marcar();
    void desmarcar();
    Vertice< T >* buscarArista( T infDes );
    bool agregarArista( Vertice< T >* ar );
    bool eliminarArista( Vertice< T >* ar );
    void marcarAdyacentes( bool esBusqueda );
};

#include "Vertice.hxx"

#endif //__VERTICE __H__
