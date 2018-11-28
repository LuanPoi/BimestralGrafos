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

	int tamanho;	//n� de vertices
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
	GrafoM(int nVertices, int nArestas, bool conexo);	//�	(1,0 Ponto) Gerador de grafo aleat�rio que recebe as seguintes entradas:N.de n�s;N.de arestas;	Se conexo ou n�o
	GrafoM(string path); //�(0, 5 Ponto) M�dulo de carregamento de Grafo de Arquivo(Formato Pajek em anexo);
	~GrafoM();

	void criaAdjacencia(int i, int j, float custo);  // cria uma adjac�ncia entre i e j com custo no grafo G;
	void removeAdjacencia(int i, int j);  // remove a adjac�ncia entre i e j no grafo G;
	void setaInformacao(int i, std::string V);  // atualiza a informa��o do n� i com o valor V (que deve ser uma string) no grafo G
	bool gravarPajek(string path);	//�	(0,5 Ponto) M�dulo de grava��o de Grafo, ponderado e rotulado em Arquivo (Formato Pajek em anexo);
	void popular(int nArestas, bool conexo);

	void imprimeAdjacencias();  // imprime a matriz de adjac�ncias do grafo G
	void imprimeVertices();
	int adjacentes(int i, float *adj);  // retorna o n�mero de adjacentes ao v�rtice i no grafo G e os armazena no vetor adj
	void imprimeCaminho(std::string potato, int s, int t, int *caminho);

	bool** fechamento();
	int melhorCaminho(int s, int t);
	float piorCaminho(int s, int t);
	std::list<int> *verticesNaDistanciaX(int distancia, int vertice);
	int buscaProfundidade(int origem, int destino);
	bool conexo();	//�(0, 5 Ponto) Fun��o que verifica se o grafo � conexo ou n�o;
	bool ciclico(); //�(0, 5 Ponto) Fun��o que verifica se o grafo � C�clico ou n�o;
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


