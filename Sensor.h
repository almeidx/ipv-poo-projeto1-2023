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

class SensorHumidade : public Sensor
{
public:
	SensorHumidade(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorHumidade();
};


class SensorFumo : public Sensor
{
public:
	SensorFumo(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorFumo();
};

class SensorMisseis : public Sensor
{

public:
   	 SensorMisseis(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorMisseis();
};

class SensorFogo : public Sensor
{

public:
   	 SensorFogo(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorFogo();
};

class SensorTemperatura : public Sensor
{

public:
   	 SensorTemperatura(string id, string marca, float valor, float probabilidade_avaria) : Sensor(id, marca, valor, probabilidade_avaria) {}
	~SensorTemperatura();
};







#endif // SENSOR_H
