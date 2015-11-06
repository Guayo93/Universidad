#include <iostream>
#include "Grafo.h"

int main()
{
  Grafo<int>* g = new Grafo<int>();

  for(int i  = 0; i < 5; i++)
  {
    g->agregarVertice(i);
  }

  std::cout << "Contenido:" << std::endl;

  for(int i = 0; i < g->darVertices().size(); i++)
  {
    std::cout << g->darVertices()[i]->darInfo() << std::endl;
  }

  std::cout << "Orden: " << g->darOrden() << std::endl;

  std::cout << "Matriz Adjacencia Inicial:" << std::endl;

  for(int i = 0; i < g->darAristas().size(); i++)
  {
    std::cout << " |";

    for(int j = 0; j < g->darAristas()[i].size(); j++)
    {
      std::cout << g->darAristas()[i][j] << "| ";
    }

    std::cout << std::endl;
  }

  g->agregarArista(0, 1);
  g->agregarArista(1, 0);
  g->agregarArista(0, 0);
  g->agregarArista(2, 3);
  g->agregarArista(3, 4);
  g->agregarArista(4, 0);

  std::cout << "Matriz Adjacencia Final:" << std::endl;

  for(int i = 0; i < g->darAristas().size(); i++)
  {
    std::cout << " |";

    for(int j = 0; j < g->darAristas()[i].size(); j++)
    {
      std::cout << g->darAristas()[i][j] << "| ";
    }

    std::cout << std::endl;
  }

  std::cout << "Numero de Componentes Conectados: " << g->darNumeroComponentesConectados() << std::endl;
}
