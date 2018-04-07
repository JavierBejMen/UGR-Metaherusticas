#include "Algevo.hpp"

#include "Clasificador.hpp"
#include "utils.hpp"
#include "BL.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

namespace Alg{
	/****************************************************************************/
	/* Class Cromosoma */
	/****************************************************************************/
	unsigned int Cromosoma::count = 0;
	
	void Cromosoma::copia(const Cromosoma& otro){
		if(&otro != this){
			this->genes = otro.genes;
			this->nGenes = otro.nGenes;
			this->valoracion = otro.valoracion;
			this->clasificador = otro.clasificador;
			this->valoraFlag = otro.valoraFlag;
			this->id = otro.id;
		}
	}
	
	void Cromosoma::nuevo(const vector<double>& genVec, Clasificador* cla){
		this->genes = genVec;
		this->nGenes = genVec.size();
		this->valoracion = 0;
		this->clasificador = cla;
		this->valoraFlag = true;
		this->id = this->count;
		this->count++;
	}
	
	void Cromosoma::nuevo(const vector<double>& genVec, Clasificador* cla, double valor){
		this->genes = genVec;
		this->nGenes = genVec.size();
		this->valoracion = valor;
		this->clasificador = cla;
		this->valoraFlag = false;
		this->id = this->count;
		this->count++;
	}
	
	Cromosoma::Cromosoma(){
		this->nGenes = 0;
		this->valoracion = 0;
		this->clasificador = nullptr;
		this->valoraFlag = true;
		this->id = this->count;
		this->count++;
	}
	
	Cromosoma::Cromosoma(const vector<double>& genVec, Clasificador* cla){
		this->genes = genVec;
		this->nGenes = genVec.size();
		this->valoracion = 0;
		this->clasificador = cla;
		this->valoraFlag = true;
		this->id = this->count;
		this->count++;
	}
	
	Cromosoma::Cromosoma(unsigned int tam, Clasificador* cla)
	{	
		this->clasificador = cla;	
		for(unsigned int i = 0; i < tam; ++i)
		{
			genes.push_back(Rand::uniformRndDistF());
		}
		this->nGenes = tam;
		this->valoracion = 0;
		this->valoraFlag = true;
		this->id = this->count;
		this->count++;
	}
		
	Cromosoma::Cromosoma(const Cromosoma& otro){
		this->copia(otro);
	}
	
	Cromosoma& Cromosoma::operator=(const Cromosoma&otro){
		this->copia(otro);
		return *this;
	}
	
	const double& Cromosoma::operator[](const unsigned int pos) const{
		if(pos < 0 || pos >= this->nGenes)
			throw runtime_error("Error: intentando accede a un Gen fuera de rango");
		
		return this->genes[pos];
	}
	
	unsigned int Cromosoma::size() const{
		return this->nGenes;
	}
	
	bool Cromosoma::empty() const{
		return this->nGenes == 0;
	}
	
	double Cromosoma::getValoracion() const{
		return this->valoracion;
	}
	
	void Cromosoma::muta(unsigned int pos){
		if(pos < 0 || pos >= this->nGenes)
			throw runtime_error("Error: intentando mutar un Gen fuera de rango");
		
		this->genes[pos] += Rand::normalRndDistF();
		if(this->genes[pos]<0)this->genes[pos]=0;
		if(this->genes[pos]>1)this->genes[pos]=1;
		
		this->valoraFlag = true;
		this->id = this->count;
		this->count++;
	}
	
	//Operadores de comparacion
	bool Cromosoma::operator==(const Cromosoma& otro) const{
		return this->valoracion==otro.valoracion;
	}
	bool Cromosoma::operator!=(const Cromosoma& otro) const{
		return this->valoracion!=otro.valoracion;
	}
	bool Cromosoma::operator<(const Cromosoma& otro) const{
		return this->valoracion<otro.valoracion;
	}
	bool Cromosoma::operator>(const Cromosoma& otro) const{
		return this->valoracion>otro.valoracion;
	}
	bool Cromosoma::operator<=(const Cromosoma& otro) const{
		return this->valoracion<=otro.valoracion;
	}
	bool Cromosoma::operator>=(const Cromosoma& otro) const{
		return this->valoracion>=otro.valoracion;
	}
	bool Cromosoma::operator==(const double& otro) const{
		return this->valoracion == otro;
	}
	bool Cromosoma::operator!=(const double& otro) const{
		return this->valoracion != otro;
	}
	bool Cromosoma::operator<(const double& otro) const{
		return this->valoracion < otro;
	}
	bool Cromosoma::operator>(const double& otro) const{
		return this->valoracion > otro;
	}
	bool Cromosoma::operator<=(const double& otro) const{
		return this->valoracion <= otro;
	}
	bool Cromosoma::operator>=(const double& otro) const{
		return this->valoracion >= otro;
	}
	
	void Cromosoma::valora(){
		if(this->clasificador == nullptr)
			throw runtime_error("No se puede valorar cromosoma sin inicializar el clasificador");
		
	
			this->clasificador->setPesos(genes);
			this->valoracion = this->clasificador->validaEntr();
		
			this->valoraFlag = false;
		
	}
	
	ostream & operator << (ostream & os, const Cromosoma &cromo){
		for(unsigned int i = 0; i < cromo.nGenes; ++i){
			os<<"["<<cromo.genes[i]<<"] ";
		}
		os<<"Valoracion("<<cromo.valoracion<<")\n";
		
		return os;
	}
	
	bool Cromosoma::necesitaValorar() const{
		return this->valoraFlag;
	}
	
	unsigned int Cromosoma::getId() const{
		return this->id;
	}
	
	void Cromosoma::initCount(){
		count = 0;
	}
	
	const vector<double>& Cromosoma::getGenes() const{
		return this->genes;
	}
	/****************************************************************************/
	
	
	/****************************************************************************/
	/* Class AG */
	/****************************************************************************/
	AG::AG(){}
	
	void AG::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, 
			double pCruce, unsigned int torneos, Clasificador *cla){
		if(cla == nullptr)
			throw runtime_error("Error: inicializando Evolutivo con clasificador nulo");
		
		this->clasificador = cla;
		this->nCromosomas = tamPoblacion;
		this->nGenes = tamGenes;
		this->nParejas = ceil(torneos/2);
		this->nCruces = ceil(pCruce*nParejas);
		//cout<<"nGenes: "<<nGenes<<"\nnMUt: "<<nMutaciones<<"\nParejas: "<<nParejas<<"\nnCruces: "<<nCruces<<endl;
	
		//Generar poblacion inicial
		double max = Utils::MIN_DOUBLE;
		Cromosoma::initCount();
		Rand::setUniformFloat(0, 1);
		for(unsigned int i = 0; i < this->nCromosomas; ++i){
			cromosomas0.push_back(Cromosoma(this->nGenes, this->clasificador));
			cromosomas0.back().valora();
			++numVals;
	
			if(cromosomas0.back() > max){
				max = cromosomas0.back().getValoracion();
				this->mejorCromosoma = cromosomas0.back().getId();
				this->posMejorCromo = i;
			}
		}
		
	
		
		
		this->popActual = &this->cromosomas0;
		this->popSiguiente = &this->cromosomas1;
		numVals = 0;
	}
	
	void AG::desarrolla()
	{
		while(numVals < 15000){
			
			reproduce();
			
			
			muta();
			
			
			integra();
		}
	}
	
	void AG::muta(){
		genMutado = Utils::MAX_INT;
		
		Rand::setUniformInt(0, rangeMutacion);//this->nCromosomas*(this->nGenes-1));
		Rand::setNormalFloat(0, 0.3);
		for(unsigned int i = 0; i < nMutaciones; ++i){
			do{
				seleccionado = Rand::uniformRndDistI();
			}while(genMutado == seleccionado%nGenes);
			genMutado = seleccionado%nGenes;
			popSiguiente->at(seleccionado/nGenes).muta(genMutado);
		}
	}
	
	const vector<double>& AG::solucion() const{
		return this->popActual->at(this->posMejorCromo).getGenes();
	}
	
	unsigned int AG::getNumVals() const{
		return this->numVals;
	}
	/****************************************************************************/
	
	
	/****************************************************************************/
	/* Class Generacional */
	/****************************************************************************/
	Generacional::Generacional():AG(){}
	
	void Generacional::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
		AG::inicializa(tamPoblacion, tamGenes, pCruce, torneos, cla);
		
		this->nMutaciones = ceil(tamPoblacion * tamGenes * pMuta);

		//this->cromosomas1.resize(tamPoblacion);
		this->rangeMutacion = (tamPoblacion*tamGenes) - 1;
	}
	
	void Generacional::reproduce(){
		//Seleccion y Cruce
		Rand::setUniformInt(1, nCromosomas*nCromosomas - 2);
		for(unsigned int i = 0; i < nParejas; ++i){
			
			//Seleccion de padres
			do{
				n = Rand::uniformRndDistI();
			}while(n%(nCromosomas+1)==0);
			rivales.first = n/nCromosomas;
			rivales.second = n%nCromosomas;
			if(popActual->at(rivales.first) > popActual->at(rivales.second)){
				padres.first = rivales.first;
			}else{
				padres.first = rivales.second;
			}
			do{
				n = Rand::uniformRndDistI();
			}while(n%(nCromosomas+1) == 0 && (n%nCromosomas == padres.first || n/nCromosomas == padres.first));
			rivales.first = n/nCromosomas;
			rivales.second = n%nCromosomas;
			if(popActual->at(rivales.first) > popActual->at(rivales.second)){
				padres.second = rivales.first;
			}else{
				padres.second = rivales.second;
			}
		
		
			//Cruce
			//Si no se ha alcanzado el numero de cruces establecido se cruza, si no ambos padres pasan a formar parte de la nueva poblacion
			if(i < nCruces){
				padre = &popActual->at(padres.first);
				madre = &popActual->at(padres.second);
				cruza();
				//this->cruzaBLX(this->popActual[padres.first], this->popActual[padres.second], genesHijo, hijo);
			}else{
				popSiguiente->push_back(popActual->at(padres.first));
				popSiguiente->push_back(popActual->at(padres.second));
			}			
		}
	}
	
	
	void Generacional::integra(){	
		//Sustitucion
		//recorremos el popSiguiente para valorar y sustituir el peor si no ha sobrevivido
		min = Utils::MAX_DOUBLE; max = Utils::MIN_DOUBLE;//double min = Utils::MAX_DOUBLE, max = Utils::MIN_DOUBLE;
		peor = 0; mejor = 0;//unsigned int peor = 0, mejor = 0;
		mejorEncontrado = false;//bool mejorEncontrado = false;
		//double media = 0;
		//int numval = 0;
			
		for(unsigned int i = 0; i < nCromosomas && numVals<15000; ++i){
		
			if(popSiguiente->at(i).necesitaValorar()){
				popSiguiente->at(i).valora();
				//numval++;
				//media+=popSiguiente->at(i).getValoracion();
				++numVals;
			}
			
			if(!mejorEncontrado && popSiguiente->at(i).getId() == mejorCromosoma){
				mejorEncontrado = true;
			}
			if(!mejorEncontrado && popSiguiente->at(i) < min){
				min = popSiguiente->at(i).getValoracion();
				peor = i;
			}
			if(popSiguiente->at(i) > max){
				max = popSiguiente->at(i).getValoracion();
				mejor = i;
			}
		}
		
		
		
		if(!mejorEncontrado){
			popSiguiente->at(peor) = popActual->at(posMejorCromo);
			if(popSiguiente->at(mejor) > popActual->at(posMejorCromo)){
				posMejorCromo = mejor;
				mejorCromosoma = popSiguiente->at(mejor).getId();
			}else{
				posMejorCromo = peor;
			}
		}
		else{
			posMejorCromo = mejor;
			mejorCromosoma = popSiguiente->at(mejor).getId();
		}
		
		//cout<<"media: "<<(numval != 0 ? media/numval : 0)<<"   nValoraciones: "<<numval<<"   Mejor: "<<popSiguiente->at(posMejorCromo).getValoracion()<<endl;
		//cout<<"numvals global: "<<numVals<<endl;
		
		//switch
		aux = popActual;
		popActual = popSiguiente;
		popSiguiente = aux;
		
		
			
		popSiguiente->clear();
	}
	/****************************************************************************/

	/****************************************************************************/	
	
	
	/****************************************************************************/
	/* Class GBLX */
	/****************************************************************************/
	GBLX::GBLX():Generacional(){}
	
	void GBLX::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
					
		Generacional::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		genes1.resize(tamGenes);
		genes2.resize(tamGenes);
	}
	
	void GBLX::cruza(){
		
		for(unsigned int i = 0; i < nGenes; ++i){
			if(padre->operator[](i) < madre->operator[](i)){
				minG = padre->operator[](i);
				maxG = madre->operator[](i);
			}else{
				minG = madre->operator[](i);
				maxG = padre->operator[](i);
			}
			I = (maxG - minG)*0.3;
			
			Rand::setUniformFloat(minG - I, maxG + I);
			k1i = Rand::uniformRndDistF();
			k2i = Rand::uniformRndDistF();
			if(k1i>1) k1i = 1;
			if(k1i<0) k1i = 0;
			genes1[i] = k1i;
			
			if(k2i>1) k2i = 1;
			if(k2i<0) k2i = 0;
			genes2[i] = k2i;
			//cout<<"["<<min - I<<", "<<max + I<<"] result: "<<genes.back()<<endl;
		}
		
		hijos.nuevo(genes1, this->clasificador);
		popSiguiente->push_back(hijos);
		hijos.nuevo(genes2, this->clasificador);
		popSiguiente->push_back(hijos);
	}
	/****************************************************************************/
	
	
	/****************************************************************************/
	/* Class GAC */
	/****************************************************************************/
	GCA::GCA():Generacional(){}
	
	void GCA::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
		Generacional::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		genes1.resize(tamGenes);
	}
	
	void GCA::cruza(){
		for(unsigned int i = 0; i < nGenes; ++i){
			genes1[i] = (padre->operator[](i) + madre->operator[](i))/2;
		}
		
		hijos.nuevo(genes1, this->clasificador);
		popSiguiente->push_back(hijos);
		hijos.nuevo(genes1, this->clasificador);
		popSiguiente->push_back(hijos);
	}
	/****************************************************************************/
	
	
	/****************************************************************************/
	/* Class Estacionario */
	/****************************************************************************/
	Estacionario::Estacionario():AG(){}
	
	void Estacionario::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
		AG::inicializa(tamPoblacion, tamGenes, pCruce, torneos, cla);
		
		this->nMutaciones = ceil(2 * tamGenes * pMuta);

		//this->cromosomas1.resize(tamPoblacion);
		this->rangeMutacion = (2*tamGenes) - 1;
		
		min1 = Utils::MAX_DOUBLE;
		min2 = Utils::MAX_DOUBLE;
		max = Utils::MIN_DOUBLE;
		for(unsigned int i = 0; i < nCromosomas; ++i){
			if(cromosomas0[i]<min1){
				if(min2 != Utils::MAX_DOUBLE){
					if(cromosomas0[peor1] < cromosomas0[peor2]){
						peor2 = peor1;
						min2 = min1;
					}
				}else{
					peor2 = peor1;
					min2 = min1;
				}
				peor1 = i;
				min1 = cromosomas0[i].getValoracion();	
			}else if(cromosomas0[i] < min2){
				peor2 = i;
				min2 = cromosomas0[i].getValoracion();
			}
			if(cromosomas0[i] > max){
				max = cromosomas0[i].getValoracion();
				posMejorCromo = i;
			}
		}
		
		cromosomas1.resize(2);
	}
	
	void Estacionario::reproduce(){
		//Seleccion y Cruce
		Rand::setUniformInt(1, nCromosomas*nCromosomas - 2);
			
		//Seleccion de padres
		do{
			n = Rand::uniformRndDistI();
		}while(n%(nCromosomas+1)==0);
		rivales.first = n/nCromosomas;
		rivales.second = n%nCromosomas;
		if(cromosomas0[rivales.first] > cromosomas0[rivales.second]){
			padres.first = rivales.first;
		}else{
			padres.first = rivales.second;
		}
		do{
			n = Rand::uniformRndDistI();
		}while(n%(nCromosomas+1) == 0);
		rivales.first = n/nCromosomas;
		rivales.second = n%nCromosomas;
		if(cromosomas0[rivales.first] > cromosomas0[rivales.second]){
			padres.second = rivales.first;
		}else{
			padres.second = rivales.second;
		}
		
		padre = &cromosomas0[padres.first];	
		madre = &cromosomas0[padres.second];
		cruza();
	}
	
	void Estacionario::integra(){
		
		cromosomas0[peor1] = cromosomas1[0];
		cromosomas0[peor2] = cromosomas1[1];
		
		
		min1 = Utils::MAX_DOUBLE;
		min2 = Utils::MAX_DOUBLE;
		max = Utils::MIN_DOUBLE;
		//double media = 0;
		//int numval = 0;
		
		for(unsigned int i = 0; i < nCromosomas && numVals<15000; ++i){
			if(cromosomas0[i].necesitaValorar()){
				cromosomas0[i].valora();
				++numVals;
				//++numval;
				//media+=cromosomas0[i].getValoracion();
			}
			if(cromosomas0[i]<min1){
				if(min2 != Utils::MAX_DOUBLE){
					if(cromosomas0[peor1] < cromosomas0[peor2]){
						peor2 = peor1;
						min2 = min1;
					}
				}else{
					peor2 = peor1;
					min2 = min1;
				}
				peor1 = i;
				min1 = cromosomas0[i].getValoracion();	
			}else if(cromosomas0[i] < min2){
				peor2 = i;
				min2 = cromosomas0[i].getValoracion();
			}
			if(cromosomas0[i] > max){
				max = cromosomas0[i].getValoracion();
				posMejorCromo = i;
			}
		}
		
		//cout<<"media: "<<(numval != 0 ? media/numval : 0)<<"   nValoraciones: "<<numval<<"   Mejor: "<<popActual->at(posMejorCromo).getValoracion()<<endl;
		//cout<<"numVals total: "<<numVals<<endl;
			
	}
	/****************************************************************************/


	/****************************************************************************/
	/* Class EBLX */
	/****************************************************************************/
	EBLX::EBLX():Estacionario(){}
	
	void EBLX::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
					
		Estacionario::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		genes1.resize(tamGenes);
		genes2.resize(tamGenes);
	}
	
	void EBLX::cruza(){
		
		for(unsigned int i = 0; i < nGenes; ++i){
			if(padre->operator[](i) < madre->operator[](i)){
				minG = padre->operator[](i);
				maxG = madre->operator[](i);
			}else{
				minG = madre->operator[](i);
				maxG = padre->operator[](i);
			}
			I = (maxG - minG)*0.3;
			
			Rand::setUniformFloat(minG - I, maxG + I);
			k1i = Rand::uniformRndDistF(); 
			k2i = Rand::uniformRndDistF();
			if(k1i>1) k1i = 1;
			if(k1i<0) k1i = 0;
			genes1[i] = k1i;
			
			if(k2i>1) k2i = 1;
			if(k2i<0) k2i = 0;
			genes2[i] = k2i;
			//cout<<"["<<min - I<<", "<<max + I<<"] result: "<<genes.back()<<endl;
		}
		
		hijos.nuevo(genes1, this->clasificador);
		cromosomas1[0] = hijos;
		hijos.nuevo(genes2, this->clasificador);
		cromosomas1[1] = hijos;
	}
	/****************************************************************************/


	/****************************************************************************/
	/* Class ECA */
	/****************************************************************************/
	ECA::ECA():Estacionario(){}
	
	void ECA::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla){
		Estacionario::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		genes1.resize(tamGenes);
	}
	
	void ECA::cruza(){
		for(unsigned int i = 0; i < nGenes; ++i){
			genes1[i] = (padre->operator[](i) + madre->operator[](i))/2;
		}
		
		hijos.nuevo(genes1, this->clasificador);
		cromosomas1[0] = (hijos);
		hijos.nuevo(genes1, this->clasificador);
		cromosomas1[1] = (hijos);
	}
	/****************************************************************************/

	
	
	/****************************************************************************/
	/* Class AM */
	/****************************************************************************/
	AM::AM():GBLX(){}
	
	void AM::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla, double pOpt){
		GBLX::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		nOpt = pOpt * nCromosomas;
		nValperOpt = 2*nGenes;
		nGeneracion = 0;
	}
	
	void AM::integra(){
		//Sustitucion
		//recorremos el popSiguiente para valorar y sustituir el peor si no ha sobrevivido
		min = Utils::MAX_DOUBLE; max = Utils::MIN_DOUBLE;//double min = Utils::MAX_DOUBLE, max = Utils::MIN_DOUBLE;
		peor = 0; mejor = 0;//unsigned int peor = 0, mejor = 0;
		mejorEncontrado = false;//bool mejorEncontrado = false;
		//double media = 0;
		//int numval = 0;
			
		for(unsigned int i = 0; i < nCromosomas && numVals<15000; ++i){
			
			if((nGeneracion % 10) == 0 && i < nOpt){
				BL::optimiza(clasificador, popSiguiente->at(i), nValperOpt, 0.3, numVals); //BL
			}
		
			
			if(popSiguiente->at(i).necesitaValorar()){
				popSiguiente->at(i).valora();
				//numval++;
				//media+=popSiguiente->at(i).getValoracion();
				++numVals;
			}
			
			if(!mejorEncontrado && popSiguiente->at(i).getId() == mejorCromosoma){
				mejorEncontrado = true;
			}
			if(!mejorEncontrado && popSiguiente->at(i) < min){
				min = popSiguiente->at(i).getValoracion();
				peor = i;
			}
			if(popSiguiente->at(i) > max){
				max = popSiguiente->at(i).getValoracion();
				mejor = i;
			}
		}
		
		
		
		if(!mejorEncontrado){
			popSiguiente->at(peor) = popActual->at(posMejorCromo);
			if(popSiguiente->at(mejor) > popActual->at(posMejorCromo)){
				posMejorCromo = mejor;
				mejorCromosoma = popSiguiente->at(mejor).getId();
			}else{
				posMejorCromo = peor;
			}
		}
		else{
			posMejorCromo = mejor;
			mejorCromosoma = popSiguiente->at(mejor).getId();
		}
		
		//cout<<"media: "<<(numval != 0 ? media/numval : 0)<<"   nValoraciones: "<<numval<<"   Mejor: "<<popSiguiente->at(posMejorCromo).getValoracion()<<endl;
		//cout<<"numvals global: "<<numVals<<endl;
		
		//switch
		aux = popActual;
		popActual = popSiguiente;
		popSiguiente = aux;
		
		
			
		popSiguiente->clear();
		
		nGeneracion++;
	}
	/****************************************************************************/



	/****************************************************************************/
	/* Class AMmej */
	/****************************************************************************/
	AMmej::AMmej():GBLX(){}
	
	void AMmej::inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla, double pOpt){
		GBLX::inicializa(tamPoblacion, tamGenes, pCruce, pMuta, torneos, cla);
		
		nOpt = pOpt * nCromosomas;
		nValperOpt = 2*nGenes;
		nGeneracion = 0;
	}
	
	void AMmej::integra(){
		
		//cout<<"Generacion: "<<nGeneracion<<endl;
		
		if((nGeneracion%10) == 0){
			//Sustitucion
			//recorremos el popSiguiente para valorar y sustituir el peor si no ha sobrevivido
			min = Utils::MAX_DOUBLE; max = Utils::MIN_DOUBLE;//double min = Utils::MAX_DOUBLE, max = Utils::MIN_DOUBLE;
			peor = 0; mejor = 0;//unsigned int peor = 0, mejor = 0;
			mejorEncontrado = false;//bool mejorEncontrado = false;
			//double media = 0;
			//int numval = 0;
			
			for(unsigned int i = 0; i <nCromosomas  && numVals<15000; ++i){	
				if(popSiguiente->at(i).necesitaValorar()){
					popSiguiente->at(i).valora();
					//numval++;
					//media+=popSiguiente->at(i).getValoracion();
					++numVals;
				}
			
				//cout<<"Valoracion "<<i<<": "<<popSiguiente->at(i).getValoracion()<<endl;
			
			}
		
			sort(popSiguiente->begin(), popSiguiente->end());
			for(unsigned int i = nCromosomas-1, j = 0; i >0  && numVals<15000; --i, ++j){
				
				if(j < nOpt){
					BL::optimiza(clasificador, popSiguiente->at(i), nValperOpt, 0.3, numVals); //BL
				}
			
				if(!mejorEncontrado && popSiguiente->at(i).getId() == mejorCromosoma){
					mejorEncontrado = true;
				}
			
				//cout<<"Valoracion Ordenada "<<i<<": "<<popSiguiente->at(i).getValoracion()<<endl;
			}
		
			if(!mejorEncontrado){
				popSiguiente->at(0) = popActual->at(posMejorCromo);
				if(popSiguiente->at(nCromosomas-1) > popActual->at(posMejorCromo)){
					posMejorCromo = nCromosomas-1;
					mejorCromosoma = popSiguiente->at(posMejorCromo).getId();
				}else{
					posMejorCromo = 0;
				}
			}
			else{
				posMejorCromo = nCromosomas-1;
				mejorCromosoma = popSiguiente->at(posMejorCromo).getId();
			}
		
			//cout<<"media: "<<(numval != 0 ? media/numval : 0)<<"   nValoraciones: "<<numval<<"   Mejor: "<<popSiguiente->at(posMejorCromo).getValoracion()<<endl;
			//cout<<"numvals global: "<<numVals<<endl;
		
			//switch
			aux = popActual;
			popActual = popSiguiente;
			popSiguiente = aux;
		
		
			
			popSiguiente->clear();
		}else{
			Generacional::integra();
		}
		
		
		nGeneracion++;
	}
	/****************************************************************************/
	
	
	/****************************************************************************/
	/* Funciones ComputaPesos */
	/****************************************************************************/
	vector<double> computaPesosAGG_BLX_A(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		GBLX alg;
		
		alg.inicializa(30, data.sizeAttr(),0.7,0.001,30,&cla);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAGG_CA(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		GCA alg;
		
		alg.inicializa(30, data.sizeAttr(),0.7,0.001,30,&cla);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAGE_BLX_A(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		EBLX alg;
		
		alg.inicializa(30, data.sizeAttr(),1,0.001,30,&cla);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAGE_CA(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		ECA alg;
		
		alg.inicializa(30, data.sizeAttr(),1,0.001,30,&cla);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAM_10_1(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		AM alg;
		
		alg.inicializa(30, data.sizeAttr(),0.7,0.001,30,&cla, 1);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAM_10_01(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		AM alg;
		
		alg.inicializa(30, data.sizeAttr(),0.7,0.001,30,&cla, 0.1);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
	
	vector<double> computaPesosAM_mej(const Datos& data){
		Clasificador cla;
		Datos dataPrueba;
		dataPrueba = FileWrapper::loadData(FileWrapper::getPathDataOpuesto(data.getPath()));
		
		cla.entrena(data, dataPrueba);
		
		AMmej alg;
		
		alg.inicializa(30, data.sizeAttr(),0.7,0.001,30,&cla, 0.1);
		
		alg.desarrolla();
	
		return alg.solucion();	
	}
		
	/****************************************************************************/	
		
}




















