#include "ILS.hpp"

#include "BL.hpp"

#include <vector>
#include <cmath>

ILS::ILS(const Datos& data){
	clasificador.entrena(data);
	
	Rand::setUniformFloat(0.0, 1.0);
	Rand::setUniformInt(0, data.sizeAttr()-1);
	s.resize(data.sizeAttr());
	for(unsigned int i = 0; i < data.sizeAttr(); ++i){
		s[i] = Rand::uniformRndDistF();
	}
	
	BL::optimiza(clasificador, s, 1000, 0.4);
	
	clasificador.setPesos(s);
	valS = clasificador.funcionObjetivo5fEntr();
	
	sol = s;
	valSol = valS;
	
	numCarMut = ceil(0.1 * data.sizeAttr());
}

void ILS::desarrolla(){
	for(unsigned int i = 0; i < 14; ++i){
		s1 = s;
		mutacion();
		BL::optimiza(clasificador, s1, 1000, 0.4);
		clasificador.setPesos(s1);
		valS1 = clasificador.funcionObjetivo5fEntr();
		if(valS1 > valS){
			s = s1;
			valS = valS1;
		}
		if(valS>valSol){
			sol = s;
			valSol = valS;
		}
	}
}

void ILS::mutacion(){
	for(unsigned int i = 0; i < numCarMut; ++i){
		Utils::mov(s1, Rand::uniformRndDistI());
	}
}

vector<double> BLReiterada::computaPesos(const Datos& data){
	ILS alg(data);
	
	alg.desarrolla();
	
	return alg.getSolucion();
}
