#include "ES.hpp"

#include "Datos.hpp"
#include "Clasificador.hpp"
#include "utils.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

vector<double> SimulatedAnnealing::computaPesos(const Datos& data){
	ES alg(data);
	alg.desarrolla();
	return alg.getSolucion();
}

ES::ES(const Datos& entr){
	Rand::setUniformFloat(0.0, 1.0);
	Rand::setNormalFloat(0, 0.3);
	Rand::setUniformInt(0, entr.sizeAttr()-1);
	
	sol.resize(entr.sizeAttr());
	for(unsigned int i = 0; i < entr.sizeAttr(); ++i){
		sol[i] = Rand::uniformRndDistF();
	}
	
	clasificador.entrena(entr);
	clasificador.setPesos(sol);
	
	valSol = clasificador.funcionObjetivo5fEntr();
	actual = sol;
	valActual = valSol;
	vecino = actual;
	
	maxVecinos = 10*entr.size();
	maxExitos = maxVecinos * 0.1;
	M = 15000/(maxVecinos);
	
	initT();
	
	beta = (T0-Tf)/(M*T0*Tf);
	
}

void ES::desarrolla(){
	
	do{
		for(nVecinos = 0, nExitos = 0; funcL(nVecinos, nExitos); ++nVecinos){
			Utils::mov(vecino, Rand::uniformRndDistI());
			clasificador.setPesos(vecino);
			valVecino = clasificador.funcionObjetivo5fEntr();
			
			difF=valActual - valVecino;
			if(aceptaVecino()){
				actualizaSol();
				++nExitos;
			}
			
		}
		
		funcG(Tk);
		
	}while(Tf<=Tk && nExitos!=0);
	
}

bool ES::aceptaVecino() const{
	if(difF<0) return true;
	else{
		if(Rand::uniformRndDistF() <= exp(-difF/Tk))
			return true;
		else return false;
	}
}

void ES::actualizaSol(){
	actual = vecino;
	valActual = valVecino;
	if(valActual > valSol){
		sol = actual;
		valSol = valActual;
	}
}

void ES::initT(){
	T0=(0.3 * valSol)/-log(0.3);
	Tf=0.001;
	Tk = T0;
	if(T0<Tf){
		cerr<<T0<<" grados    Valoracion: "<<valSol<<endl;
		throw runtime_error("Temperatura final mayor que temperatura inicial");
	}
}

void ES::funcG(const double& Tant){
	Tk=Tant/(1+beta*Tant);
}

bool ES::funcL(unsigned int nVec, unsigned int nExi) const{
	return nVec < maxVecinos && nExi < maxExitos;
}

const vector<double>& ES::getSolucion() const{
	return sol;
}

const double& ES::getValSolucion() const{
	return valSol;
}

const double& ES::getT0() const{
	return T0;
}
