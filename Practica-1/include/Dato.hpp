//Clase que representa una instancia concreta

#ifndef _DATO_H_
#define _DATO_H_

#include <vector>
#include <iostream>

using namespace std;

class Dato
{
public:
	Dato();
	Dato(const Dato& otro);
	Dato(const vector<double>& attr, const unsigned int cls);

	Dato& operator=(const Dato &otro);
	
	bool empty() const;
	unsigned int size() const;
	
	int getClass() const;
	const double& operator[](const unsigned int pos) const;
	//double& operator[](const unsigned int pos);
	
	friend ostream & operator << (ostream & os, const Dato &dato);
	
	double distEuclid(const Dato& otro) const;											
	double distEuclid(const Dato& otro, const vector<double>& pesos) const;
	
	void clear();
	
private:
	vector<double> attributes;
	unsigned int clase;
	unsigned int nAttr;
	
	void copia(const Dato& otro);
};

#endif
