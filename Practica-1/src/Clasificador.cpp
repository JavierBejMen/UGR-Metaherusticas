#include "Clasificador.hpp"

#include "Datos.hpp"
#include "Dato.hpp"
#include "utils.hpp"



#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


void Clasificador::entrena(const Datos& entr, const Datos& prb)
{
	if(entr.empty() || prb.empty())
	{
		cerr<<"Error: entrenamiento Clasificador:"<<endl;
		cerr<<entr.getMetaData()<<prb.getMetaData();
		throw runtime_error("Conjunto de entrenamiento o prueba vacio");
	}
	
	if(prb.sizeAttr() != entr.sizeAttr())
	{
		cerr<<"Error: entrenamiento Clasificador"<<endl;
		cerr<<entr.getMetaData()<<prb.getMetaData();
		throw runtime_error("Diferente numero de atributos en los datos de entrenamiento y clasificacion");
	}
	
	entrenamiento = entr;
	
	prueba = prb;
	
	sizeAttr = prb.sizeAttr();
	sizeEntr = entr.size();
	sizePrb = prb.size();
	
	
	pesos.clear();
}


double Clasificador::validaPrueba()
{
	numAciertos = 0;
	
	for(unsigned int i = 0; i < sizePrb; ++i)
	{
		posDato = -1;
		minDist = Utils::MAX_DOUBLE;
		for(unsigned int j = 0; j < sizeEntr; ++j)
		{
			aux = prueba[i].distEuclid(entrenamiento[j], pesos);
			if(aux < minDist)
			{
				posDato = j;
				minDist = aux;
			}
		}
		
		if(entrenamiento[posDato].getClass() == prueba[i].getClass())
			++numAciertos;
	}
	
	result = 100*((double)numAciertos/(double)sizePrb);
	
	return result;
}


double Clasificador::validaEntr()
{
	numAciertos = 0;
	
	for(unsigned int i = 0; i < sizeEntr; ++i)
	{
		posDato = -1;
		minDist = Utils::MAX_DOUBLE;
		for(unsigned int j = 0; j < sizeEntr; ++j)
		{
			if(i != j)
			{
				aux = entrenamiento[i].distEuclid(entrenamiento[j], pesos);
				if(aux < minDist)
				{
					posDato = j;
					minDist = aux;
				}
			}
		}
		
		if(entrenamiento[posDato].getClass() == entrenamiento[i].getClass())
			++numAciertos;
	}
	result = 100*((double)numAciertos/(double)sizeEntr);
	
	return result;
}

double Clasificador::validaSol()
{
	tasa = validaEntr();
	tasa += validaPrueba();
	tasa/=2;
	return tasa;
}

void Clasificador::valida(string name, string nameAlg, vector<double> (* algorithim)(const Datos&))
{
	Utils::resultado result; //Captura resultados parciales
	Datos dataEntr;
	Datos dataPrb;

	vector<Utils::resultado> resultados;
	string path;
	
	for(unsigned int i = 0; i < 5; ++i)
	{
		for(unsigned int j = 0; j < 2; ++j)
		{
			result.clear();
			path = FileWrapper::set5c2path(name, i, j);
			dataEntr = FileWrapper::loadData(path);
			dataPrb = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(path));
			
			entrena(dataEntr, dataPrb);
			
			//Tomamos el tiempo de algorithim
			Timer::startChrono();
			pesos = algorithim(dataEntr);
			result.first = Timer::elapsedTime();
			
			result.second = validaSol();
			
			resultados.push_back(result); //Guardamos el resultado
			
			cout<<"Conjunto "<<path<<" ------> OK!"<<endl;
		}
	}
	
	//Ya se ha realizado la validacion 5x2c
	if(resultados.size() != 10)
		throw runtime_error("Error en la validacion cruzada");
		
	
	FileWrapper::guardaResultados(resultados, name, nameAlg);
}

void Clasificador::valida(string name)
{
	Utils::resultado result; //Captura resultados parciales
	Datos dataEntr;
	Datos dataPrb;

	vector<Utils::resultado> resultados;
	string path;
	
	for(unsigned int i = 0; i < 5; ++i)
	{
		for(unsigned int j = 0; j < 2; ++j)
		{
			result.clear();
			path = FileWrapper::set5c2path(name, i, j);
			dataEntr = FileWrapper::loadData(path);
			dataPrb = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(path));
			
			//Tomamos el tiempo de entrenamiento
			Timer::startChrono();
			entrena(dataEntr, dataPrb);
			pesos.resize(sizeAttr, 1);
			result.first = Timer::elapsedTime();
			
			result.second = validaSol();
			
			resultados.push_back(result); //Guardamos el resultado
			
			cout<<"Conjunto "<<path<<" ------> OK!"<<endl;
		}
	}
	
	//Ya se ha realizado la validacion 5x2c
	if(resultados.size() != 10)
		throw runtime_error("Error en la validacion cruzada");
		
	
	FileWrapper::guardaResultados(resultados, name, "1-NN");
}

void Clasificador::setPesos(const vector<double>& w)
{
	if(w.size() != sizeAttr){
		cerr<<"w: "<<w.size()<<"  sizeAttr: "<<sizeAttr<<endl;
		throw runtime_error("No se puede asignar W a clasificador con distinto numero de atributos");
	}
	pesos = w;
}
