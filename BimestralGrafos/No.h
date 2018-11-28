#pragma once
#include <string>
#include <iostream>

using namespace std;

class No
{
private:
	string nome;
public:
	No();
	~No();

	void setNome(string nome);
	string getNome();

};
