//Busqueda local

#ifndef _BL_H_
#define _BL_H

#include "Datos.hpp"
#include "Clasificador.hpp"
#include "Algevo.hpp"

#include <vector>


using namespace std;



namespace BL
{	
	
	vector<double> computaPesos(const Datos& data);
	
	//devuelve el mismo vector si no encuentra solucion mejor
	vector<double> generaSol(vector<double> pesos, const unsigned int maxVecinos,
						const unsigned int maxEval, const double radio,
						const Datos& dataEntr);
						
	void optimiza(Clasificador* cla, Alg::Cromosoma& cromo,
						const unsigned int maxEval, const double radio, unsigned int &numVals);
						
	void optimiza(Clasificador& cla, vector<double>& pesos,
						const unsigned int maxEval, const double radio);
}


#endif
