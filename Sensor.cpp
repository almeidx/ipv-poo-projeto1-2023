#include "Sensor.h"
#include "Fabrica.h"

Sensor::Sensor(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->valor_aviso = valor_aviso;
	this->prob_avaria = prob_avaria;
	this->posicao = posicao;
	this->ptr_fabrica = fabrica;

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

void SLuz::Avisar_Fabrica() {
	Get_Fabrica()->Aviso_Luz(ALERTA_LUZ_FICHEIRO_VIDEO);
}

list<Motor *> SHumidade::Avisar_Fabrica() {
	list<Motor *> motores_desligados;

	Get_Fabrica()->Aviso_Humidade(motores_desligados);

	return motores_desligados;
}

list<Motor *> SFumo::Avisar_Fabrica() {
	list<Motor *> motores_desligados;

	Get_Fabrica()->Aviso_Fumo(motores_desligados, ALERTA_FUMO_FICHEIRO_VIDEO);

	return motores_desligados;
}

void SMissel::Avisar_Fabrica() {
	Get_Fabrica()->Aviso_Missel(ALERTA_MISSEL_FICHEIRO_VIDEO, ALERTA_MISSEL_FICHEIRO_ESTADO);
}
