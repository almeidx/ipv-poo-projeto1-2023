#ifndef SENSOR_H
#define SENSOR_H

#include "Uteis.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Sensor {
	int id;
	string marca;
	float valor, valor_aviso, probabilidade_avaria;
	Ponto *posicao;

public:
	Sensor(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao);
	~Sensor();

	Ponto *Get_Posicao() { return posicao; }
	float Get_Valor_Aviso() { return valor_aviso; }
	bool Em_Alerta() { return Get_Valor() >= Get_Valor_Aviso(); }

	virtual string Get_Tipo() { return "???"; }

	float Get_Valor() {
		// Gerar um número aleatório de 0-1 para decidir se devemos adicionar ou remover valores
		int adc_ou_sub = rand() % 2;
		int n = Uteis::Generate_Random_Number(1, 30);

		if (!adc_ou_sub) {
			valor += n;
		} else {
			valor -= n;
		}

		return valor;
	}
};

class SLuz : public Sensor {
public:
	SLuz(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~SLuz();

	string Get_Tipo() { return "Luz"; }
};

class SHumidade : public Sensor {
public:
	SHumidade(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~SHumidade();

	string Get_Tipo() { return "Humidade"; }
};

class SFumo : public Sensor {
public:
	SFumo(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~SFumo();

	string Get_Tipo() { return "Fumo"; }
};

class SMissil : public Sensor {
public:
	SMissil(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~SMissil();

	string Get_Tipo() { return "Missil"; }
};

class SFogo : public Sensor {
public:
	SFogo(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~SFogo();

	string Get_Tipo() { return "Fogo"; }
};

class STemperatura : public Sensor {
public:
	STemperatura(int id, string marca, float valor_aviso, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, probabilidade_avaria, posicao) {}
	~STemperatura();

	string Get_Tipo() { return "Temperatura"; }
};

#endif // SENSOR_H
