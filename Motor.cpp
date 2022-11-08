#include "Motor.h"

Motor::Motor(string id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
			 float probabilidade_avariada) {
	this->id = id;
	this->marca = marca;
	this->consumo_hora = consumo_hora;
	this->temperatura_aviso = temperatura_aviso;
	this->temperatura_paragem = temperatura_paragem;
	this->probabilidade_avariada = probabilidade_avariada;

	temperatura = 0;
	estado = EstadoMotor::STOP;
}

Motor::~Motor() { cout << "Motor " << id << " destruído" << endl; }

bool Motor::Esta_Avariado(const string fname) {
	if (estado == EstadoMotor::AVARIADO) {
		cout << "[" << fname << "] Motor " << id << " está avariado" << endl;
		return true;
	}

	return false;
}

bool Motor::RUN() {
	if (Esta_Avariado(__FUNCTION__))
		return;

	// Se não estiver com estado RUN, colocar
	if (estado != EstadoMotor::RUN) {
		estado = EstadoMotor::RUN;
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

	if (estado == EstadoMotor::START) {
		cout << "[" << __FUNCTION__ << "] Motor " << id << " já está a trabalhar" << endl;
		return;
	}

	estado = EstadoMotor::START;
	temperatura = 0;
}

void Motor::RESTART() {
	// Fazer START() apenas se o STOP() terminar com sucesso
	if (STOP()) {
		START();
	}
}

bool Motor::STOP() {
	if (estado == EstadoMotor::STOP) {
		cout << "[" << __FUNCTION__ << "] Motor " << id << " já está parado!" << endl;
		return false;
	}

	temperatura_paragem = temperatura;
	estado = EstadoMotor::STOP;
}

void Motor::ESTOU_QUENTE() { STOP(); }
