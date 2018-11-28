#include "GrafoM.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>

GrafoM::GrafoM(int tamanho, bool direcionado) : tamanho(tamanho), direcionado(direcionado){
	matriz = new float*[tamanho];
	for (int i = 0; i < tamanho; i++) {
		matriz[i] = new float[tamanho];
	}
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			matriz[i][j] = INFINITO;
		}
	}
	vertices = new No[tamanho];
}

GrafoM::GrafoM(int nVertices, int nArestas, bool conexo) : tamanho(nVertices){
	srand((unsigned)time(0));
	direcionado = rand() % 2;
	matriz = new float*[tamanho];
	for (int i = 0; i < tamanho; i++) {
		matriz[i] = new float[tamanho];
	}
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			matriz[i][j] = INFINITO;
		}
	}
	vertices = new No[tamanho];
	popular(nArestas, conexo);
}

void GrafoM::popular(int nArestas, bool conexo) {
	//Defini nome de cada vertice
	for (int indice = 0; indice < tamanho; indice++) {
		if(indice == 0)
			vertices[indice].setNome("a");
		else
			vertices[indice].setNome(textoRandom(vertices[indice-1].getNome()));
	}
	//Cria adjacencias
	int origem = (rand()* rand() % tamanho), destino, maxArestas;
	if (direcionado)
		maxArestas = tamanho*tamanho - tamanho;
	else
		maxArestas = (tamanho*tamanho - tamanho) / 2;
	if (nArestas < maxArestas)
		maxArestas = nArestas;

	for (int aresta = 0; aresta < maxArestas; aresta++) {
		destino = (rand()* rand() % tamanho);
		if (matriz[origem][destino] == INFINITO && origem != destino) {
			criaAdjacencia(origem, destino, ((rand() % 100 + 1) % 5));
		}
		else 
			aresta--;
		if (conexo)
			origem = destino;
		else 
			origem = (rand()* rand() % tamanho), destino;
	}
}

string GrafoM::textoRandom(string nomeAnterior) {
	int cont = 0;
	string resultado;
	string alf = "abcdefghijklmnopqrstuvwxyz";
	for (int letra = 0; letra < nomeAnterior.size(); ++letra) {
		if (nomeAnterior[letra] != 'z') {
			cont++;
		}
	}
	if (cont == 0) {
		for (int letra = 0; letra < nomeAnterior.size(); ++letra) {
			nomeAnterior[letra] = 'a';
		}
		nomeAnterior += 'a';
	}
	else {
		for (int letra = 0, cont1 = 0; letra < nomeAnterior.size(); ++letra, ++cont1) {
			if ((nomeAnterior[letra] == 'z') && (letra == nomeAnterior.size() - 1)) {
				nomeAnterior[letra] = 'a';
				cont1--;
				while (nomeAnterior[cont1] == 'z') {
					nomeAnterior[cont1] = 'a';
					cont1--;
				}
				for (int i = 0; i < alf.size(); ++i) {
					if (alf[i] == nomeAnterior[cont1]) {
						nomeAnterior[cont1] = alf[i + 1];
						break;
					}
				}
			}
			else if (letra == nomeAnterior.size() - 1) {
				for (int i = 0; i < alf.size(); ++i) {
					if (alf[i] == nomeAnterior[letra]) {
						nomeAnterior[letra] = alf[i + 1];
						break;
					}
				}
			}

		}
	}

	return nomeAnterior;
}

GrafoM::GrafoM(string path){
	try {
		fstream file(path);
		if (file){
			int caractere;
			string line;
			getline(file, line);
			line.erase(line.begin(), line.begin() + 9);
			for (int c = 0; c < line.size(); c++) { //igorando comentarios na primeira linha
				if (line[c] == '/') {
					if (line[c + 1] == '/') {
						line.erase(line.begin() + c, line.end());
						break;
					}
				}
			}
			tamanho = atoi(line.c_str());
			matriz = new float*[tamanho];
			for (int i = 0; i < tamanho; i++) {
				matriz[i] = new float[tamanho];
			}
			for (int i = 0; i < tamanho; i++) {
				for (int j = 0; j < tamanho; j++) {
					matriz[i][j] = INFINITO;
				}
			}
			//nome dos vertices
			vertices = new No[tamanho];
			while (getline(file, line) && line[0] != '*')
			{

				if (line == "") {
					continue;
				}
				string indice;
				string nome;
				for (caractere = 0; line[caractere] != ' '; caractere++)
				{
					indice += line[caractere];
				}
				caractere += 2;
				for (; line[caractere] != '\"'; caractere++)
				{
					nome += line[caractere];
				}
				setaInformacao(atoi(indice.c_str()) - 1, nome);
			}
			//Identificando direcionamento
			if (line[1] == 'A' && line[2] == 'r' && line[3] == 'c' && line[4] == 's')
				direcionado = true;
			else if (line[1] == 'E' && line[2] == 'd' && line[3] == 'g' && line[4] == 'e' && line[5] == 's')
				direcionado = false;
			else
				throw "Nao e possivel definir direcionamento.";

			//Criando adjacencias
			while (getline(file, line)){
				string origem;
				string destino;
				string valor;
				for (caractere = 0; line[caractere] != ' '; caractere++)
					origem += line[caractere];
				caractere++;
				for (; line[caractere] != ' '; caractere++)
					destino += line[caractere];
				caractere++;
				for (; line[caractere] != '\0'; caractere++) {
					if (line[caractere] == ' ' || line[caractere] == '/') //igorando comentarios
						break;
					valor += line[caractere];
				}

				criaAdjacencia(atoi(origem.c_str()) - 1, atoi(destino.c_str()) - 1, atoi(valor.c_str()));
			}
		}
		else
			throw ("Não foi possivel abrir o arquivo na pasta (" + path + ").");
	}
	catch (const char*mensagem) {
		cerr << mensagem << "  GrafoM::GrafoM(string path)";
		system("pause");
		exit(1);
	}
}

void apagaComentario(string &line) {
	for (int c = 0; c < line.size(); c++) {
		if (line[c] == '/') {
			if (line[c + 1] == '/') {
				line.erase(line.begin() + c, line.end());
			}
		}
	}
	return;
}

GrafoM::~GrafoM(){
}

void GrafoM::criaAdjacencia(int i, int j, float custo) {
	if (i != -1 && j != -1) {
		if (direcionado) {
			matriz[i][j] = custo;
		}
		else {
			matriz[i][j] = custo;
			matriz[j][i] = custo;
		}
	}
	else {
		cout << "Codigo de erro -1, aresta n encontrada, cria_adjacencia();";
		exit(-1);
	}
}

void GrafoM::removeAdjacencia(int i, int j) {
	if (direcionado) {
		matriz[i][j] = INFINITO;
	}
	else {
		matriz[i][j] = INFINITO;
		matriz[j][i] = INFINITO;
	}
}

void GrafoM::imprimeAdjacencias() {
	cout << "Adjacencias: " << endl;
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			if (matriz[i][j] == INFINITO)
				std::cout << 0 << " ";
			else
				std::cout << matriz[i][j] << " ";
		}
		std::cout << std::endl;
	}
	cout << endl;
}

void GrafoM::imprimeVertices() {
	cout << "Vertices: " << endl;
	for (int indice = 0; indice < tamanho; indice++) {
		cout << indice << " \"" << vertices[indice].getNome() << "\"" << endl;
	}
	cout << endl;
}

void GrafoM::setaInformacao(int i, std::string V) {
	vertices[i].setNome(V);
}

int GrafoM::adjacentes(int i, float *adj) {
	int k = 0;
	for (int j = 0; j < tamanho; j++) {
		if (matriz[i][j] != INFINITO) {
			adj[k] = j;
			k++;
		}
	}
	for (int j = k; j < tamanho; j++) {
		adj[j] = INFINITO;
	}
	return k;
}

bool** GrafoM::fechamento(){
	bool **fechamento = new bool*[tamanho];
	for (int i = 0; i < tamanho; i++) {
		fechamento[i] = new bool[tamanho];
	}
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			if (matriz[i][j] != INFINITO) {
				fechamento[i][j] = true;
			}
			else {
				fechamento[i][j] = false;
			}
		}
	}
	std::cout << "Antes:" << std::endl;
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			std::cout << fechamento[i][j] << " ";
		}
		std::cout << std::endl;
	}		
	//algoritmo de Warshall
	int i, j, k;
	for (k = 0; k < tamanho; k++)
	{
		for (i = 0; i < tamanho; i++)
		{
			if (fechamento[i][k])
				for (j = 0; j < tamanho; j++)
					fechamento[i][j] = fechamento[i][j] || fechamento[k][j];
		}
	}
	std::cout << "Depois:" << std::endl;
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			std::cout << fechamento[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return fechamento;
}

int GrafoM::melhorCaminho(int s, int t) {
	bool MEMBRO = true;
	bool NAOMEMBRO = false;
	int *caminho = new int[tamanho];
	int *distancia = new int[tamanho];
	bool *perm = new bool[tamanho];
	int corrente, k = s, dc, j = 0;
	int menordist, novadist;
	//inicialização
	for (int i = 0; i < tamanho; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] = INFINITO;
		caminho[i] = -1;
	}
	perm[s] = MEMBRO;
	distancia[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = INFINITO;
		dc = distancia[corrente];
		for (int i = 0; i < tamanho; i++) {
			if (!perm[i]) {
				novadist = dc + matriz[corrente][i];
				if (novadist < distancia[i]) {

					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] < menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;
		perm[corrente] = MEMBRO;
	}
	//imprimeCaminho("Melhor",s, t, caminho);
	return distancia[t];

}

void GrafoM::imprimeCaminho(std::string potato, int s, int t, int *caminho) {
	int i = t;
	std::cout << potato << " caminho: " << t << "-";
	while (i != s) {
		std::cout << caminho[i] << "-";
		i = caminho[i];
	}
	std::cout << std::endl;
	return;
}

float GrafoM::piorCaminho(int s, int t) {
	bool MEMBRO = true;
	bool NAOMEMBRO = false;
	float *distancia = new float[tamanho];
	int *caminho = new int[tamanho];
	bool *perm = new bool[tamanho];
	int corrente, k = s, j = 0;
	float menordist, novadist, dc;
	for (int i = 0; i < tamanho; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] = 0;
		caminho[i] = -1;
	}
	perm[s] = MEMBRO;
	distancia[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = 0;
		dc = distancia[corrente];
		for (int i = 0; i < tamanho; i++) {
			if (!perm[i]) {
				if (matriz[corrente][i] != INFINITO)
					novadist = dc + matriz[corrente][i];
				if (novadist > distancia[i]) {

					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] > menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;
		perm[corrente] = MEMBRO;
	}
	imprimeCaminho("Pior", s, t, caminho);
	return distancia[t];
}

std::list<int> *GrafoM::verticesNaDistanciaX(int distancia, int vertice) {
	int *perm = new int(tamanho);
	for (int i = 0; i < tamanho; i++) 
		perm[i] = false;
	std::list<int> *lista = new std::list<int>();
	verticesNaDistanciaXRecursivo(vertice, 1, distancia, lista, -1, vertice);
	return lista;
}

void GrafoM::verticesNaDistanciaXRecursivo(int vertice, int nivel, int distancia, std::list<int> *lista, int verticeAnterior, int origem) {
	if (nivel == distancia) {
		for (int i = 0; i < tamanho; i++) {
			if (i != origem) {
				if (i != verticeAnterior) {
					if (matriz[vertice][i] != INFINITO) {
						bool repetido = false;
						for (std::list<int>::iterator it = lista->begin(); it != lista->end(); it++) {
							if (*it == i) {
								repetido = true;
							}
						}
						if (repetido == false) {
							lista->push_back(i);
						}
					}
				}
			}
		}
		return;
	}
	for (int i = 0; i < tamanho; i++) {
		if (i != origem) {
			if (i != verticeAnterior) {
				if (matriz[vertice][i] != INFINITO) {
					verticeAnterior = vertice;
					verticesNaDistanciaXRecursivo(i, nivel + 1, distancia, lista, verticeAnterior, origem);
				}
			}
		}
	}
}

int GrafoM::buscaProfundidade(int origem, int destino) {
	bool *visitado = new bool[tamanho];
	for (int i = 0; i < tamanho; i++) 
		visitado[i] = false;
	std::cout << "Iniciando busca em profundidade..." << std::endl;
	int x = buscaProfundidadeRecursivo(origem, destino, visitado);
	if (x == 1){
		std::cout << origem << "-> achou!" << std::endl;
	}
	else{
		std::cout << "Não foi encontrado um caminho." << std::endl;
	}
	return x;
}

int GrafoM::buscaProfundidadeRecursivo(int origem, int destino, bool *visitado) {
	if (origem == destino)
		return 1;
	else
	{
		if (visitado[origem] == false)
		{
			visitado[origem] = true;
			for (int i = 0; i < tamanho; i++)
			{
				if (matriz[origem][i] != INFINITO && visitado[i] == false)
				{
					int x = buscaProfundidadeRecursivo(i, destino, visitado);
					if (x == 1)
					{
						std::cout << i << "-";
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int GrafoM::buscaLargura(int origem, int destino)
{
	bool *visitado = new bool[tamanho];
	for (int i = 0; i < tamanho; i++){
		visitado[i] = false;
	}
	std::list<int> fila;
	fila.push_back(origem);
	std::cout << "Iniciando busca em largura..." << std::endl;
	int x = buscaLarguraRecursivo(destino, &fila, visitado);
	return 1;
}

int GrafoM::buscaLarguraRecursivo(int destino, std::list<int> *fila, bool *visitado){
	if (fila->empty())
		return 0;
	else {
		int x = fila->front();
		fila->pop_front();
		visitado[x] = true;
		if (x == destino)
		{
			std::cout << "Um caminho foi encontrado." << std::endl;
			return 1;
		}
		for (int i = 0; i < tamanho; i++)
		{
			if (visitado[i] == false && matriz[x][i] != INFINITO && !iterarFila(x, fila))
			{
				fila->push_front(i);
			}
		}
		buscaLarguraRecursivo(destino, fila, visitado);
	}
	return 0;
}

bool GrafoM::iterarFila(int valor, std::list<int> *fila) {
	for (auto it = fila->begin(); it != fila->end(); it++) {
		if (*it == valor)
			return true;
	}
	return false;
}

bool GrafoM::conexo() {
	bool resultado = true;
	bool *visitado = new bool[tamanho];
	for (int i = 0; i < tamanho; i++)
		visitado[i] = false;
	conexoRecursivo(0, visitado);
	for (int i = 0; i < tamanho; i++) {
		if (visitado[i] == false) {
			resultado = false;
		}
	}
	return resultado;
}

void GrafoM::conexoRecursivo(int origem, bool *visitado) {
	if (visitado[origem] == false) {
		visitado[origem] = true;
		for (int i = 0; i < tamanho; i++)
		{
			if (matriz[origem][i] != INFINITO && visitado[i] == false)
			{
				conexoRecursivo(i, visitado);
			}
		}
	}
	return;
}

bool GrafoM::ciclico() {
	bool *visitado = new bool[tamanho];
	for (int i = 0; i < tamanho; i++)
		visitado[i] = false;
	if (conexo())
		return ciclicoRecursivo(0, 0, visitado);
	else {
		for (int i = 0; i < tamanho; i++) {
			if (ciclicoRecursivo(i, i, visitado)) {
				return true;
			}
		}
		return false;
	}
}

bool GrafoM::ciclicoRecursivo(int anterior, int atual, bool *visitado) {
	bool resposta = false;
	if (visitado[atual] == false) {
		visitado[atual] = true;
		for (int adjacente = 0; adjacente < tamanho; adjacente++)
		{
			if (matriz[atual][adjacente] != INFINITO && atual != adjacente) {
				if (visitado[adjacente] == false) {
					resposta = ciclicoRecursivo(atual, adjacente, visitado);
				}
				else if (adjacente != anterior) {
					//std::cout << "Anterior " << anterior << "  Origem " << atual << "  Atual " << adjacente << std::endl;
					return true;
				}
			}
		}
	}
	return resposta;
}

GrafoM *GrafoM::kruskal() {
	GrafoM *arvore = new GrafoM(tamanho, direcionado);
	using Aresta = struct aresta {
		int origem, destino, valor;
	};
	list<Aresta> lista;
	Aresta aux;
	bool pushOk = false;
	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			if (matriz[i][j] != INFINITO) {
				aux.origem = i;
				aux.destino = j;
				aux.valor = matriz[i][j];
				if (lista.size() == 0) {
					lista.push_back(aux);
				}
				else {
					for (list<Aresta>::iterator it = lista.begin(); it != lista.end(); it++) {
						if (aux.valor <= (*it).valor) {
							lista.insert(it, aux);
							pushOk = true;
							break;
						}
					}
					if (!pushOk) {
						lista.push_back(aux);
					}
					pushOk = false;
				}
			}
		}
	}
	for (list<Aresta>::iterator it = lista.begin(); it != lista.end(); it++) {
		arvore->criaAdjacencia((*it).origem, (*it).destino, (*it).valor);
		if (arvore->ciclico()) {
			arvore->removeAdjacencia((*it).origem, (*it).destino);
		}
		if (arvore->conexo()) {
			return arvore;
		}
	}
	delete arvore;
	cerr << "Nao foi possivel gerar a arvore. GrafoM::kruskall();";
	return NULL;
}

int GrafoM::coeficienteAgrupamentoLocal(int vertice) {
	//Digrafo
	if (direcionado) 
		return numArestasVizinhos(vertice) / (grau(vertice)*(grau(vertice) - 1));
	else 
		return 2 * (numArestasVizinhos(vertice) / (grau(vertice)*(grau(vertice) - 1)));
	//não direcionado


	return 1;
}

int GrafoM::numArestasVizinhos(int vertice) {
	vector<int> vizinhos;
	int numArestasVizinhos = 0;
	for (int vizinho = 0; vizinho < tamanho; vizinho++) {
		if (matriz[vertice][vizinho] != INFINITO) {
			vizinhos.push_back(vizinho);
		}
	}
	for (int i = 0; i < vizinhos.size(); i++) {
		for (int aresta = 0; aresta < tamanho; aresta++) {

			if (matriz[vizinhos[i]][aresta] != INFINITO && aresta != vertice) {
				numArestasVizinhos++;
			}
		}
	}
	return numArestasVizinhos;
}

bool GrafoM::gravarPajek(string path)
{
	try {
		ofstream file(path);

		if (file)
		{
			file << "*Vertices " << tamanho << endl;
			for (int vertice = 0; vertice < tamanho; vertice++) 
				file << vertice + 1 << " \"" << vertices[vertice].getNome() << "\"" << endl;
			if (direcionado)
				file << "*Arcs " << endl;
			else
				file << "*Edges " << endl;
			if (direcionado) {
				for (int i = 0; i < tamanho; i++)
				{
					for (int j = 0; j < tamanho; j++)
					{
						if (matriz[i][j] != INFINITO)
						{
							file << i + 1 << " " << j + 1 << " " << matriz[i][j] << endl;
						}
					}
				}
			}
			else {
				for (int i = 0; i < tamanho; i++)
				{
					for (int j = i; j < tamanho; j++)
					{
						if (matriz[i][j] != INFINITO)
						{
							file << i + 1 << " " << j + 1 << " " << matriz[i][j] << endl;
						}
					}
				}
			}
			file.close();
			return true;
		}
		else
			throw ("Não foi possivel abrir o arquivo na pasta (" + path + ").");
	}
	catch (const char*mensagem) {
		cerr << mensagem << "   GrafoM::gravarPajek(string path)." << endl;
		return false;
	}
}

bool GrafoM::euleriano(){
	int grauImpar = 0;
	for (int vertice = 0; vertice < tamanho; vertice++) {		
		if ((grau(vertice) % 2) != 0) 
			grauImpar++;
	}
	
	if (grauImpar == 0 || grauImpar == 2) 
		return true;
	else 
		return false;
}

int GrafoM::grau(int vertice) {
	int grau = 0;
	for (int adjacente = 0; adjacente < tamanho; adjacente++) {
		if (matriz[vertice][adjacente] != INFINITO) {
			grau++;
		}
	}
	return grau;
}

int GrafoM::centralidadePosicionamento(int vertice) {
	double peso = 0;
	for (int i = 0; i < tamanho; i++) {
		peso += melhorCaminho(vertice, i);
	}
	return 0;
}

int* GrafoM::caminhoDijkstra(int s, int t) {
	bool MEMBRO = true;
	bool NAOMEMBRO = false;
	int *caminho = new int[tamanho];
	int *distancia = new int[tamanho];
	bool *perm = new bool[tamanho];
	int corrente, k = s, dc, j = 0;
	int menordist, novadist;
	//inicialização
	for (int i = 0; i < tamanho; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] = INFINITO;
		caminho[i] = -1;
	}
	perm[s] = MEMBRO;
	distancia[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = INFINITO;
		dc = distancia[corrente];
		for (int i = 0; i < tamanho; i++) {
			if (!perm[i]) {
				novadist = dc + matriz[corrente][i];
				if (novadist < distancia[i]) {

					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] < menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;
		perm[corrente] = MEMBRO;
	}
	//imprimeCaminho("Melhor",s, t, caminho);
	return caminho;

}

float GrafoM::centralidadeIntermediacao(int vertice) {

	int *melhor_caminho = new int[tamanho];
	int contador = 0;
	int controlador = 0;
	float resultado = 0;
	for (int origem = 0; origem < tamanho; origem++) {
		for (int destino = 0; destino < tamanho; destino++) {
			controlador = destino;
			melhor_caminho = caminhoDijkstra(origem, destino);
			while (controlador != origem) {
				if (vertice != origem && melhor_caminho[controlador] == vertice)
				{
					contador++;
				}
				controlador = melhor_caminho[controlador];
			}
		}
	}

	if (direcionado) 
		resultado = (float)contador / ((tamanho - 1)*(tamanho - 2));
	else 
		resultado = (float)contador / (((tamanho - 1)*(tamanho - 2))/2);


	resultado = (float)contador / ((tamanho - 1)*(tamanho - 2));


	return resultado;
}

std::vector<std::pair<std::string, int>> GrafoM::maiorGrauSaida() {
	std::vector<std::pair<std::string, int>> maiorGrau;
	std::pair<std::string, int> p;
	p.second = 0;
	for (int i = 0; i < 20; i++)
		maiorGrau.push_back(p);
	for (int indice = 0; indice < tamanho; indice++) {
		int grauAtual = 0;
		for (int adjacente = 0; adjacente < tamanho; adjacente++) {
			if (matriz[indice][adjacente] != INFINITO) {
				grauAtual++;
			}
		}
		for (int posicao = 0; posicao < 20; posicao++) {
			if (grauAtual > maiorGrau[posicao].second) {
				std::string verticeAtual = vertices[indice].getNome();
				for (int troca = posicao; troca < 20; troca++) {
					std::string verticeAux = maiorGrau[troca].first;
					int grauAux = maiorGrau[troca].second;

					maiorGrau[troca].first = verticeAtual;
					maiorGrau[troca].second = grauAtual;

					verticeAtual = verticeAux;
					grauAtual = grauAux;
				}
			}
		}
	}
	std::cout << "\t -> Os 20 individuos que possuem maior grau de saida:" << std::endl;
	std::cout << "\t\tGrau\tVertice" << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << "\t\t" << maiorGrau[i].second << "\t" << maiorGrau[i].first << std::endl;
	}
	return maiorGrau;
}

vector<pair<string, int>> GrafoM::maiorGrauEntrada() {
	std::vector<std::pair<std::string, int>> maiorGrau;
	std::pair<std::string, int> p;
	p.second = 0;
	for (int i = 0; i < 20; i++) {
		maiorGrau.push_back(p);
	}
	for (int adjacente = 0; adjacente < tamanho; adjacente++) {
		int grauAtual = 0;
		for (int indice = 0; indice < tamanho; indice++) {
			if (matriz[indice][adjacente] != INFINITO) {
				grauAtual++;
			}
		}
		for (int posicao = 0; posicao < 20; posicao++) {
			if (grauAtual > maiorGrau[posicao].second) {
				std::string verticeAtual = vertices[adjacente].getNome();
				for (int troca = posicao; troca < 20; troca++) {
					std::string verticeAux = maiorGrau[troca].first;
					int grauAux = maiorGrau[troca].second;

					maiorGrau[troca].first = verticeAtual;
					maiorGrau[troca].second = grauAtual;

					verticeAtual = verticeAux;
					grauAtual = grauAux;
				}
			}
		}
	}
	return maiorGrau;
}

vector<pair<string, int>> GrafoM::maiorCentrIntermediacao() {

	std::vector<std::pair<std::string, int>> centrInterm;
	std::pair<std::string, int> p;
	p.second = 0;
	for (int i = 0; i < 5; i++) {
		centrInterm.push_back(p);
	}
	for (int i = 0; i < tamanho; i++) {
		int intermAtual = centralidadeIntermediacao(i);

		for (int posicao = 0; posicao < 20; posicao++) {
			if (intermAtual > centrInterm[posicao].second) {
				std::string verticeAtual = vertices[i].getNome();
				for (int troca = posicao; troca < 20; troca++) {
					std::string verticeAux = centrInterm[troca].first;
					int grauAux = centrInterm[troca].second;

					centrInterm[troca].first = verticeAtual;
					centrInterm[troca].second = intermAtual;

					verticeAtual = verticeAux;
					intermAtual = grauAux;
				}
			}
		}
	}
	return centrInterm;

}

int GrafoM::nVertices() {
	int num = 0;
	for (int i = 0; i < tamanho; i++)
		for (int j = 0; j < tamanho; j++)
			if (matriz[i][j] != INFINITO)
				num++;
	return num;
}