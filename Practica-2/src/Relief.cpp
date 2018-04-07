#include "Relief.hpp"

#include "Datos.hpp"
#include "Dato.hpp"
#include "utils.hpp"
#include "Clasificador.hpp"

#include <vector>
#include <stdexcept>
#include <cmath>


using namespace std;

vector<double> Relief::computaPesos(const Datos& datos)
{	
	unsigned int sizeAttr = datos.sizeAttr();
	unsigned int sizeDat = datos.size();
	vector<double> pesos;
	
	pesos.resize(sizeAttr, 0);
	
	
	double minDistAmigo, minDistEnemigo, dist;
	unsigned int amigo, enemigo;
	
	
	for(unsigned int i = 0; i < sizeDat; ++i)
	{
		minDistAmigo = Utils::MAX_DOUBLE;
		minDistEnemigo = Utils::MAX_DOUBLE;
		amigo = -1;
		enemigo = -1;
		for(unsigned int j = 0; j < sizeDat; ++j)
		{
			dist = datos[i].distEuclid(datos[j]);
			if(datos[i].getClass() != datos[j].getClass())
			{
				if(dist < minDistEnemigo)
				{
					minDistEnemigo = dist;
					enemigo = j;
				}
			}
			else if(i != j)
			{
				if(dist < minDistAmigo)
				{
					minDistAmigo = dist;
					amigo = j;
				}
			}
		}
		
		for(unsigned int j = 0; j < sizeAttr; ++j)
		{
			pesos[j] += Utils::distPunto(datos[i][j], datos[enemigo][j]) - Utils::distPunto(datos[i][j], datos[amigo][j]);
		}
	}
	
	Utils::normaliza(pesos);
	
	return pesos;
}
