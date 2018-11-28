#include <iostream>
#include "GrafoM.h"
#include "Explorador.h"
#include <fstream>

using namespace std;

int main() {
	int verticeDaVez = 2;

	int numNos = 5000, numArestas = 20000;						//
	bool conexo = false;										// 
	GrafoM aleatorio(numNos, numArestas, conexo);				// 
	aleatorio.gravarPajek("pajek\\grafoAleatorio.net");		    //  grafo aleatório
	cout << "Tamanho do grafo (aleatorio):" << endl;			// 
	cout << aleatorio.getTamanho() << endl;						//

	GrafoM grafo("pajek\\grafoAleatorio.net");

	cout << "Grafo conexo: " << endl;
	(grafo.conexo()) ? (cout << "Sim" << endl) : (cout << "Nao" << endl);

	cout << "Grafo euleriano: " << endl;
	(grafo.euleriano()) ? (cout << "Sim" << endl) : (cout << "Nao" << endl);
	
	cout << "Grafo ciclico: " << endl;
	(grafo.ciclico()) ? (cout << "Sim" << endl) : (cout << "Nao" << endl);
	/*
	cout << "Centralidade de Posicionamento: " << endl;
	cout << grafo.centralidadePosicionamento(verticeDaVez) << endl;
	
	cout << "Centralidade de Intermediacao: " << endl;
	cout << grafo.centralidadeIntermediacao(verticeDaVez) << endl;
	*/
	
	/*
	try {
		Explorador openFlights("pajek\\exemplo.net");
		cout << "--- Problema aplicado --- " << endl;
		cout << "Nos:" << endl;
		cout << openFlights.graph->getTamanho() << endl;

		cout << "Arestas:" << endl;
		cout << openFlights.graph->nVertices() << endl;

		openFlights.maiorFluxo();
	}
	catch (string erro) {
		cout << erro << endl;
	}*/
	system("pause");
	return 0;
}
