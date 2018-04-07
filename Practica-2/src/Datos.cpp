#include "Datos.hpp"

#include <iostream>
#include <vector>
#include <string>



using namespace std;


//Class MetaData
void Datos::MetaData::copia(const Datos::MetaData& otro)
{
	if(&otro != this)
	{
		this->relation = otro.relation;
		this->path = otro.path;
		this->nAttr = otro.nAttr;
		this->nData = otro.nData;
	}
}

bool Datos::MetaData::empty() const
{
	return (this->relation.empty() || this->path.empty() || this->nAttr == 0
		|| this->nData == 0);
}

Datos::MetaData::MetaData()
{
	this->nAttr = 0;
	this->nData = 0;
}

Datos::MetaData::MetaData(const Datos::MetaData& otro)
{
	this->copia(otro);
}

Datos::MetaData::MetaData(const string& relation, const string& path, const unsigned int nAttr, const unsigned int nData)
{
	this->relation = relation;
	this->path = path;
	this->nAttr = nAttr;
	this->nData = nData;
}

Datos::MetaData& Datos::MetaData::operator=(const Datos::MetaData& otro)
{
	this->copia(otro);
	
	return *this;
}

ostream& operator<<(ostream& os, const Datos::MetaData &metaData)
{
	os<<"Path("<<metaData.getPath()<<"), Relation("<<metaData.getRelation()
	<<"), nAttr("<<metaData.sizeAttr()<<"), nData("<<metaData.sizeData()<<")\n";
	
	return os;
}

string Datos::MetaData::getRelation() const
{
	return this->relation;
}


string Datos::MetaData::getPath() const
{
	return this->path;
}

unsigned int Datos::MetaData::sizeAttr() const
{
	return this->nAttr;
}

unsigned int Datos::MetaData::sizeData() const
{
	return this->nData;
}

void Datos::MetaData::clear()
{
	this->relation.clear();
	this->path.clear();
	this->nAttr = 0;
	this->nData = 0;
}



//Class Datos
void Datos::copia(const Datos& otro)
{	
	if(&otro != this)
	{
		this->data = otro.data;
		this->metaData = otro.metaData;
	}
}

Datos::Datos(){}

Datos::Datos(const Datos& otro)
{
	this->copia(otro);
}

Datos::Datos(const vector<Dato>& data, const Datos::MetaData& metaData)
{
	if(data.size() !=  metaData.sizeData() || data.empty() || data[0].size() != metaData.sizeAttr())
		throw runtime_error("El formato de data o metaData es incorrecto, o data esta vacio");
		
	this->data = data;
	this->metaData = metaData;
}

Datos& Datos::operator=(const Datos& otro)
{
	this->copia(otro);
	
	return *this;
}

Datos Datos::operator +(const Datos& otro){
	if(this->sizeAttr() != otro.sizeAttr() || this->getRelation() != otro.getRelation()){
		throw runtime_error("No se puede sumar datos de relaciones diferentes");
	}
	
	vector<Dato> datos(this->data);
	for(unsigned int i = 0; i < otro.size(); ++i){
		datos.push_back(otro.data[i]);
	}
	MetaData meta(this->getRelation(), "5f", this->sizeAttr(), datos.size());
	
	return Datos(datos, meta);
}

void Datos::operator +=(const Datos& otro){
	if(this->empty())
		*this=otro;
	else
		*this = *this + otro;
}

const Dato& Datos::operator[](const unsigned int pos) const
{
	if(pos < 0 || pos > this->size())
		throw runtime_error("Consulta de dato fuera de rango");
		
	return data[pos];
}

ostream & operator << (ostream & os, const Datos &datos)
{
	os<<datos.getMetaData();
	for(unsigned int i = 0; i < datos.size(); ++i)
		os<<datos[i];
		
	return os;
}

bool Datos::empty() const
{
	return (this->data.empty());
}

unsigned int Datos::size() const
{
	return this->metaData.sizeData();
}
	
unsigned int Datos::sizeAttr() const
{
	return this->metaData.sizeAttr();
}

string Datos::getRelation() const
{
	return this->metaData.getRelation();
}

string Datos::getPath() const
{
	return this->metaData.getPath();
}

const Datos::MetaData& Datos::getMetaData() const
{
	return this->metaData;
}

void Datos::clear()
{
	this->data.clear();
	this->metaData.clear();
}



	
		
		
		
		
		
		
		
		
		
