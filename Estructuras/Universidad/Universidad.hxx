#include "Universidad.h"

template <class T>
Universidad<T>::Universidad(std::string nombreUniversidad)
{
    nombre = nombreUniversidad;
}

template <class T>
std::string Universidad<T>::getNombre()
{
    return nombre
}

template <class T>
T Universidad<T>::buscarFacultad(std::string nombreFacultad)
{
    T temp;

    for(std::list<T>::iterator it = facultades.begin(); it != facultades.end(); it++)
    {
        if(nombre.compare(it->getNombre()) == 0))
        {
            temp = *it;
        }
    }

    return temp;
}

template <class T>
bool Universidad<T>::agregarFacultad(std::string nombreFacultad)
{
    T facultad = Universidad<T>::buscarFacultad(nombreFacultad);

    if(facultad == NULL)
    {
        facultad = T(nombreFacultad);
        facultades.push_back(facultad);

        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool Universidad<T>::eliminarFacultad(std::string nombreFacultad)
{
    T facultad = Universidad<T>::buscarFacultad(nombreFacultad);

    if(facultad != NULL)
    {
        facultades.remove(facultad);

        return true;
    }
    else
    {
        return false;
    }
}
