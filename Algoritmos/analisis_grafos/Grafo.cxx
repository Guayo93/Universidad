#include "./Grafo.h"

Grafo::Grafo(){

}

Grafo::~Grafo(){

}

Grafo::Grafo( int nVertices ){
  this->nVertices = nVertices;
  for (int i = 0; i < nVertices; i++) {
    this->m_adj[i][i] = 0;
  }
}

void Grafo::agregarArista( int origen , int destino , int peso ){
  this->m_adj[origen][destino] = peso;
}

void Grafo::agregarArista( arc a ){
  this->agregarArista( a.start , a.end , a.cost );
}

bool Grafo::existeArista( int origen , int destino ){
  bool hasKey = false;
  if( this->m_adj.find(origen) != this->m_adj.end()  )
  {
    hasKey = (this->m_adj.find(origen)->second.find(destino) != this->m_adj.find(origen)->second.end() );
  }
  return hasKey;
}

int Grafo::getPeso( int origen , int destino ){
  int w = -1;
  if( this->existeArista(origen, destino) ){
      w = this->m_adj[origen][destino];
  }
  return w;
}

int Grafo::bfs( int origen , int destino ){
  std::queue<std::pair<int,int>> Q;
  std::set<int> S;
  std::pair<int,int> aux(origen,0);
  S.insert(origen);
  Q.push(aux);

  while( !Q.empty() )
  {
      std::pair<int,int> current = Q.front();
      Q.pop();
      if( current.first == destino){
        return current.second;
      }
      std::vector<int> v=this->getVecinos(current.first);
      for (int i = 0; i < v.size(); i++) {
        if( S.find(v[i]) == S.end() )
        {
          S.insert(v[i]);
          std::pair<int,int> ng(v[i],current.second + this->getPeso(current.first, v[i]));
          Q.push(ng);
        }
      }
  }
}

std::vector<int> Grafo::getVecinos( int punto )
{
	std::vector<int> res;
	typedef typename std::map<int, int>::iterator mIter;
	for( mIter it = m_adj[punto].begin() ; it != m_adj[punto].end() ; it++ )
		res.push_back( it->first );
	return res;
}
