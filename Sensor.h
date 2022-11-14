#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>

using namespace std;

class Sensor {
	string id;
	string marca;
	float valor;
	float probabilidade_avaria;

public:
	Sensor(string id, string marca, float valor, float probabilidade_avaria);
	~Sensor();
};

class SensorLuz : public Sensor
{
public:
	SensorLuz(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorLuz();
};

class SHumidade : public Sensor
{
public:
	SHumidade(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SHumidade();
};


class SFumo : public Sensor
{
public:
	SFumo(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SFumo();
};

class SMisseis : public Sensor
{

public:
   	 SMisseis(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SMisseis();
};

class SFogo : public Sensor
{

public:
   	 SFogo(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SFogo();
};

class STemperatura : public Sensor
{

public:
   	 STemperatura(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~STemperatura();
};







#endif // SENSOR_H
