//Formatea los datos

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>








using namespace std;

int main(int argc, char * argv[])
{
	
	if (argc != 2) 
	{
		cerr << "Sintaxis: " << argv[0] << " <nombre_fichero>" << endl;
		return(-1);
	}
	
	ifstream ifile;
	ifile.open(argv[1]);
	if(!ifile)
	{
		cerr<<"fichero: "<<argv[1]<<" no encontrado"<<endl;
		return -1;
	}
	
	ifile.ignore(numeric_limits<streamsize>::max(), '@');
	string in;
	ifile>>in;
	transform(in.begin(), in.end(), in.begin(), ::tolower);

	if(in != "relation" )
	{
		cerr<<"Formato de archivo incorrecto"<<endl;
		return -1;
	}
	
	ifile>>in;
	
	string relation;
	
	
	if(in == "sonar")
	{
		relation = "sonar";
	}
	else if(in == "'Wisconsin")
	{
		relation = "wdbc";
	}
	else if(in == "Spambase-460")
	{
		relation = "Spambase-460";
	}
	
		
	int nAttr = -1;
	while(in != "data" && !ifile.eof())
	{
		ifile.ignore(numeric_limits<streamsize>::max(), '@');
		ifile>>in;
		nAttr++;
	}
	
	ifile.ignore(numeric_limits<streamsize>::max(), '\n');
	
	vector<double> atributes;
	vector<vector <double> > datos;
	double value;
	int nDatos = 0;
	
	//-------------------------------------------SONAR
	if(relation == "sonar")
	{
		ifile>>value;
		while(!ifile.eof())
		{
			for(int i = 0; i < nAttr-2 && !ifile.eof(); ++i)
			{
				atributes.push_back(value);
				ifile.ignore(numeric_limits<streamsize>::max(), ',');
				ifile>>value;
			}
			atributes.push_back(value);
			ifile.ignore(numeric_limits<streamsize>::max(), ',');
			ifile>>in;
			if(in == "Mine")
				value = 1;
			else if(in == "Rock")
				value = 0;
				
			atributes.push_back(value);
			datos.push_back(atributes);
			
			++nDatos;
			atributes.clear();
			
			ifile.ignore(numeric_limits<streamsize>::max(), '\n');
			
			ifile>>value;
			
		}
		
		cout<<datos.size()<<endl;
	}
	
	
	//-------------------------------------------WDBC
	if(relation == "wdbc")
	{
		char aux;
		ifile>>aux;
		while(!ifile.eof())
		{		
			for(int i = 0; i < nAttr-1 && !ifile.eof(); ++i)
			{
				ifile.ignore(numeric_limits<streamsize>::max(), ',');
				ifile>>value;
				atributes.push_back(value);
			}
			
			
			
			if(aux == 'M')
				value = 0;
			else if(aux == 'B')
				value = 1;
				
			atributes.push_back(value);	
			
			datos.push_back(atributes);
			++nDatos;
			
			atributes.clear();
			
			ifile.ignore(numeric_limits<streamsize>::max(), '\n');
			ifile>>aux;
		
		}
		cout<<datos.size()<<endl;
	}
	
	//-------------------------------------------SpamBase
	if(relation == "Spambase-460")
	{
		ifile>>value;
		while(!ifile.eof())
		{
			atributes.clear();
			for(int i = 0; i < nAttr - 1 && !ifile.eof(); ++i)
			{
				atributes.push_back(value);
				ifile.ignore(numeric_limits<streamsize>::max(), ',');
				ifile>>value;
			}
			atributes.push_back(value);
			
			datos.push_back(atributes);
			++nDatos;
			
			ifile.ignore(numeric_limits<streamsize>::max(), '\n');
			ifile>>value;
		}
	}
	//---------------------------------------Calcula numero de etiquetas y normaliza
	int n_class_0 = 0;
	int n_class_1 = 0;
	for(int i = 0; i < nDatos; ++i)
	{
		if(datos[i][nAttr-1] == 0) ++n_class_0;	
		else if(datos[i][nAttr-1] == 1) ++n_class_1;

	} if(n_class_0 +n_class_1 != nDatos) cout<<"Algo falla "<<n_class_0<<"  "<<n_class_1<<endl;
	
	
	//Obtenemos el min y max para cada atributo
	vector<pair<double, double> > min_max;
	min_max.resize(nAttr);
	for(int i = 0; i < nAttr -1; ++i)//nDatos; ++i)
	{
		min_max[i].first = datos[0][i];
		min_max[i].second = datos[0][i];
		for(int j = 0; j < nDatos;++j)
		{
			
			if(datos[j][i] < min_max[i].first){
				min_max[i].first = datos[j][i];
			}
			else if(datos[j][i] > min_max[i].second){
				min_max[i].second = datos[j][i];
			}
		}
		
		
	}
	
	
	
	//Normalizamos
	for(int i = 0; i < nDatos; ++i)
	{
		for(int j = 0; j < nAttr - 1; ++j)
		{
			datos[i][j] = (datos[i][j] - min_max[j].first) / (min_max[j].second - min_max[j].first);
		}
	}
	
	
	
	//---------------------------------------Write
	ifile.close();
	ofstream ofile;	
	string path;
	
	path = "data/"+relation+"/"+relation+".data";
	ofile.open(path.c_str() , fstream::out | fstream::trunc);
			if(!ofile)
			{
				cerr<<"Error al crear archivo <"<<path<<">"<<endl;
				return -1;
			}
	
	ofile<<relation<<" "<<datos[0].size()<<" "<<datos.size()<<"\n";
	
	for(unsigned int i = 0; i<datos.size();++i)
	{
		for(unsigned int j = 0; j < datos[0].size(); ++j)
		{
			ofile<<datos[i][j]<<" ";
		}
		ofile<<"\n";
	}
	
	ofile.close();
	
	
	
	//----------------------------------Write 5x2c
	path.clear();
	std::srand ( unsigned ( std::time(0) ) );
	vector<vector<double> > aux, aux1;
	int in_n_class_0 = 0, in_n_class_1 = 0;
	int sizeAux = 0;
	string auxpath;
	for(int i = 0; i < 5; ++i)
	{	
		random_shuffle(datos.begin(), datos.end());
		random_shuffle(datos.begin(), datos.end());
		random_shuffle(datos.begin(), datos.end());
		aux.clear();
		aux1.clear();
		path ="data/"+ relation + "/" + relation + to_string(i) + "_";
		
		in_n_class_0 = 0;
		in_n_class_1 = 0;
		sizeAux = 0;
		for(int j = 0; j < nDatos ; ++j)
		{
			if(datos[j][nAttr-1] == 0 && in_n_class_0 < n_class_0/2)
			{
				aux.push_back(datos[j]);
				++in_n_class_0;
				++sizeAux;
			}
			else if(datos[j][nAttr-1] == 1 && in_n_class_1 < n_class_1/2)
			{
				aux.push_back(datos[j]);
				++in_n_class_1;
				++sizeAux;
			}
			else aux1.push_back(datos[j]);
		}
		
		
		cout<<"aux :"<<aux.size()<<"    "<<in_n_class_0<<"    "<<in_n_class_1<<"     "<<sizeAux<<endl;
		
		
		
		
		vector<double> pesos;
		
		for(int j = 0; j < 2; ++j)
		{
			auxpath=to_string(j) + ".data";
			
	
			ofile.open((path+auxpath).c_str() , fstream::out | fstream::trunc);
			if(!ofile)
			{
				cerr<<"Error al crear archivo <"<<path<<">"<<endl;
				return -1;
			}
	
			ofile<<relation<<" "<<aux[0].size()<<" "<<aux.size()<<"\n";
		
			for(unsigned int i = 0; i < aux.size(); ++i)
			{
				for(unsigned int j = 0; j < aux[0].size(); ++j)
				{
					ofile<<aux[i][j]<<" ";
				}
				ofile<<"\n";
			}
			
			/*
			ofile<<"@Pesos\n";
			pesos.resize(aux[0].size() - 1, 1);
			for(unsigned int i = 0; i < pesos.size(); ++i)
			{
				ofile<<pesos[i]<<" ";
			}
			ofile<<"\n";
			*/
			
			ofile.close();
			
			aux = aux1;
		}
		cout<<"aux :"<<aux.size()<<"    "<<in_n_class_0<<"    "<<in_n_class_1<<"     "<<sizeAux<<endl;
	}
	
	
	
	return 0;
}
