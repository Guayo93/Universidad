#ifndef NODO__H
#define NODO__H

#include <vector>

template <class T>
class Nodo
{
  protected:
    T dato;
    std::vector <Nodo <T>* > hijos;

  public:
    Nodo();
    ~Nodo();
    bool esHoja();
    T& obtenerDato();
    void fijarDato(T& nDato);
    std::vector< Nodo<T>* > obtenerHijos();
    void limpiarHijos();
    void adicionarHijo(T& dato);
    void eliminarHijo(T& dato);
    Nodo<T>* buscarHijo(T& dato);
    void recorrerHijos();
};

#include "Nodo.hxx"

#endif // NODO__H
