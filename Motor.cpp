#include "Motor.h"

Motor::Motor(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
			 float probabilidade_avariada, int x, int y) {
	this->id = id;
	this->marca = marca;
	this->consumo_hora = consumo_hora;
	this->temperatura_aviso = temperatura_aviso;
	this->temperatura_paragem = temperatura_paragem;
	this->probabilidade_avariada = probabilidade_avariada;

	this->x = x;
	this->y = y;

	temperatura = 0;
	estado = ESTADO_MOTOR::STOP;
}

Motor::~Motor() { cout << "Motor " << id << " destruído" << endl; }

bool Motor::Esta_Avariado(const string fname) {
	if (estado == ESTADO_MOTOR::AVARIADO) {
		cout << "[" << fname << "] Motor " << id << " está avariado" << endl;
		return true;
	}

	return false;
}

bool Motor::RUN() {
	if (Esta_Avariado(__FUNCTION__))
		return false;

	// Se não estiver com estado RUN, colocar
	if (estado != ESTADO_MOTOR::RUN) {
		estado = ESTADO_MOTOR::RUN;
		return true;
	}

	temperatura += 0.1f;
	if (temperatura > temperatura_aviso) {
		ESTOU_QUENTE();
	}

	return true;
}

void Motor::START() {
	if (Esta_Avariado(__FUNCTION__))
		return;

	if (estado == ESTADO_MOTOR::START) {
		cout << "[" << __FUNCTION__ << "] Motor " << id << " já está a trabalhar" << endl;
		return;
	}

	estado = ESTADO_MOTOR::START;
	temperatura = 0;
}

void Motor::RESTART() {
	// Fazer START() apenas se o STOP() terminar com sucesso
	if (STOP()) {
		START();
	}
}

bool Motor::STOP() {
	if (estado == ESTADO_MOTOR::STOP) {
		cout << "[" << __FUNCTION__ << "] Motor " << id << " já está parado!" << endl;
		return false;
	}

	temperatura_paragem = temperatura;
	estado = ESTADO_MOTOR::STOP;

	return true;
}

void Motor::ESTOU_QUENTE() { STOP(); }

MCombostao::~MCombostao() {}

MEletrico::~MEletrico() {}
MInducao::~MInducao() {}
