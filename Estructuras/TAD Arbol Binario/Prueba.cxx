#include <iostream>
#include "Arbol.h"

int main()
{
    bool agrego;

    Arbol<int>* a = new Arbol<int>();

    Nodo<int>* n = new Nodo<int>();

    int i1 = 15;

    n->fijarDato(i1);

    a->fijarRaiz(n);

    int i2 = 8;

    agrego = a->agregarNodo(i2);

    int i3 = 7;

    agrego = a->agregarNodo(i3);

    int i4 = 22;

    agrego = a->agregarNodo(i4);

    int i5 = 11;

    agrego = a->agregarNodo(i5);

    int i6 = 21;

    agrego = a->agregarNodo(i6);

    int i7 = 17;

    agrego = a->agregarNodo(i7);

    int i8 = 31;

    agrego = a->agregarNodo(i8);

    int i9 = 4;

    agrego = a->agregarNodo(i9);

    int i10 = 5;

    agrego = a->agregarNodo(i10);

    int i11 = 1;

    agrego = a->agregarNodo(i11);

    int i12 = 28;

    agrego = a->agregarNodo(i12);

    int i13 = 19;

    agrego = a->agregarNodo(i13);

    int i14 = 25;

    agrego = a->agregarNodo(i14);

    int i15 = 33;

    agrego = a->agregarNodo(i15);

    std::cout << "Pre-Orden:" << std::endl;
    a->recPreOrden();

    std::cout << std::endl << "In-Orden:" << std::endl;
    a->recInOrden();

    std::cout << std::endl << "Pos-Orden:" << std::endl;
    a->recPosOrden();
}
