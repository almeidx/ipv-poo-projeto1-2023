#include "Sensor.h"

Sensor::Sensor(int id, string marca, float valor, float probabilidade_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->valor = valor;
	this->probabilidade_avaria = probabilidade_avaria;
	this->posicao = posicao;
}

Sensor::~Sensor() {}

SLuz::~SLuz() {}

SHumidade::~SHumidade() {}

SFumo::~SFumo() {}

SMissil::~SMissil() {}

SFogo::~SFogo() {}

STemperatura::~STemperatura() {}
