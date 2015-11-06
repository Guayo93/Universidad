#ifndef __ARISTA__H__
#define __ARISTA__H__

#include "Vertice.h"

template< class T >
class Arista
{
  protected:
    T origen;
    T destino;
    bool marca;

  public:
    Arista();
    ~Arista();
    T darOrigen();
    void setOrigen( T nOri );
    T darDestino();
    void setDestino( T nDes );
    bool darMarca();
    void marcar();
    void desmarcar();
};

#include "Arista.hxx"

#endif // __ARISTA__H__
