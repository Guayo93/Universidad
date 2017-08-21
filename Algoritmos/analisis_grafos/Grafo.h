#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <map>
#include <vector>
#include <stack>
#include <utility>
#include <queue>
#include <set>

struct DisjointSets
{
   int *parent, *rnk;
   int n;

   DisjointSets(int n)
   {
       this->n = n;
       parent = new int[n+1];
       rnk = new int[n+1];

       for (int i = 0; i <= n; i++)
       {
         rnk[i] = 0;
         parent[i] = i;
       }
     }

     int find(int u)
     {
       if (u != parent[u])
       parent[u] = find(parent[u]);
       return parent[u];
     }

     void merge(int x, int y)
     {
       x = find(x), y = find(y);
       if (rnk[x] > rnk[y]){
         parent[y] = x;
       }else {
         parent[x] = y;
       }
       if (rnk[x] == rnk[y]){
         rnk[y]++;
       }
     }
};

struct arc{
  int start;
  int end;
  int cost;
  arc( int start , int end , int cost ){
    this->start = start;
    this->end = end;
    this->cost = cost;
  }
  bool operator <( const arc& rhs ) const
	{
		return (this->cost > rhs.cost);
	}
};

struct vertex{
	int index;
	int prev;
	int dist;
	bool operator <( const vertex& rhs ) const
	{
		return (this->dist > rhs.dist);
	}
};

class Grafo{
  public:
    int nVertices;
    std::map<int, std::map<int, int> > m_adj;


    Grafo();
    Grafo( int nVertices );
    virtual ~Grafo();

    void agregarArista( int origen, int destino , int peso );
    void agregarArista( arc a );
    bool existeArista( int origen , int destino );
    int bfs( int origen , int destino );
    int getPeso( int origen , int destino );
    std::vector<int> getVecinos( int punto );
};

#include "Grafo.cxx"

#endif
