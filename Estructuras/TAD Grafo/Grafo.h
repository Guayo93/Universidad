#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <vector>
#include "Vertice.h"

template < class T >
class Grafo
{
  protected:
    std::vector< Vertice< T >* > vertices;
    std::vector< std::vector< int > > aristas;

  public:
    Grafo();
    ~Grafo();
    std::vector< Vertice< T >* > darVertices( );
    void setVertices( std::vector< Vertice< T >* > verts );
    std::vector< std::vector< int > > darAristas( );
    void setAristas( std::vector< int > aris[]);
    int darOrden( );
    int darTamanho( );
    Vertice< T >* buscarVertice( T info );
    bool agregarVertice( T info );
    bool eliminarVertice( T infVertice );
    bool agregarArista( T infOrigen, T infDestino );
    bool eliminarArista( T infOrigen, T infDestino );
    void desmarcarVertices();
    int darNumeroComponentesConectados();
};

#include "Grafo.hxx"

#endif // __GRAFO__H__
