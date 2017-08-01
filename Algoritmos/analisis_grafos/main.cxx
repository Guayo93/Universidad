#include <iostream>
#include <fstream>
#include "Grafo.h"

int main( )
{
  Grafo* grafo;
  int numVertices, numAristas, origen, destino, peso, i = 0;
  std::string nomArchivo;

  std::cout << "Como se llama el archivo de entrada?" << std::endl;
  cin >> nomArchivo;

  std::ifstream archEntrada;
  archEntrada.open( nomArchivo );

  if( !archEntrada )
  {
    std::cout << "Error de archivo" << std::endl;
    exit( 1 );
  }

  archEntrada >> numVertices;
  grafo = new Grafo( numVertices );

  archEntrada >> numAristas;

  while( i < numAristas && archEntrada >> origen >> destino >> peso )
  {
    grafo->agregarArista( origen, destino, peso );
  }
}
