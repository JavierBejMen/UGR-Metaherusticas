//Clasificador 1-nn

#ifndef _CLASIFICADOR_H_
#define _CLASIFICADOR_H_

#include "Datos.hpp"
#include "utils.hpp"


#include <string>
#include <vector>


using namespace std;

class Clasificador
{
public:
	Clasificador() = default;
	
	void entrena(const Datos& entr, const Datos& prb);
	void setPesos(const vector<double>& w);
	

	
	//valida solo el clasificador 1-nn
	void valida(string name);
	
	//todo algoritmo tiene una funcion computePesos, que devuelve los pesos de la solucion y recibe como parametro los datos de la relacion.
	void valida(string name, string nameAlg, vector<double> (* algorithim)(const Datos&)); 
	double validaSol();
	
	double validaEntr();
	
private:
	Datos entrenamiento;
	Datos prueba;
	
	//Variables para la validacion de soluciones
	//Inicializadas en entrena()
	unsigned int sizeAttr;
	unsigned int sizeEntr;
	unsigned int sizePrb;
	
	//Inicializadas en las validaciones
	double tasa;
	double result;
	double minDist;
	double aux;
	unsigned int posDato;
	unsigned int numAciertos;
	
	vector<double> pesos;
	
	
	double validaPrueba();
	
	
	
};


#endif
