#include "Fabrica.h"

Fabrica::Fabrica() {}

Fabrica::~Fabrica() {}

Fabrica::Fabrica(User *ut) {
	Ut_Atual = ut;
	Users.push_back(ut);
}

bool Fabrica::Load(const string &ficheiro) {}

bool Fabrica::Add(User *ut) {
	// TODO: Ver se tem permissão

	// Adicionar o user se não estiver na lista
	if (find(Users.begin(), Users.end(), ut) == Users.end()) {
		Users.push_back(ut);
		return true;
	}

	return false;
}

bool Fabrica::Add(Motor *m) {
	// TODO: Ver se tem permissão

	// Adicionar o motor se não estiver na lista
	if (find(Motores.begin(), Motores.end(), m) == Motores.end()) {
		Motores.push_back(m);
		return true;
	}

	return false;
}

void Fabrica::Listar(ostream &f) {}

void Fabrica::Desligar(int id_motor) {
	for (list<Motor *>::iterator it = Motores.begin(); it != Motores.end(); ++it) {
		if ((*it)->Get_Id() == id_motor) {
			(*it)->STOP();
			return;
		}
	}
}

ESTADO_MOTOR Fabrica::Get_Estado(int id_motor) {
	for (list<Motor *>::iterator it = Motores.begin(); it != Motores.end(); ++it) {
		if ((*it)->Get_Id() == id_motor) {
			return (*it)->Get_Estado();
		}
	}

	return ESTADO_MOTOR::AVARIADO;
}

list<Motor *> Fabrica::Listar_Tipo(string Tipo, ostream &f) {}

bool Fabrica::Manutencao() {
	if (Motores.empty()) {
		return false;
	}

	for (list<Motor *>::iterator it = Motores.begin(); it != Motores.end(); ++it) {
		(*it)->Set_Temperatura(TEMPERATURA_MANUTENCAO);
		(*it)->Set_Estado(ESTADO_MOTOR::RUN);
	}

	return true;
}

list<string> Fabrica::Ranking_Dos_Fracos() {}

list<Motor *> Fabrica::Ranking_Dos_Mais_Trabalhadores() {}

void Fabrica::Relatorio(string fich_xml) {}

int Fabrica::Aviso_Humidade(list<Motor *> &lm) {}

int Fabrica::Aviso_Fumo(list<Motor *> &lm, string fich_video) {
	for (list<Motor *>::iterator it = Motores.begin(); it != Motores.end(); ++it) {
		(*it)->STOP();
	}

	system(fich_video.c_str());
}

int Fabrica::Aviso_Luz(string fich_video) {


    for (list<Motor *>::iterator it = Motores.begin(); it != Motores.end(); ++it){
        		
	}
    }

void Fabrica::Aviso_Missel(string fvideo, string festado) {}
