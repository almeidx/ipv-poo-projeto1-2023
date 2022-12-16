#include "Motor.h"
#include "Fabrica.h"

Motor::Motor(Fabrica *fabrica, int id, string marca, float consumo_hora, float temperatura_aviso,
			 float temperatura_paragem, float prob_avaria, Ponto *posicao) {
	this->id = id;
	this->marca = marca;
	this->consumo_hora = consumo_hora;
	this->temperatura_aviso = temperatura_aviso;
	this->temperatura_paragem = temperatura_paragem;
	this->prob_avaria = prob_avaria;

	ptr_fabrica = fabrica;

	this->posicao = posicao;

	temperatura = 0;
	estado = ESTADO_MOTOR::STOP;
	horas_trabalho = 0;
	ultima_hora_registada = 0;
	consumo_atual = 0;
}

Motor::~Motor() {
	delete posicao;

	cout << "Motor " << id << " destruído" << endl;
}

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
		ultima_hora_registada = ptr_fabrica->Get_Horas();
		return true;
	}

	temperatura += Uteis::Generate_Random_Float(0.1, 1.0);
	if (temperatura > temperatura_aviso) {
		ESTOU_QUENTE();
		return false;
	}

	Inc_Consumo_Atual();

	time_t horas_agora = ptr_fabrica->Get_Horas();

	// Se tiver passado 1 hora desde que começou a funcionar, incrementar o número de horas de funcionamento
	if (ultima_hora_registada + 60 > horas_agora) {
		horas_trabalho++;
		ultima_hora_registada = horas_agora;
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
	STOP(false);
	START();
}

bool Motor::STOP(bool warn) {
	if (warn && estado == ESTADO_MOTOR::STOP) {
		cout << "[" << __FUNCTION__ << "] Motor " << id << " já está parado!" << endl;
		return false;
	}

	temperatura_paragem = temperatura;
	estado = ESTADO_MOTOR::STOP;

	return true;
}

void Motor::ESTOU_QUENTE() {
	Inc_Avarias();
	STOP(false);
}

string Motor::Get_Estado_String() {
	switch (Get_Estado()) {
	case ESTADO_MOTOR::STOP:
		return "STOP";
	case ESTADO_MOTOR::START:
		return "START";
	case ESTADO_MOTOR::RUN:
		return "RUN";
	case ESTADO_MOTOR::AVARIADO:
	default:
		return "AVARIADO";
	}
}

void Motor::Print() {
	cout << string(10, '-') << " MOTOR " << string(10, '-') << endl;
	cout << "Id:                      " << Get_Id() << endl;
	cout << "Marca:                   " << Get_Marca() << endl;
	cout << "Consumo por hora:        " << Uteis::Float_To_String_Precisao(Get_Consumo_Hora()) << endl;
	cout << "Temperatura de aviso:    " << Uteis::Float_To_String_Precisao(temperatura_aviso) << endl;
	cout << "Temperatura de paragem:  " << Uteis::Float_To_String_Precisao(temperatura_paragem) << endl;
	cout << "Temperatura atual:       " << Uteis::Float_To_String_Precisao(Get_Temperatura()) << endl;
	cout << "Probabilidade de avaria: " << Uteis::Float_To_String_Precisao(Get_Prob_Avaria()) << endl;
	cout << "Estado:                  " << Get_Estado_String() << endl;
	cout << "Horas de trabalho:       " << Get_Horas_Trabalho() << endl;
	cout << "Consumo atual:           " << Uteis::Float_To_String_Precisao(Get_Consumo_Atual()) << endl;
	cout << "Posição:                 " << Get_Posicao()->To_String() << endl;
	cout << string(27, '-') << endl;
}
