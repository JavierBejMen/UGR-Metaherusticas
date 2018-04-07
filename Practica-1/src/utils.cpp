#include "utils.hpp"


#include <cmath>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>


using namespace std;

namespace Utils{
	double distPunto(const double x, const double y)
	{
		return abs(x-y);
	}

	void normaliza(vector<double>& vec)
	{
		double maxW = MIN_DOUBLE;
		for(unsigned int i = 0; i < vec.size(); ++i)
		{
			if(vec[i] > maxW)
				maxW = vec[i];
		}
	
		for(unsigned int i = 0; i < vec.size(); ++i)
		{
			vec[i] = (vec[i] < 0 ? 0 : vec[i]/maxW);
		}
	}

	void mov(vector<double>& pesos,const unsigned int pos)
	{
		pesos[pos] += Rand::normalRndDistF();
		
		if(pesos[pos]<0) pesos[pos] = 0;
		if(pesos[pos]>1) pesos[pos] = 1;
	}
}

namespace Timer{
	namespace{
		ChronoTimer t1;
		ChronoTimer t2;
		UnitTimer elapsed;
	}

	void startChrono()
	{
		t1 = Clock::now();
	}

	double elapsedTime()
	{
		t2 = Clock::now();
		elapsed = chrono::duration_cast<UnitTimer>(t2-t1);
		return elapsed.count();
	}
}	
	
namespace Rand{
	namespace{
		mt19937 generator;
		normal_distribution<double> norm_distribution;
		uniform_real_distribution<double> unif_float_dist;
		uniform_int_distribution<> unif_int_dist;
	}
	
	void initRndEngGen(unsigned int seed)
	{
		generator = mt19937(seed);
		unif_float_dist = uniform_real_distribution<double>(0.0, 1.0);
		norm_distribution = normal_distribution<double>(0.0, 1.0);
		unif_int_dist = uniform_int_distribution<>(0, 1);
	}

	double uniformRndDistF()
	{
		return unif_float_dist(generator);
	}
	void setUniformFloat(double low, double high)
	{
		unif_float_dist = uniform_real_distribution<double>(low, high);
	}


	double normalRndDistF()
	{
		return norm_distribution(generator);
	}
	void setNormalFloat(double low, double high)
	{
		norm_distribution = normal_distribution<double>(low, high);
	}


	unsigned int uniformRndDistI()
	{
		return unif_int_dist(generator);
	}
	void setUniformInt(unsigned int low, unsigned int high)
	{
		unif_int_dist = uniform_int_distribution<>(low, high);
	}
}

namespace FileWrapper{
	namespace{
		//files
		ifstream ifile;
		ofstream ofile;
		
		string path;
		Datos retDato;
		
		//Apertura de files
		void openiFile();
		void openoFile();
		
		//Cierre de files
		void closeiFile();
		void closeoFile();
	}

	const Datos& loadData(const string& pathFile)
	{
		string relation;
		unsigned int nAttr;
		unsigned int nData;
		
		path.clear();
		retDato.clear();
		
		path = pathFile;
		openiFile();
		
		//Leemos y construimos metaData
		ifile>>relation;
		ifile>>nAttr;
		ifile>>nData;
		--nAttr; //No contamos la clase como atributo
		if(nAttr == 0 || nData == 0)
		{
			closeiFile();
			cerr << "Error: FileWrapper reading file <"<<path<<">"<<endl;
			throw runtime_error("Numero de datos o de atributos vacio");
		}
		if(relation.empty())
		{
			closeiFile();
			cerr << "Error: FileWrapper reading file <"<<path<<">"<<endl;
			throw runtime_error("Relation atributo vacio");
		}
			
		Datos::MetaData metaData(relation, path, nAttr, nData);
		
		//Leemos y construimos data
		double value;
		vector<double> attrib;
		vector<Dato> data;
		
		for(unsigned int i = 0; i < nData && !ifile.eof(); ++i)
		{
			attrib.clear();
			for(unsigned int j = 0; j < nAttr && !ifile.eof(); ++j)
			{
				ifile>>value;
				attrib.push_back(value);
			}
			ifile>>value;
			Dato dato(attrib, value);
			data.push_back(dato);
		}
		
		closeiFile();
		
		if(data.size() != nData || data.empty() || data[0].size() != nAttr)
		{
			cerr << "Error: FileWrapper reading file <"<<path<<">"<<endl;
			throw runtime_error("Lectura falllida, data.size() != sizeData || data.empty() || data[0].size() != sizeAttr");
		}
		
		retDato = Datos(data, metaData);
	
		return retDato;
	}

	string set5c2path(string name, const unsigned int i, const unsigned int j)
	{
		name = "data/" + name + "/" + name + to_string(i) + "_" + to_string(j) + ".data";
	
		return name;
	}

	string getPathDataOpuesto(string pathFile)
	{
		bool good = false;
		for(unsigned int i = 0; i < pathFile.size() && !good; ++i)
		{
			if(pathFile[i] == '_')
			{
				pathFile[i+1] = (pathFile[i+1] == '0' ? '1' : '0');
				good = true;
			}
		}
		if(!good)
			throw runtime_error("Fallos al cargar path opuesto");
		
		return pathFile;
	}

	void guardaResultados(const vector<Utils::resultado>& resultados,const string& relation,const string& algorithim)
	{
		path = "data/resultados/" + algorithim + "/" + relation + ".result";
		openoFile();
		Utils::resultado mediaResult;
		ofile<<"%Aci"<<" "<<"t\n";
		for(unsigned int i = 0; i < 10; ++i)
		{
			ofile<<resultados[i].second<<" "<<resultados[i].first<<"\n";
			mediaResult.suma(resultados[i]);
		}
	
		ofile<<"media ";
		mediaResult.media(10);
		ofile<<mediaResult.second<<" "<<mediaResult.first<<"\n";
	
		closeoFile();
	}

	namespace{
		void openiFile()
		{
			ifile.open(path);
			if(!ifile)
			{
				cerr<<"Error: file: "<<path<<"\n";
				throw runtime_error("Unable to open file");
			}
		}

		void openoFile()
		{
			ofile.open(path, fstream::out | fstream::trunc);
			if(!ofile)
			{
				cerr<<"Error: file: "<<path;
				throw runtime_error("Unable to create file");
			}
		}

		void closeiFile()
		{
			ifile.close();
		}

		void closeoFile()
		{
			ofile.close();
		}
	}
}
