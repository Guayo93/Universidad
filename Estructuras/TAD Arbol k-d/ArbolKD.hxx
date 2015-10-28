#include "Point.h"

ArbolKD::ArbolKD()
{
    this->raiz = NULL;
}

ArbolKD::~ArbolKD()
{

}

NodoKD* ArbolKD::darRaiz()
{
    return this->raiz;
}

void ArbolKD::setRaiz( NodoKD* nR )
{
    this->raiz = nR;
}

bool ArbolKD::insertarNodo( float x, float y, float z )
{
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;

    NodoKD* n = new NodoKD();
    n->setPoint( p );

    if(this->raiz == NULL)
    {
        n->setTag('x');
        this->setRaiz( n );
        return true;
    }
    else
    {
        return this->raiz->insertarNodo( n );
    }

    return false;
}

bool eliminarNodo( float x, float y, float z );

NodoKD* ArbolKD::buscarNodo( float x, float y, float z )
{
    NodoKD* n = NULL;

    Point p;
    p.x = x;
    p.y = y;
    p.z = z;

    if(this->raiz != NULL)
    {
        n = raiz->buscarNodo(p);
    }

    return n;
}

NodoKD* buscarVecinoMasCercano( float x, float y, float z );
std::vector< NodoKD > buscarNodosRango( float x1, float x2, float y1, float y2, float z1, float z2 );

void ArbolKD::recorridoPreOrden()
{
    if(this->raiz == NULL)
    {
        std::cout << "El arbol esta vacio." << std::endl;
    }
    else
    {
        std::cout << this->raiz->darPoint() << std::endl;

        if(this->raiz->darIzquierdo() != NULL)
        {
            this->raiz->darIzquierdo()->recorridoPreOrden();
        }

        if(this->raiz->darDerecho() != NULL)
        {
            this->raiz->darDerecho()->recorridoPreOrden();
        }
    }
}

void ArbolKD::recorridoInOrden()
{
    if(this->raiz == NULL)
    {
        std::cout << "El arbol esta vacio." << std::endl;
    }
    else
    {
        if(this->raiz->darIzquierdo() != NULL)
        {
            this->raiz->darIzquierdo()->recorridoInOrden();
        }

        std::cout << this->raiz->darPoint() << std::endl;

        if(this->raiz->darDerecho() != NULL)
        {
            this->raiz->darDerecho()->recorridoInOrden();
        }
    }
}

void ArbolKD::recorridoPosOrden()
{
    if(this->raiz == NULL)
    {
        std::cout << "El arbol esta vacio." << std::endl;
    }
    else
    {
        if(this->raiz->darIzquierdo() != NULL)
        {
            this->raiz->darIzquierdo()->recorridoPosOrden();
        }

        if(this->raiz->darDerecho() != NULL)
        {
            this->raiz->darDerecho()->recorridoPosOrden();
        }

        std::cout << this->raiz->darPoint() << std::endl;
    }
}
