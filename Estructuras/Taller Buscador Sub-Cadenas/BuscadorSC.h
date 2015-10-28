#ifndef __BUSCADORSC__H__
#define __BUSCADORSC__H__

class BuscadorSC
{
	protected:
		std::string cadenaABuscar;
	public:
		BuscadorSC();
		std::string obtenerSubcadena();
		void fijarSubCadena(std::string subCadena);
		void buscarSubCadena(std::ifstream archivo);
		void buscarInicio(std::string cadena, std::stack pilaInicio);
		void buscarDentro(std::string cadena, std::stack pilaDentro);
		void buscarInvertida(std::string cadena, std::stack pilaInvertida);
};

#include "BuscadorSC.hxx"

#endif //__BUSCADORSC__H__
