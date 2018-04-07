#include "Clasificador.hpp"
#include "Relief.hpp"
#include "BL.hpp"
#include "ES.hpp"

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
		c1nn.valida5f(name, "ES", SimulatedAnnealing::computaPesos);
		
		//Conjunto wdbc
		name = "wdbc";
		cout<<"Conjunto "<<name<<endl;
		c1nn.valida5f(name, "ES", SimulatedAnnealing::computaPesos);
		
		//Conjunto Spambase-460
		name = "Spambase-460";
		cout<<"Conjunto "<<name<<endl;
		
		c1nn.valida5f(name, "ES", SimulatedAnnealing::computaPesos);
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
