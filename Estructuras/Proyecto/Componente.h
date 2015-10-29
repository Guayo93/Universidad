#ifndef __COMPONENTE__H__
#define __COMPONENTE__H__

#include "ObjectView.h"
#include "ArbolKD.h"
#include <string>
#include <fstream>
#include <sstream>


class Componente
{
  public:
    Componente();
    ~Componente();

    ObjectView* load(std::string archivo);

  public:
    std::string name;
    ObjectView* obj;
    int nCant;
    ArbolKD* puntos;
};

#include "Componente.hxx"

#endif
