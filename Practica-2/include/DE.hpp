#ifndef _DE_H_
#define _DE_H_

#include "Clasificador.hpp"


using namespace std;
class DERnd;

namespace DiferencialEvolution{
	vector<double> computaPesosDERand(const Datos& data);
	vector<double> computaPesosDEcurr(const Datos& data);
}

class DE{
public:
	DE(const Datos& data, unsigned int tamPoblacion, double pCruce, 
		unsigned int maxEvaluaciones, double valorF);

	void desarrolla();
	
	vector<double> getSolucion() const;
	double getValSolucion() const;
	
protected:
	class Agente{
	public:
		Agente();
		Agente(Clasificador *clasi, unsigned int numAttrib);
		void inicializa();
		void inicializa(double val);
		void valora();
		double getValoracion() const;
		unsigned int size() const;
		
		Agente& operator=(const Agente& otro);
		bool operator>(const Agente& otro) const;
		bool operator>(const double& otro) const;
		double& operator[](const unsigned pos);
		
		vector<double> getPesos() const;
		
	private:
		vector<double> pesos;
		unsigned int nAttr;
		double valoracion;
		Clasificador* clasificador;
	};
	
	vector<Agente> Pact, Psig;
	Agente V;
	
	unsigned int nP;
	unsigned int nAttr;
	Clasificador clasificador;
	
	unsigned int numVals, maxVals;
	double CR;
	double F;
	unsigned int r1, r2, r3, jRand;
	
	Agente sol;
	unsigned int posSol;
	double valSol;
	
	virtual void selecPadres(const unsigned int i);
	virtual void muta(unsigned int i) = 0;
	
	void sustitucion();
	
	void actualizaSol();
};

class DERnd: public DE{
public:
	DERnd(const Datos& data, unsigned int tamPoblacion, double pCruce, 
		unsigned int maxEvaluaciones, double valorF);
	
private:
	void muta(const unsigned i);
	
};

class DEBest: public DE{
public:
	DEBest(const Datos& data, unsigned int tamPoblacion, double pCruce, 
		unsigned int maxEvaluaciones, double valorF);
		
private:
	void muta(const unsigned i);
	void selecPadres(const unsigned int i);
};
#endif






