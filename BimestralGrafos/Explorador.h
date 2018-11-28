#include "GrafoM.h"
#include <string>
#include <fstream>
#include <vector>

#define DELIMITER ','

using namespace std;

using Route = struct rout {
	string source, destiny;
};
class Explorador
{
	//private:
public:
	GrafoM *graph;

	vector<string> airport;
	vector<Route> routes;


	//public:
	Explorador(string path);
	~Explorador();

	bool loadFile(string path);
	int keyExistAirports(string key);
	void createVertices();
	void createEdges();

	//Aeroportos com maior grau de Entrada e saida
	void maiorFluxo();

	void maisRelevantes();


};
