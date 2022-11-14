#include "Sensor.h"

Sensor::Sensor(int id, string marca, float valor, float probabilidade_avaria, int x, int y) {
	this->id = id;
	this->marca = marca;
	this->valor = valor;
	this->probabilidade_avaria = probabilidade_avaria;
	this->x = x;
	this->y = y;
}

Sensor::~Sensor() {}

SLuz::~SLuz() {}

SHumidade::~SHumidade() {}

SFumo::~SFumo() {}

SMisseis::~SMisseis() {}

SFogo::~SFogo() {}

STemperatura::~STemperatura() {}
