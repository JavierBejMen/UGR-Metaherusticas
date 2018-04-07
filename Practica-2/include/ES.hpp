#ifndef _ES_H_
#define _ES_H_

#include "Datos.hpp"
#include "Clasificador.hpp"

using namespace std;

namespace SimulatedAnnealing{
	vector<double> computaPesos(const Datos& data);
}

class ES{
public:
	ES(const Datos& entr);
	
	
	void desarrolla();
	
	const vector<double>& getSolucion() const;
	const double& getValSolucion() const;
	const double& getT0() const;
	

private:
	vector<double> sol, vecino, actual;
	double valSol, valVecino, valActual;
	double difF;
	double T0, Tf, Tk, beta;
	unsigned int M, maxVecinos, maxExitos;
	Clasificador clasificador;
	unsigned int nVecinos, nExitos;
	
	void funcG(const double& Tant);
	bool funcL(unsigned int nVec, unsigned int nExi) const;
	void initT();
	
	bool aceptaVecino() const;
	void actualizaSol();

	
	
};

#endif
