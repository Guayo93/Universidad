#ifndef __NODOKD__H__
#define __NODOKD__H__

#include "Point.h"

class NodoKD
{
  protected:
    Point p;
    char tag;
    NodoKD* izq;
    NodoKD* der;

  public:
    NodoKD();
    ~NodoKD();
    NodoKD* darIzquierdo();
    void setIzquierdo( NodoKD* nI );
    NodoKD* darDerecho();
    void setDerecho( NodoKD* nD );
    Point darPoint();
    void setPoint( Point nP );
    char darTag();
    void setTag( char nT );
    bool insertarNodo( NodoKD* n );
    bool eliminarNodo( NodoKD* n );
    NodoKD* buscarNodo( Point p );
    NodoKD* buscarVecinoMasCercano( NodoKD* n );
    std::vector< NodoKD > buscarNodosRango( std::vector< NodoKD* > vec, float x1, float x2, float y1, float y2, float z1, float z2 );
    void recorridoPreOrden();
    void recorridoInOrden();
    void recorridoPosOrden();
};

#include "NodoKD.hxx"

#endif //__NODOKD__H__
