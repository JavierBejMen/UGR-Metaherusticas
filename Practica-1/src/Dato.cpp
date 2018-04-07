#include "Dato.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

void Dato::copia(const Dato& otro)
{
	if(&otro != this)
	{
		this->attributes = otro.attributes;
		this->nAttr = otro.nAttr;
		this->clase = otro.clase;
	}
}

Dato::Dato()
{
	this->nAttr = 0;
}

Dato::Dato(const Dato& otro)
{
	this->copia(otro);
}

Dato::Dato(const vector<double>& attr,const unsigned int cls)
{
	if(attr.empty())
		throw runtime_error("Error: no se puede construir Dato a partir de un vector vacio");
	
	this->attributes = attr;
	this->nAttr = attr.size();
	this->clase = cls;
}


bool Dato::empty() const
{
	return (this->nAttr == 0);
}

Dato& Dato::operator =(const Dato& otro)
{
	this->copia(otro);
	return *this;
}

int Dato::getClass() const
{
	if(empty())
		throw runtime_error("Quering class of a non initialized data");
		
	return this->clase;
}

unsigned int Dato::size() const
{
	return this->nAttr;
}

ostream & operator << (ostream &os, const Dato &dato)
{
	
	for(unsigned int i = 0; i < dato.size(); ++i)
	{
		os<<"["<<dato.attributes[i]<<"]";
	}
	os<<" Clase["<<dato.getClass()<<"]\n";
	
	return os;
}
		
const double& Dato::operator[](const unsigned int pos) const
{
	if(pos < 0 || pos >= this->size())
		throw runtime_error("Consulta de atibuto fuera de rango");
	
	return this->attributes[pos];
}

/*double& Dato::operator[](const unsigned int pos)
{
	if(pos < 0 || pos >= this->size())
		throw runtime_error("Consulta de atibuto fuera de rango");
	
	return this->attributes[pos];
}*/
	
double Dato::distEuclid(const Dato& otro) const
{
	if(this->empty() || otro.empty())
		throw runtime_error("Error: no se puede calcular distancia si uno de los datos esta vacio");
		
	double dist = 0, retDist = 0;
	for(unsigned int i = 0; i < this->size(); ++i)
	{
		dist=(this->attributes[i]-otro.attributes[i]);
		dist*=dist;
		retDist+=dist;
	}
	
	retDist = sqrt(retDist);

	return retDist;
}
										
double Dato::distEuclid(const Dato& otro, const vector<double>& pesos) const
{
	if(this->empty() || otro.empty())
		throw runtime_error("Error: no se puede calcular distancia si uno de los datos esta vacio");
	
	double dist = 0, retDist = 0;
	for(unsigned int i = 0; i < this->size(); ++i)
	{
		dist=(this->attributes[i]-otro.attributes[i]);
		dist*=dist*pesos[i];
		retDist+=dist;
	}
		
	retDist = sqrt(retDist);
	
	return retDist;
}

void Dato::clear()
{
	this->attributes.clear();
	this->nAttr = 0;
}
