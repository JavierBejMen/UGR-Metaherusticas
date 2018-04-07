/***************************************************************/
// Fichero: tamanio3.cpp
//
// Calcula el tamaño (en bytes y Kbytes) de un fichero,
// independeientemente de su contenido.
// El tamaño se calcula usando una función creada a tal efecto.
/***************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
/***************************************************************/
int tam_file (char *nombre);
/***************************************************************/
int main (int argc, char **argv)
{
	if (argc != 2) {
		cerr << "Error: Num. de params. erroneo\n";
		cerr << "Uso: " << argv[0]<< " <fich>\n";
		exit (1);
	}
	// Llamar a la función que calcula el tamaño de un fichero
	int tam = tam_file (argv[1]);
	cout.setf (ios::fixed);
	cout << "\nFichero: " << argv[1] << setw(10) << tam << " bytes, ";
	cout << setprecision(2) << setw(8) << tam/1024.0 << " Kb.\n\n";
	return (0);
}
/***************************************************************/
int tam_file (char *nombre)
{
	ifstream fi;
	fi.open (nombre);
	// Abrir fichero
	if (!fi) {
		cerr << "Error: no puedo abrir " << nombre << endl;
		exit (1);
	}
	fi.seekg (0, ios::end);
	int tam = fi.tellg();
	fi.close ();
	// Colocarse al final
	// Obtener posición
	// Cerrar fichero
	return (tam);
}
/***************************************************************/
