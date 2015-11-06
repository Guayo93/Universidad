#ifndef __VERTICE__H__
#define __VERTICE__H__

#include <vector>
#include "Arista.h"

template< class T >
class Vertice
{
  protected:
    T info;
    std::vector< Arista< T >* > predecesores;
    std::vector< Arista< T >* > sucesores;
    bool marca;

  public:
    Vertice();
    ~Vertice();
    T darInfo();
    void setInfo( T nInfo );
    std::vector< Arista< T >* > darPredecesores();
    void setPredecesores( std::vector< Arista< T >* > nAris );
    std::vector< Arista< T >* > darSucesores();
    void setSucesores( std::vector< Arista< T >* > nAris );
    bool darMarca();
    void marcar();
    void desmarcar();
    Arista< T >* buscarArista( T infOri, T infDes );
    bool agregarArista( Arista< T >* ar );
    bool eliminarArista( Arista< T >* ar );
    void marcarAdyacentes();
};

#include "Vertice.hxx"

#endif //__VERTICE __H__
