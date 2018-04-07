#include "BL.hpp"

#include "Datos.hpp"
#include "Clasificador.hpp"
#include "Relief.hpp"
#include "utils.hpp"
#include "Algevo.hpp"


#include <vector>




using namespace std;

namespace BL
{
	namespace
	{
		Clasificador c1nn;
		vector<double> mejorSol, auxpesos;
		double mejorTasa, tasa;
		vector<int> pos;
		unsigned int i,j,k;
		unsigned int aux;
		unsigned int sizePesos;
	}

	vector<double> computaPesos(const Datos& data)
	{
		vector<double> pesos;//Relief::computaPesos(data);
		Rand::setUniformFloat(0.0, 1.0);
		pesos.resize(data.sizeAttr());
		for(unsigned int i = 0; i < data.sizeAttr(); ++i)
		{
			pesos[i] = Rand::uniformRndDistF();
		}
	
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		

		pesos = generaSol(pesos, 20*data.sizeAttr(), 15000, 0.3, data,
						dataPrueba);
	
		return pesos;
	}

	vector<double> generaSol(vector<double> pesos,const unsigned int maxVecinos,
						const unsigned int maxEval,const double radio,
						const Datos& dataEntr, const Datos& dataPrueba)
	{
		sizePesos = pesos.size();
		
		Rand::setUniformInt(0, sizePesos-1);
		Rand::setNormalFloat(0, radio);
		
	
		c1nn.entrena(dataEntr, dataPrueba);
		
		mejorSol = pesos;
		c1nn.setPesos(mejorSol);
		mejorTasa = c1nn.validaEntr();
		
		pos.clear();
		for(k = 0; k < sizePesos; ++k)
		{
			pos.push_back(k);
		}
	
		
		for(i = 0, j = 0; i < maxVecinos && j < maxEval; ++i, ++j)
		{
			if(pos.empty())
			{
				aux = Rand::uniformRndDistI();
				for(k = 0; k < sizePesos; ++k)
				{
					pos.push_back(aux%sizePesos);
					++aux;
				}
			}
			
			Utils::mov(pesos, pos.back());
			pos.pop_back();
		
			c1nn.setPesos(pesos);
			tasa = c1nn.validaEntr();
			
			if(tasa > mejorTasa)
			{
			
				mejorTasa = tasa;
				mejorSol = pesos;
				i = 0;
			}
			else
			{
				pesos = mejorSol;
			}
		}
		
		return mejorSol;
	}
	
	void optimiza(Clasificador* cla, Alg::Cromosoma& cromo, const unsigned int maxEval,
						const double radio, unsigned int &numVals){
		
		sizePesos = cromo.size();
		auxpesos = cromo.getGenes();
		mejorSol = auxpesos;
		
		if(cromo.necesitaValorar()){
			cromo.valora();
			++numVals;
		}
		mejorTasa = cromo.getValoracion();
		
		Rand::setUniformInt(0, sizePesos-1);
		Rand::setNormalFloat(0, radio);
		
		pos.clear();
		for(k = 0; k < sizePesos; ++k)
		{
			pos.push_back(k);
		}
	
		
		for(i = 0; i < maxEval && numVals < 15000; ++i)
		{
			if(pos.empty())
			{
				aux = Rand::uniformRndDistI();
				for(k = 0; k < sizePesos; ++k)
				{
					pos.push_back(aux%sizePesos);
					++aux;
				}
			}
			
			Utils::mov(auxpesos, pos.back());
			pos.pop_back();
		
			cla->setPesos(auxpesos);
			tasa = cla->validaSol();
			++numVals;
			
			if(tasa > mejorTasa)
			{
			
				mejorTasa = tasa;
				mejorSol = auxpesos;
			}
			else
			{
				auxpesos = mejorSol;
			}
		}
		
		cromo.nuevo(mejorSol, cla, mejorTasa);
	}
}

