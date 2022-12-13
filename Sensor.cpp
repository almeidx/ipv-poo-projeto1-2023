#include "Sensor.h"

Sensor::Sensor(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->valor_aviso = valor_aviso;
	this->prob_avaria = prob_avaria;
	this->posicao = posicao;

	valor = Uteis::Generate_Random_Float(1.0, 100.0);
}

Sensor::~Sensor() {
	delete posicao;

	cout << "Sensor " << id << " destruído" << endl;
}

float Sensor::Ler_Valor() {
	int adc_ou_sub = Uteis::Generate_Random_Int(0, 1);

	float val = Uteis::Generate_Random_Int(1.0, 2.5);

	if (!adc_ou_sub || valor - val <= 0) {
		valor += val;
	} else {
		valor -= val;
	}

	return valor;
}

void Sensor::Print() {
	cout << string(10, '-') << " SENSOR " << string(10, '-') << endl;
	cout << "Id:                      " << Get_Id() << endl;
	cout << "Marca:                   " << Get_Marca() << endl;
	cout << "Tipo:                    " << Get_Tipo() << endl;
	cout << "Valor atual:             " << Uteis::Float_To_String_Precisao(Get_Valor_Atual()) << endl;
	cout << "Valor de aviso:          " << Get_Valor_Aviso() << endl;
	cout << "Probabilidade de avaria: " << Get_Prob_Avaria() << endl;
	cout << "Posicao:                 " << Get_Posicao()->To_String() << endl;
	cout << "Em alerta:               " << (Em_Alerta() ? "Sim" : "Nao") << endl;
	cout << string(27, '-') << endl;
}
