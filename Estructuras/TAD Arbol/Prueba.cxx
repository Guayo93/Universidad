#include <iostream>
#include "Arbol.h"

int main()
{
  Arbol<int>* a = new Arbol<int>();

  Nodo<int>* n = new Nodo<int>();

  int i = 123; //RAIZ

  n->fijarDato(i);

  a->fijarRaiz(n);

  int i1 = 321; //HIJO 1 DE RAIZ

  a->insertarNodo(i, i1);

  int i2 = 987; //HIJO 1 DE 321

  a->insertarNodo(i1, i2);

  int i3 = 789; //HIJO 2 DE 321

  a->insertarNodo(i1, i3);

  int i4 = 654;  //HIJO 2 DE RAIZ

  a->insertarNodo(i, i4);

  int i5 = 456;  //HIJO 1 DE 987

  a->insertarNodo(i2, i5);

  int i6 = 351;  //HIJO 3 DE RAIZ

  a->insertarNodo(i, i6);

  int i7 = 957;  //HIJO 1 DE 654

  a->insertarNodo(i4, i7);

  int i8 = 751;  //HIJO 2 DE 654

  a->insertarNodo(i4, i8);

  int i9 = 953;  //HIJO 2 DE 987

  a->insertarNodo(i2, i9);

  int i0 = 500;  //HIJO 1 DE 953

  a->insertarNodo(i9, i0);

  a->recorrido();
}
