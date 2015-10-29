#include "Point.h"

NodoKD::NodoKD()
{
    this->izq = NULL;
    this->der = NULL;
}

NodoKD::~NodoKD()
{

}

NodoKD* NodoKD::darIzquierdo()
{
    return this->izq;
}

void NodoKD::setIzquierdo( NodoKD* nI )
{
    this->izq = nI;
}

NodoKD* NodoKD::darDerecho()
{
    return this->der;
}

void NodoKD::setDerecho( NodoKD* nD )
{
    this->der = nD;
}

Point NodoKD::darPoint()
{
    return this->p;
}

void NodoKD::setPoint( Point nP )
{
    this->p = nP;
}

char NodoKD::darTag()
{
    return this->tag;
}

void NodoKD::setTag( char nT )
{
    this->tag = nT;
}

bool NodoKD::insertarNodo( NodoKD* n )
{
    if(this->darTag() == 'x')
    {
        if(n->darPoint().x <= this->darPoint().x)
        {
            if(this->darIzquierdo() == NULL)
            {
                n->setTag( 'y' );
                this->setIzquierdo( n );
                return true;
            }
            else
            {
                return this->darIzquierdo()->insertarNodo( n );
            }
        }
        else
        {
            if(this->darDerecho() == NULL)
            {
                n->setTag( 'y' );
                this->setDerecho( n );
                return true;
            }
            else
            {
                return this->darDerecho()->insertarNodo( n );
            }
        }
    }
    else if(this->darTag() == 'y')
    {
        if( n->darPoint().y <= this->darPoint().y)
        {
            if(this->darIzquierdo() == NULL)
            {
                n->setTag( 'z' );
                this->setIzquierdo( n );
                return true;
            }
            else
            {
                return this->darIzquierdo()->insertarNodo( n );
            }
        }
        else
        {
            if(this->darDerecho() == NULL)
            {
                n->setTag( 'z' );
                this->setDerecho( n );
                return true;
            }
            else
            {
                return this->darDerecho()->insertarNodo( n );
            }
        }
    }
    else if(this->darTag() == 'z')
    {
        if( n->darPoint().z <= this->darPoint().z)
        {
            if(this->darIzquierdo() == NULL)
            {
                n->setTag( 'x' );
                this->setIzquierdo( n );
                return true;
            }
            else
            {
                return this->darIzquierdo()->insertarNodo( n );
            }
        }
        else
        {
            if(this->darDerecho() == NULL)
            {
                n->setTag( 'x' );
                this->setDerecho( n );
                return true;
            }
            else
            {
                return this->darDerecho()->insertarNodo( n );
            }
        }
    }
    else
    {
        return false;
    }
}

bool eliminarNodo( NodoKD* n );

NodoKD* NodoKD::buscarNodo( Point p )
{
    NodoKD* n = NULL;

    if(this->p == p)
    {
        n = this;
    }

    if(this->izq != NULL && n == NULL)
    {
        n = this->izq->buscarNodo(p);
    }

    if(this->der != NULL && n == NULL)
    {
        n = this->der->buscarNodo(p);
    }

    return p;
}

NodoKD* buscarVecinoMasCercano( NodoKD* n );
std::vector< NodoKD > buscarNodosRango( std::vector< NodoKD* > vec, float x1, float x2, float y1, float y2, float z1, float z2 );

void NodoKD::recorridoPreOrden()
{
    std::cout << this->darPoint() << std::endl;

    if(this->darIzquierdo() != NULL)
    {
        this->darIzquierdo()->recorridoPreOrden();
    }

    if(this->darDerecho() != NULL)
    {
        this->darDerecho()->recorridoPreOrden();
    }
}

void NodoKD::recorridoInOrden()
{
    if(this->darIzquierdo() != NULL)
    {
        this->darIzquierdo()->recorridoInOrden();
    }

    std::cout << this->darPoint() << std::endl;

    if(this->darDerecho() != NULL)
    {
        this->darDerecho()->recorridoInOrden();
    }
}

void NodoKD::recorridoPosOrden()
{
    if(this->darIzquierdo() != NULL)
    {
        this->darIzquierdo()->recorridoPosOrden();
    }

    if(this->darDerecho() != NULL)
    {
        this->darDerecho()->recorridoPosOrden();
    }

    std::cout << this->darPoint() << std::endl;
}
