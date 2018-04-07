#include "Dato.hpp"
#include "Datos.hpp"
#include "utils.hpp"
#include "Clasificador.hpp"
#include "Relief.hpp"
#include "BL.hpp"
#include "Algevo.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

//3651278846
using namespace std;

int DoError(string message);

int main(int argc, char* argv[])
{
	try
	{
		unsigned seed = 3651278846;//chrono::system_clock::now().time_since_epoch().count();
		Rand::initRndEngGen(seed);
		cout<<seed<<endl;
		
		string name;
		Clasificador c1nn;
		
		//Conjunto sonar
		name = "sonar";
		cout<<"Conjunto "<<name<<endl;
		c1nn.valida(name, "AGE-CA", Alg::computaPesosAGE_CA);
		
		//Conjunto wdbc
		name = "wdbc";
		cout<<"Conjunto "<<name<<endl;
		c1nn.valida(name, "AGE-CA", Alg::computaPesosAGE_CA);
		
		//Conjunto Spambase-460
		name = "Spambase-460";
		cout<<"Conjunto "<<name<<endl;
		
		c1nn.valida(name, "AGE-CA", Alg::computaPesosAGE_CA);
	}
	catch(const runtime_error &error)
	{
		DoError(error.what());
	}
	return 0;
}

int DoError(string message)
{
	// Print the error message in the terminal.
	cerr << message << endl;
	
	return -1;
}
