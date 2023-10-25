#include <fstream>  
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int calculatePunctuation(const vector<int>& puestos)
{
	const vector<int> puntos{ 10,8,6,5,4,3,2,1 };

	int suma = 0;
	for (auto puesto : puestos) {
		if (puesto > 0 && puesto < puntos.size() + 1)
			suma += puntos[puesto - 1];
	}
	return suma;
}

void puntuation(vector<string>& pilotos, vector<int>& puntos, string nombre_fichero)
{
	ifstream fich(nombre_fichero);
	if (!fich.is_open())
	{
		cout << "Error al abrir " << nombre_fichero << "\n";
		exit(EXIT_FAILURE);
	}

	string n_carreras;
	getline(fich, n_carreras);//se lee la línea y se convierte su valor de texto a entero con atoi (ANSI to integer)
	int num_carreras = atoi(n_carreras.c_str()); //funciona con stoi
	string n_pilotos;
	getline(fich, n_pilotos);
	int num_pilotos = atoi(n_pilotos.c_str());

	pilotos.clear();  // Por si vienen con datos a la función
	puntos.clear();

	for (int i = 0; i < num_pilotos; i++)
	{
		string piloto;
		getline(fich, piloto);
		pilotos.push_back(piloto);
		vector<int> puestos;

		int puesto;
		string s_puestos;
		getline(fich, s_puestos);
		for (int j = 0; j < num_carreras; j++)
		{
			int pos = 0;
			while  (pos = s_puestos.find(";") != string::npos) {
				if (pos == string::npos)
					pos = s_puestos.find(";");
				if (pos != string::npos) {
					puesto = atoi(s_puestos.substr(0, pos).c_str());
					s_puestos.erase(0, pos + 1);//se elimina de la cadena de puestos el dato extraído
					puestos.push_back(puesto);
				}
			}
		}
		puntos.push_back(calculatePunctuation(puestos));
	}
	fich.close();
}

void muestra_puntuacion(const vector<string>& pilotos, const vector<int>& puntos)
{
	cout << "\nLa puntuacion actual es:\n\n";
	for (int i = 0; i < pilotos.size(); i++)
		cout << pilotos[i] << ":" << puntos[i] << endl;
	cout << endl << endl;
}

int main()
{
	vector<string> pilotos;
	vector<int> puntos;
	puntuation(pilotos, puntos, "pilotos_clasificaciones.txt");
	muestra_puntuacion(pilotos, puntos);
}