#ifndef __UNIVERSIDAD__H__
#define __UNIVERSIDAD__H__

#include <string.h>

template <class T>
class Universidad
{
    protected:
        std::list<T> facultades;
        std::string nombre;
    public:
        Universidad(std::string nombre);
        std::string getNombre();
        T buscarFacultad(std::string nombreFacultad);
        bool agregarFacultad(std::string nombreFacultad);
        bool eliminarFacultad(std::string nombreFacultad);
};

#include "Universidad.hxx"

#endif // UNIVERSIDAD_H_INCLUDED
