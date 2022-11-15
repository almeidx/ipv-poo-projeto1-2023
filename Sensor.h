#ifndef SENSOR_H
#define SENSOR_H

#include "Uteis.h"
#include <iostream>

using namespace std;

class Sensor {
	int id;
	string marca;
	float valor, probabilidade_avaria;
	Ponto *posicao;

public:
	Sensor(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao);
	~Sensor();
};

class SLuz : public Sensor {
public:
	SLuz(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~SLuz();
};

class SHumidade : public Sensor {
public:
	SHumidade(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~SHumidade();
};

class SFumo : public Sensor {
public:
	SFumo(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~SFumo();
};

class SMissil : public Sensor {
public:
	SMissil(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~SMissil();
};

class SFogo : public Sensor {
public:
	SFogo(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~SFogo();
};

class STemperatura : public Sensor {
public:
	STemperatura(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao)
		: Sensor(id, marca, valor, probabilidade_avaria, posicao) {}
	~STemperatura();
};

#endif // SENSOR_H
