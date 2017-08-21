#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include "Grafo.h"

int Dijkstra( Grafo g , int inicio , int fin ){
  std::vector<vertex> vertices;//create vertex set Q
  for( int i = 0 ; i < g.nVertices ; ++i ){
    vertex v;
    v.dist = std::numeric_limits<int>::max();
    v.prev = -1;
    v.index = i;
    vertices.push_back(v);
  }
  vertices[inicio].dist = 0;
  std::priority_queue<vertex> q;
	for( int i = 0 ; i < vertices.size() ; i++ )
	{
		q.push( vertices[i] );
	}
  while( !q.empty() )
  {
    int u = q.top().index;
    q.pop();
    std::vector<int> vecinos = g.getVecinos( u );
    for( int i = 0 ; i < vecinos.size() ; ++i )
    {
      int v = vecinos[i];
      int weight = vertices[u].dist + g.getPeso(u,v);
      if( vertices[v].dist > weight )
      {
        vertices[v].dist = weight;
        vertices[v].prev = u;
        q.push( vertices[v] );
      }
      if( v == fin ){
        while( !q.empty() ){
          q.pop();
        }
      }
    }
  }
  //camino
  std::vector<int> camino;
  int pos = fin;
  while( pos != inicio )
  {
    camino.push_back( pos );
    pos = vertices[pos].prev;
  }
  //Push inicio
  camino.push_back( pos );
  //Reverse
  std::reverse( camino.begin(), camino.end());
  int w = 0;
  for( int i = 1 ; i < camino.size() ; i++ )
  {
    w+=g.getPeso(camino[i-1],camino[i]);
  }
  return w;
}

//-----------------------------------------------------

int Kruskal( Grafo g , int inicio , int fin ){
  std::vector<arc> edges;
  for (int i = 0; i < g.nVertices; i++) {
    for (int j = 0; j < g.nVertices ; j++) {
      if( g.existeArista(i,j) ){
        arc a(i,j, g.getPeso(i,j));
        edges.push_back(a);
      }
    }
  }

  std::sort( edges.begin() , edges.end() );
  DisjointSets ds(g.nVertices);

  typedef std::vector<arc>::iterator arcIt;
  for (arcIt it=edges.begin(); it!=edges.end(); it++)
  {
    int u = it->start;
    int v = it->end;

    int set_u = ds.find(u);
    int set_v = ds.find(v);

    if (set_u != set_v)
    {
      ds.merge(set_u, set_v);
    }
  }
  Grafo gaux(g.nVertices);
  for( arcIt it = edges.begin() ; it != edges.end() ; it++ ){
    gaux.agregarArista(*it);
  }
  return gaux.bfs(inicio,fin);
}


//---------------------------------------------


int FloydWarshall( Grafo g , int inicio , int fin ){
  int dist[g.nVertices][g.nVertices];
  for (int i = 0; i < g.nVertices; i++) {
    for (int j = 0; j < g.nVertices; j++) {
      if( g.existeArista(i,j) && i!= j){
        dist[i][j] = g.getPeso(i,j);
      }else{
        dist[i][j] = std::numeric_limits<int>::max();
      }
    }
  }
  for (int i = 0; i < g.nVertices; i++) {
    dist[i][i] = 0;
  }
  for (int k = 0; k < g.nVertices; k++) {
    for (int i = 0; i < g.nVertices; i++) {
      for (int j = 0; j < g.nVertices; j++) {
        if( dist[i][j] > dist[i][k] + dist[k][j] &&
          dist[i][k] != std::numeric_limits<int>::max() &&
          dist[k][j] != std::numeric_limits<int>::max() ){
          //std::cout << "dist["<<i<<"]["<<j<<"]="<< dist[i][k] + dist[k][j]<< '\n';
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  return dist[inicio][fin];
}

//----------------------------------------------------

int main()
{
  srand( time( NULL ) );
  Grafo* grafo;
  int numVertices, numAristas, origen, destino, peso, i = 0;
  std::string nomArchivo;

  std::cout << "Como se llama el archivo de entrada?" << std::endl;
  std::cin >> nomArchivo;

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

  int nodoInicio = rand() % numVertices + 1;
  int nodoFin = rand() % numVertices + 1;

  long inicioDijkstra = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now(  ).time_since_epoch(  ) ).count( );
  int pesoDijkstra = Dijkstra( *grafo, nodoInicio, nodoFin);
  long finDijkstra = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
  long tiempoDijkstra = finDijkstra - inicioDijkstra;
  std::cout << "Termina Algoritmo de Dijkstra" << std::endl;

  long inicioKruskal = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now(  ).time_since_epoch(  ) ).count( );
  int pesoKruskal = Kruskal( *grafo, nodoInicio, nodoFin);
  long finKruskal = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
  long tiempoKruskal = finKruskal - inicioKruskal;
  std::cout << "Termina Algoritmo de Kruskal" << std::endl;

  long inicioFloydWarshall  = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now(  ).time_since_epoch(  ) ).count( );
  int pesoFloydWarshall = FloydWarshall( *grafo, nodoInicio, nodoFin);
  long finFloydWarshall = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
  long tiempoFloydWarshall = finFloydWarshall - inicioFloydWarshall;
  std::cout << "Termina Algoritmo de Floyd-Warshall" << std::endl << std::endl;

  std::cout << "Nodo de Inicio: " << nodoInicio << std::endl << "Nodo de Fin: " << nodoFin << std::endl << "Dijkstra: " << pesoDijkstra << ", " << tiempoDijkstra << std::endl << "Kruskal: " << pesoKruskal << ", " << tiempoKruskal << std::endl << "Floyd-Warshall: " << pesoFloydWarshall << ", " << tiempoFloydWarshall << std::endl;

  return 0;
}
