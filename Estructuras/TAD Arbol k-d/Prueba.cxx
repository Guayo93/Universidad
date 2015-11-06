#include <iostream>
#include "ArbolKD.h"

int main()
{
    ArbolKD* arbol = new ArbolKD();

    arbol->insertarNodo(35, 40, 55);
    arbol->insertarNodo(50, 10, 45);
    arbol->insertarNodo(60, 75, 65);
    arbol->insertarNodo(80, 65, 95);
    arbol->insertarNodo(85, 15, 25);
    arbol->insertarNodo(5, 45, 15);
    arbol->insertarNodo(25, 35, 35);
    arbol->insertarNodo(90, 5, 55);

    std::cout << "Pre-Orden:" << std::endl;
    arbol->recorridoPreOrden();

    std::cout << std::endl << arbol->buscarVecinoMasCercano(92, 8, 50)->darPoint() << std::endl;
}
