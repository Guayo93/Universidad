#include <iostream>
#include "ArbolAVL.h"

int main()
{
  bool agrego;

  ArbolAVL<int>* a = new ArbolAVL<int>();

  NodoAVL<int>* n = new NodoAVL<int>();

  int i1 = 1;

  n->fijarDato(i1);

  a->fijarRaiz(n);

  std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i2 = 2;

  agrego = a->agregarNodo(i2);

  std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i3 = 3;

  agrego = a->agregarNodo(i3);

  std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i4 = 4;

  agrego = a->agregarNodo(i4);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i5 = 5;

  agrego = a->agregarNodo(i5);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i6 = 6;

  agrego = a->agregarNodo(i6);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i7 = 7;

  agrego = a->agregarNodo(i7);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i8 = 8;

  agrego = a->agregarNodo(i8);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i9 = 9;

  agrego = a->agregarNodo(i9);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i10 = 10;

  agrego = a->agregarNodo(i10);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i11 = 11;

  agrego = a->agregarNodo(i11);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i12 = 12;

  agrego = a->agregarNodo(i12);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i13 = 13;

  agrego = a->agregarNodo(i13);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i14 = 14;

  agrego = a->agregarNodo(i14);

    std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  int i15 = 15;

  agrego = a->agregarNodo(i15);

  std::cout << "Pre-Orden:" << std::endl;
  a->recPreOrden();

  std::cout << std::endl << "In-Orden:" << std::endl;
  a->recInOrden();

  std::cout << std::endl << "Pos-Orden:" << std::endl;
  a->recPosOrden();
}
