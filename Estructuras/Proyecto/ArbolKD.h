#ifndef __ARBOLKD__H__
#define __ARBOLKD__H__

#include <vector>
#include "NodoKD.h"

class ArbolKD
{
  protected:
    NodoKD* raiz;

  public:
    ArbolKD();
    ~ArbolKD();
    NodoKD* darRaiz();
    void setRaiz( NodoKD* nR );
    bool insertarNodo( float x, float y, float z );
    bool eliminarNodo( float x, float y, float z );
    NodoKD* buscarNodo( float x, float y, float z );
    NodoKD* buscarVecinoMasCercano( float x, float y, float z );
    std::vector< NodoKD* > buscarNodosRango( float x1, float x2, float y1, float y2, float z1, float z2 );
    void recorridoPreOrden();
    void recorridoInOrden();
    void recorridoPosOrden();
};

#include "ArbolKD.hxx"

#endif //__ARBOLKD__H__
