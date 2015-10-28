#ifndef __COMPONENTE__H__
#define __COMPONENTE__H__

#include "ObjectView.h"
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
      
};

#include "Componente.hxx"

#endif
