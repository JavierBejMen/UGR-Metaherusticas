//Selfguards must come from caller
#ifndef _UTILS_H_
#define _UTILS_H_

#include "Dato.hpp"
#include "Datos.hpp"

#include <vector>
#include <limits>
#include <chrono>
#include <random>
#include <string>

using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::high_resolution_clock::time_point ChronoTimer;
typedef chrono::duration<double> UnitTimer;

namespace Utils{
	void imprimeSol(const vector<double>& solucion);
	
	const double MAX_DOUBLE = numeric_limits<double>::max();
	const double MIN_DOUBLE = numeric_limits<double>::min();
	const int MAX_INT = numeric_limits<int>::max();
	const int MIN_INT = numeric_limits<int>::min();
	
	double distPunto(const double x, const double y); 	
							
	void normaliza(vector<double>& vec);
	
	//Operador por mutacion normal
	//Se basa en el genereador definido en RAND, definir la desviacion con RAND::setNormalDist(0, desviacion)
	void mov(vector<double>& pesos, const unsigned int pos);
	
	struct resultado
	{
		double first = 0;
		double second = 0;
		
		void clear(){
			first = 0;
			second = 0;
		}

		void suma(const resultado otro){
			first += otro.first;
			second += otro.second;
		}
		
		void sumaFirst(const resultado otro){
			first += otro.first;
		}
		
		void sumaSecond(const resultado otro){
			second += otro.second;
		}
		
		void mediaSecond(unsigned int i)
		{
			second /= i;
		}
		
		void mediaFirst(unsigned int i)
		{
			first /= i;
		}
		
		void media(unsigned int i)
		{
			first /= i;
			second /= i;
		}
		
		void operator =(const resultado& otro){
			first = otro.first;
			second = otro.second;
		}
	};
	
	struct resultado5f{
		double time = 0;
		resultado valoracion;
		
		void clear(){
			time = 0;
			valoracion.clear();
		}
		
		void media(unsigned int i){
			time/=i;
			valoracion.media(i);
		}
		
		void suma(const resultado5f otro){
			time += otro.time;
			valoracion.suma(otro.valoracion);
		}
	};
	
}

namespace Timer{
	void startChrono();
	double elapsedTime();
}

namespace Rand{
	
	void initRndEngGen(unsigned int seed);
	
	double uniformRndDistF();
	void setUniformFloat(double low, double high);
	
	double normalRndDistF();
	void setNormalFloat(double low, double high);
	
	unsigned int uniformRndDistI();
	void setUniformInt(unsigned int low, unsigned int high);
}

namespace FileWrapper{
	const Datos& loadData(const string& pathFile);
	
	string set5c2path(string name, const unsigned int i, const unsigned int j);
	string getPathDataOpuesto(string pathFile);
	
	const Datos& load5fData(const string& name, unsigned int exclude);
	
	void guardaResultados(const vector<Utils::resultado>& resultados,const string& relation,const string& algorithim);
	void guardaResultados(const vector<Utils::resultado5f>& resultados,const string& relation,const string& algorithim);
}
#endif
