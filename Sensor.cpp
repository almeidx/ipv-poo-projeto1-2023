#include "Sensor.h"

Sensor::Sensor(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->valor_aviso = valor_aviso;
	this->prob_avaria = prob_avaria;
	this->posicao = posicao;

	valor = (rand() % 100) + 1;
}

float Sensor::Get_Valor() {
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
