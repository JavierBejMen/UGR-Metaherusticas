//Algoritmos geneticos, generacional / estacionario blx-a / ca

#ifndef _ALGEVO_H_
#define _ALGEVO_H_

#include "Datos.hpp"
#include "Clasificador.hpp"

#include <vector>
#include <iostream>

using namespace std;

namespace Alg{
	class Cromosoma;
	class AG;
	class Generacional;
	class GBLX;
	class GCA;
	class Estacionario;
	class EBLX;
	class ECA;
	class AM;
	class AMmej;

	vector<double> computaPesosAGG_BLX_A(const Datos& data);
	vector<double> computaPesosAGG_CA(const Datos& data);
	
	vector<double> computaPesosAGE_BLX_A(const Datos& data);
	vector<double> computaPesosAGE_CA(const Datos& data);
	
	vector<double> computaPesosAM_10_1(const Datos& data);
	vector<double> computaPesosAM_10_01(const Datos& data);
	vector<double> computaPesosAM_mej(const Datos& data);
	
	//Representa un individuo o cromosoma, el vector de pesos W
	class Cromosoma{
	public:
		
		Cromosoma();
		Cromosoma(unsigned int tam, Clasificador* cla);
		Cromosoma(const vector<double>& genVec, Clasificador* cla);
		void nuevo(const vector<double>& genVec, Clasificador* cla);
		void nuevo(const vector<double>& genVec, Clasificador* cla, double valor);
		Cromosoma(const Cromosoma& otro);
		Cromosoma& operator=(const Cromosoma& otro);
		
		
		
		const double& operator[](const unsigned int pos) const;
		
		unsigned int size() const;
		bool empty() const;
		double getValoracion() const;
		
		bool operator==(const Cromosoma& otro) const;
		bool operator!=(const Cromosoma& otro) const;
		bool operator<(const Cromosoma& otro) const;
		bool operator>(const Cromosoma& otro) const;
		bool operator<=(const Cromosoma& otro) const;
		bool operator>=(const Cromosoma& otro) const;
		
		bool operator==(const double& otro) const;
		bool operator!=(const double& otro) const;
		bool operator<(const double& otro) const;
		bool operator>(const double& otro) const;
		bool operator<=(const double& otro) const;
		bool operator>=(const double& otro) const;
		
		friend ostream & operator << (ostream & os, const Cromosoma &cromo);
		
		void muta(unsigned int pos);
		void valora();
		
		bool necesitaValorar() const;
		unsigned int getId() const;
		
		static void initCount();
		
		const vector<double>& getGenes() const;
		
	private:
		static unsigned int count;
		unsigned int id; //Para saber si el mejor sobrevive
		vector<double> genes;
		unsigned int nGenes;
		double valoracion;
		Clasificador *clasificador;
		bool valoraFlag;
		
		
		void copia(const Cromosoma& otro);
	};
	
	class AG{
	public:
		AG();
		
		virtual void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, 
						double pCruce, unsigned int torneos, Clasificador* cla);
		
		void desarrolla();
		
		const vector<double>& solucion() const;
		unsigned int getNumVals() const;
		
	protected:	
		Clasificador* clasificador;
		vector<Cromosoma> cromosomas0;
		vector<Cromosoma>* popActual;
		vector<Cromosoma>* popSiguiente;
		unsigned int nGenes;
		unsigned int nCromosomas;
		unsigned int nCruces;
		unsigned int nParejas;
		unsigned int numVals;

		vector<Cromosoma> cromosomas1;


		virtual void reproduce() = 0;
	
		virtual void cruza() = 0;

		void muta();
		//Inicializadas en esquema (generacional o estacionario)
		unsigned int nMutaciones;
		unsigned int rangeMutacion;
		unsigned int seleccionado;
		unsigned int genMutado;


		virtual void integra() = 0;
		
		unsigned int posMejorCromo;
		unsigned int mejorCromosoma; //ID
	};
	
	class Generacional: public AG{
	public:
		Generacional();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
		
	protected:
		const Cromosoma* padre;
		const Cromosoma* madre;
		Cromosoma hijos;
		virtual void cruza() = 0;
		
		pair<unsigned int, unsigned int> rivales, padres;
		unsigned int n;
		void reproduce();
		
		vector<Cromosoma>* aux;
		double min , max;
		unsigned int peor, mejor;
		bool mejorEncontrado;
		virtual void integra();
	};
	
	class GBLX: public Generacional{
	public:
		GBLX();
		
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
		//void desarrolla();	
			
	private:
		vector<double> genes1, genes2;
		double minG, maxG, I, k1i, k2i;
	
		void cruza();
					
	};
	
	class GCA: public Generacional{
	public:
		GCA();
		
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
		
		
	private:
		vector<double> genes1;
		
		void cruza();
	}; 
		
	class Estacionario: public AG{
	public:
		Estacionario();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
				
	protected:
		const Cromosoma* padre;
		const Cromosoma* madre;
		Cromosoma hijos;
		virtual void cruza() = 0;
		
		pair<unsigned int, unsigned int> rivales, padres;
		unsigned int n;
		void reproduce();
		
		double min1, min2, max;
		unsigned int peor2, peor1;
		void integra();
	};
	
	class EBLX: public Estacionario{
	public:
		EBLX();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
	
	private:
		vector<double> genes1, genes2;
		double minG, maxG, I, k1i, k2i;
		
		void cruza();
		
	};
	
	class ECA: public Estacionario{
	public:
		ECA();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla);
	
	private:
		vector<double> genes1;
		
		void cruza();
		
	};
	
	class AM: public GBLX{
	public:
		AM();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla, double pOpt);
				
	private:
		unsigned int nValperOpt;
		unsigned int nGeneracion;
		unsigned int nOpt;
		void integra();
		
	};
	
	class AMmej: public GBLX{
	public:
		AMmej();
		void inicializa(unsigned int tamPoblacion, unsigned int tamGenes, double pCruce, 
				double pMuta, unsigned int torneos, Clasificador* cla, double pOpt);
		
	private:
		
		unsigned int nValperOpt;
		unsigned int nGeneracion;
		unsigned int nOpt;
		void integra();
	};
	
}

#endif
