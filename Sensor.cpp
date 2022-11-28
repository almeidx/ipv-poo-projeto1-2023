#include "Sensor.h"

Sensor::Sensor(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->valor_aviso = valor_aviso;
	this->prob_avaria = prob_avaria;
	this->posicao = posicao;

	valor = (rand() % 100) + 1;
}
