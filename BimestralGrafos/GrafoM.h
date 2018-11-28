#pragma once
#include "No.h"
#include <vector>
#include <list>
#define INFINITO 9999
using namespace std;

class GrafoM
{

private:
	bool direcionado;

	int tamanho;	//n° de vertices
	float **matriz;	// tamanho X tamanho
	No *vertices;


	int buscaProfundidadeRecursivo(int origem, int destino, bool *visitado);
	int buscaLarguraRecursivo(int destino, std::list<int> *fila, bool *visitado);
	bool iterarFila(int valor, std::list<int> *fila);
	void verticesNaDistanciaXRecursivo(int vertice, int nivel, int distancia, std::list<int> *lista, int verticeAnterior, int origem);
	int buscaLargura(int origem, int destino);
	void conexoRecursivo(int origem, bool *visitado);
	bool ciclicoRecursivo(int anterior, int origem, bool *visitado);
	string textoRandom(string nomeAnterior);

public:
	GrafoM(int tamanho, bool direcionado);
	GrafoM(int nVertices, int nArestas, bool conexo);	//•	(1,0 Ponto) Gerador de grafo aleatório que recebe as seguintes entradas:N.de nós;N.de arestas;	Se conexo ou não
	GrafoM(string path); //•(0, 5 Ponto) Módulo de carregamento de Grafo de Arquivo(Formato Pajek em anexo);
	~GrafoM();

	void criaAdjacencia(int i, int j, float custo);  // cria uma adjacência entre i e j com custo no grafo G;
	void removeAdjacencia(int i, int j);  // remove a adjacência entre i e j no grafo G;
	void setaInformacao(int i, std::string V);  // atualiza a informação do nó i com o valor V (que deve ser uma string) no grafo G
	bool gravarPajek(string path);	//•	(0,5 Ponto) Módulo de gravação de Grafo, ponderado e rotulado em Arquivo (Formato Pajek em anexo);
	void popular(int nArestas, bool conexo);

	void imprimeAdjacencias();  // imprime a matriz de adjacências do grafo G
	void imprimeVertices();
	int adjacentes(int i, float *adj);  // retorna o número de adjacentes ao vértice i no grafo G e os armazena no vetor adj
	void imprimeCaminho(std::string potato, int s, int t, int *caminho);

	bool** fechamento();
	int melhorCaminho(int s, int t);
	float piorCaminho(int s, int t);
	std::list<int> *verticesNaDistanciaX(int distancia, int vertice);
	int buscaProfundidade(int origem, int destino);
	bool conexo();	//•(0, 5 Ponto) Função que verifica se o grafo é conexo ou não;
	bool ciclico(); //•(0, 5 Ponto) Função que verifica se o grafo é Cíclico ou não;
	GrafoM *kruskal();
	int coeficienteAgrupamentoLocal(int vertice);
	int numArestasVizinhos(int vertice);
	bool euleriano();
	int centralidadePosicionamento(int vertice);
	int * caminhoDijkstra(int origem, int destino);
	float centralidadeIntermediacao(int vertice);
	std::vector<std::pair<std::string, int>> maiorGrauSaida();
	std::vector<std::pair<std::string, int>> maiorGrauEntrada();
	vector<pair<string, int>> maiorCentrIntermediacao();
	int grau(int vertice);
	int getTamanho() { return tamanho; };
	int nVertices();

};


