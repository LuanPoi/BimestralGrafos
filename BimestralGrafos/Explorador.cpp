#include "Explorador.h"
#include <iostream>

using namespace std;

Explorador::~Explorador()
{
	
}

Explorador::Explorador(string path){
	loadFile(path);
	cout << "arquivo carregado" << endl;
	graph = new GrafoM(airport.size(), false);
	cout << "grafo criado" << endl;
	createVertices();
	cout << "vertices criados" << endl;
	createEdges();
	cout << "Arestas criadas" << endl;
}

bool Explorador::loadFile(string path)
{
	try {
		ifstream file(path);
		if (file) {
		string line,
		source,
		destiny;
		Route edge;
		int word;

		int cont = 0;
		while (getline(file,line)) {
			cont++;

			source = "";
			destiny = "";
			for (word = 0; word < line.length() && line[word] != DELIMITER; word++) {}
				//Ignorar primeiro campo do .CSV
			word++;
			for (; word < line.length() && line[word] != DELIMITER; word++) {}
				//Ignorar segundo campo do .CSV
			word++;
			for (; word < line.length() && line[word] != DELIMITER; word++)
				source += line[word];
			word++;
			for (; word < line.length() && line[word] != DELIMITER; word++) {}
				//Ignorar quarto campo do .CSV
			word++;
			for (; word < line.length() && line[word] != DELIMITER; word++)
				destiny += line[word];

			if (source == "" || destiny == "") {				
				throw "Estrutura do arquivo nao e coerente.";
			}
				

			edge.source = source;
			edge.destiny = destiny;
			routes.push_back(edge);

			if (keyExistAirports(source) == -1)
				airport.push_back(source);
			if (keyExistAirports(destiny) == -1)
				airport.push_back(destiny);
		}
		file.close();
		return true;
		}
		throw "Arquivo nao encontrado.";
	}
	catch (const char* message) {
		cerr << message << " loadFile();" << endl;
		return false;
	}
	return false;
}

int Explorador::keyExistAirports(string key) {
	for (int i = 0; i < airport.size(); i++) {
		if (key == airport[i])
			return i;
		}
	return -1;
}

void Explorador::createVertices() {
	for (int i = 0; i < airport.size(); i++)
		graph->setaInformacao(i, airport[i]);
}

void Explorador::createEdges(){
	for (int i = 0; i < routes.size(); i++) {
		graph->criaAdjacencia(keyExistAirports(routes[i].source), keyExistAirports(routes[i].destiny), 1);
	}
}

void Explorador::maiorFluxo(){
	vector<pair<string, int>> maiorFluxo = graph->maiorGrauEntrada();
	std::cout << "\t-> Os 5 aeroportos que possuem maior grau:" << std::endl;
	std::cout << "\t\tGrau\tVertice" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "\t\t" << maiorFluxo[i].second << "\t" << maiorFluxo[i].first << std::endl;
	}
}

void Explorador::maisRelevantes() {
	vector<pair<string, int>> maisRelevantes = graph->maiorCentrIntermediacao();
	std::cout << "\t-> Os 5 aeroportos mais relevantes de acordo com a centralidade de intermediação:" << std::endl;
	std::cout << "\t\tGrau\tVertice" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "\t\t" << maisRelevantes[i].second << "\t" << maisRelevantes[i].first << std::endl;
	}

}