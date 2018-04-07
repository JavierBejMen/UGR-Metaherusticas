#ifndef _DATOS_H_
#define _DATOS_H_

#include "Dato.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Datos
{
public:
	class MetaData;
	
	Datos();
	Datos(const Datos& otro);
	Datos(const vector<Dato>& data, const MetaData& metaData);
	
	Datos& operator=(const Datos& otro);
	const Dato& operator[](const unsigned int pos) const;
	friend ostream & operator << (ostream & os, const Datos &datos);
	
	bool empty() const;
	
	unsigned int size() const;
	unsigned int sizeAttr() const;
	string getRelation() const;
	string getPath() const;
	const MetaData& getMetaData() const;
	
	void clear();
	
	class MetaData
	{
	public:
		MetaData();
		MetaData(const MetaData& otro);
		MetaData(const string& relation, const string& path, const unsigned int nAttr, const unsigned int nData);
		
		MetaData& operator=(const MetaData& otro);
		friend ostream & operator << (ostream & os, const MetaData &metaData);
		
		bool empty() const;
		void clear();
		
		string getRelation() const;
		string getPath() const;
		unsigned int sizeAttr() const;
		unsigned int sizeData() const;
		
	private:
		string relation;
		string path;
		unsigned int nAttr;
		unsigned int nData;
		
		void copia(const MetaData& otro);
	};
	
private:
	vector<Dato> data;
	MetaData metaData;
	
	void copia(const Datos& otro);
};


#endif
