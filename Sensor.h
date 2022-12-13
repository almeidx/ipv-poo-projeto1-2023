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
	float valor, valor_aviso, prob_avaria;
	Ponto *posicao;

public:
	Sensor(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao);
	~Sensor();

	int Get_Id() {
		return id;
	}
	string Get_Marca() {
		return marca;
	}
	float Get_Prob_Avaria() {
		return prob_avaria;
	}
	float Get_Valor_Atual() {
		return valor;
	}
	Ponto *Get_Posicao() {
		return posicao;
	}
	float Get_Valor_Aviso() {
		return valor_aviso;
	}

	bool Em_Alerta() {
		return Get_Valor_Atual() >= Get_Valor_Aviso();
	}

	virtual string Get_Tipo() {
		return "???";
	}

	float Ler_Valor();
	void Print();
};

class SLuz : public Sensor {
public:
	SLuz(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~SLuz();

	string Get_Tipo() {
		return "SLUZ";
	}
};

class SHumidade : public Sensor {
public:
	SHumidade(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~SHumidade();

	string Get_Tipo() {
		return "SHUMIDADE";
	}
};

class SFumo : public Sensor {
public:
	SFumo(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~SFumo();

	string Get_Tipo() {
		return "SFUMO";
	}
};

class SMissel : public Sensor {
public:
	SMissel(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~SMissel();

	string Get_Tipo() {
		return "SMISSEL";
	}
};

class SFogo : public Sensor {
public:
	SFogo(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~SFogo();

	string Get_Tipo() {
		return "SFOGO";
	}
};

class STemperatura : public Sensor {
public:
	STemperatura(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(id, marca, valor_aviso, prob_avaria, posicao) {}
	~STemperatura();

	string Get_Tipo() {
		return "STEMPERATURA";
	}
};

#endif // SENSOR_H
