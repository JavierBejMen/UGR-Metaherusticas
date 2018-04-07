#include "DE.hpp"

#include "Clasificador.hpp"
#include "utils.hpp"

#include <iostream>
#include <cmath>

using namespace std;

DE::Agente::Agente(){
	clasificador = nullptr;
	valoracion = 0;
	nAttr = 0;
}

DE::Agente::Agente(Clasificador* clasi, unsigned int numAtrib){
	clasificador = clasi;
	valoracion = 0;
	nAttr = numAtrib;
}

void DE::Agente::inicializa(){
	pesos.resize(nAttr);
	
	for(unsigned int i = 0; i < nAttr; ++i){
		pesos[i]=Rand::uniformRndDistF();
	}
	valora();
}

void DE::Agente::inicializa(double val){
	pesos.resize(nAttr, val);
	
	valora();
}

void DE::Agente::valora(){
	clasificador->setPesos(pesos);
	valoracion = clasificador->funcionObjetivo5fEntr();
}

double DE::Agente::getValoracion() const{
	return valoracion;
}

DE::Agente& DE::Agente::operator =(const DE::Agente& otro){
	if(this!=&otro){
		clasificador = otro.clasificador;
		valoracion = otro.valoracion;
		pesos = otro.pesos;
		nAttr = otro.nAttr;
	}
	return *this;
}

bool DE::Agente::operator >(const DE::Agente& otro) const{
	return valoracion>otro.valoracion;
}

bool DE::Agente::operator >(const double& otro) const{
	return valoracion>otro;
}

double& DE::Agente::operator [](const unsigned int i){
	return pesos[i];
}

vector<double> DE::Agente::getPesos() const{
	return pesos;
}

unsigned int DE::Agente::size() const{
	return pesos.size();
}

DE::DE(const Datos& data, unsigned int tamPoblacion, double pCruce, 
	unsigned int maxEvaluaciones, double valorF){
	numVals = 0;
	maxVals = maxEvaluaciones;
	CR = pCruce;
	F = valorF;
	nAttr = data.sizeAttr();
	clasificador.entrena(data);
	
	nP = tamPoblacion;
	Pact.resize(nP);
	Psig.resize(nP);
	Rand::setUniformFloat(0, 1);
	for(unsigned int i = 0; i < nP; ++i){
		Pact[i] = Agente(&clasificador, nAttr);
		/*if(Rand::uniformRndDistF() < CR) //Para inicializar a 0 en DE/current-to-best/1
			Pact[i].inicializa(0);
		else*/
			Pact[i].inicializa();
		++numVals;
	}
	
	Rand::setUniformInt(0, nP-1);
	actualizaSol();
}

void DE::desarrolla(){
	while(numVals < maxVals){
		for(unsigned int i = 0; i < nP; ++i){
			selecPadres(i);
			V = Pact[i];
			jRand = Rand::uniformRndDistI();
			for(unsigned int j = 0; j < nAttr; ++j){
				if(Rand::uniformRndDistF() < CR || j == jRand){
					muta(j);
				}
			}
			Psig[i] = V;
			Psig[i].valora();

			++numVals;
		}
		sustitucion();
		actualizaSol();
	}
}

void DE::selecPadres(const unsigned int i){
	do{
		r1 = Rand::uniformRndDistI();
	}while(r1 == i);
	do{
		r2 = Rand::uniformRndDistI();
	}while(i == r2 || r2 == r1);
	do{
		r3 = Rand::uniformRndDistI();
	}while(i == r3 || r1 == r3 || r2 == r3);
}

void DE::sustitucion(){
	for(unsigned int i = 0; i < nP; ++i){
		if(Psig[i] > Pact[i])
			Pact[i] = Psig[i];
	}	
}

void DE::actualizaSol(){
	valSol = Utils::MIN_DOUBLE;
	for(unsigned int i = 0; i < nP; ++i){
		if(Pact[i] > valSol){
			valSol = Pact[i].getValoracion();
			posSol = i;
		}
	}
	sol = Pact[posSol];
}

vector<double> DE::getSolucion() const{
	return sol.getPesos();
}

double DE::getValSolucion() const{
	return valSol;
}

DERnd::DERnd(const Datos& data, unsigned int tamPoblacion, double pCruce, 
		unsigned int maxEvaluaciones, double valorF)
		:DE(data, tamPoblacion, pCruce,
		maxEvaluaciones, valorF){}
		
void DERnd::muta(unsigned int i){
	V[i] = Pact[r1][i] + F *(Pact[r2][i] - Pact[r3][i]);
	if(V[i] < 0) V[i] = 0;
	if(V[i] > 1) V[i] = 1;
}

namespace DiferencialEvolution{
	vector<double> computaPesosDERand(const Datos& data){
		DERnd alg(data, 50, 0.5, 15000, 0.5);
		alg.desarrolla();
		return alg.getSolucion();
	}
	vector<double> computaPesosDEcurr(const Datos& data){
		DEBest alg(data, 50, 0.5, 15000, 0.5);
		alg.desarrolla();
		return alg.getSolucion();
	}
}

DEBest::DEBest(const Datos& data, unsigned int tamPoblacion, double pCruce, 
		unsigned int maxEvaluaciones, double valorF)
		:DE(data, tamPoblacion, pCruce,
		maxEvaluaciones, valorF){}
		
void DEBest::muta(const unsigned int i){
	V[i] = V[i] + F * (sol[i] - V[i]) + F * (Pact[r1][i] - Pact[r2][i]);
	if(V[i] < 0) V[i] = 0;
	if(V[i] > 1) V[i] = 1;
}

void DEBest::selecPadres(const unsigned i){
	do{
		r1 = Rand::uniformRndDistI();
	}while(r1 == i);
	do{
		r2 = Rand::uniformRndDistI();
	}while(i == r2 || r2 == r1);
}











