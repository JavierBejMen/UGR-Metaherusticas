#ifndef _ILS_H_
#define _ILS_H_

#include "Datos.hpp"
#include "Clasificador.hpp"

#include <vector>

using namespace std;

namespace BLReiterada{
	vector<double> computaPesos(const Datos& data);
}


class ILS{
public:
	ILS(const Datos& data);
	
	void desarrolla();
	
	inline vector<double> getSolucion() const{return sol;}
	inline double getValSolucion() const{return valSol;}

private:
	vector<double> sol, s, s1;
	double valSol, valS, valS1;
	Clasificador clasificador;
	unsigned int numCarMut;
	
	void mutacion();
	
};



#endif
