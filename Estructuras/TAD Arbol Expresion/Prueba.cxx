#include "ArbolEx.h"
#include <iostream>

int main()
{
    ArbolEx* a = new ArbolEx();

    a->generarExpresionPrefija();

    std::string a0 = "+";
    a->agregarNodoPrefijo(a0);

    std::string a1 = "*";
    a->agregarNodoPrefijo(a1);

    std::string a2 = "2";
    a->agregarNodoPrefijo(a2);

    std::string a3 = "6";
    a->agregarNodoPrefijo(a3);

    std::string a4 = "/";
    a->agregarNodoPrefijo(a4);

    std::string a5 = "3";
    a->agregarNodoPrefijo(a5);

    std::string a6 = "8";
    a->agregarNodoPrefijo(a6);

    a->generarExpresionPosfija();
}
