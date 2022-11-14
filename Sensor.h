#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>

using namespace std;

class Sensor {
	int id;
	string marca;
	float valor, probabilidade_avaria;
	int x, y;

public:
	Sensor(int id, string marca, float valor, float probabilidade_avaria, int x, int y);
	~Sensor();
};

class SLuz : public Sensor {
public:
	SLuz(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~SLuz();
};

class SHumidade : public Sensor {
public:
	SHumidade(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~SHumidade();
};

class SFumo : public Sensor {
public:
	SFumo(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~SFumo();
};

class SMisseis : public Sensor {
public:
	SMisseis(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~SMisseis();
};

class SFogo : public Sensor {
public:
	SFogo(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~SFogo();
};

class STemperatura : public Sensor {
public:
	STemperatura(int id, string marca, float valor, float probabilidade_avaria, int x, int y)
		: Sensor(id, marca, valor, probabilidade_avaria, x, y) {}
	~STemperatura();
};

#endif // SENSOR_H
