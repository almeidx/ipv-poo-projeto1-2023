#include "Fabrica.h"

Fabrica::Fabrica() {
	this->Users = new list<User *>;
	this->Sensores = new list<Sensor *>;
	this->Motores = new list<Motor *>;
}

Fabrica::~Fabrica() { cout << "Destruindo Fabrica" << endl; }

Fabrica::Fabrica(User *ut) {
	User_Atual = ut;
	Users->push_back(ut);
}

bool Fabrica::Tem_User_Atual(const string fname) {
	if (!User_Atual) {
		cout << "[" << fname << "] Não há nenhum user atual na fábrica" << endl;
		return false;
	}

	return true;
}

bool Fabrica::Load(const string &ficheiro) {
	using namespace tinyxml2;

	XMLDocument doc;

	doc.LoadFile(ficheiro.c_str());
	if (doc.Error()) {
		cout << "Erro ao abrir ficheiro XML" << endl;
		return false;
	}

	XMLElement *root = doc.FirstChildElement("DADOS");
	if (!root) {
		cout << "Ficheiro XML mal formado" << endl;
		return false;
	}

	XMLElement *definicoes = root->FirstChildElement("DEFINICOES");
	if (!definicoes) {
		cout << "Ficheiro XML mal formado" << endl;
		return false;
	}

	this->nome = definicoes->FirstChildElement("NOME_EMPRESA")->GetText();
	this->hora_inicio = definicoes->FirstChildElement("HORA_INICIO")->IntText();
}

bool Fabrica::Add(User *ut) {
	if (!Tem_User_Atual(__FUNCTION__)) {
		return false;
	}

	// Adicionar o user se não estiver na lista
	if (User_Atual->Posso_Adicionar() && find(Users->begin(), Users->end(), ut) == Users->end()) {
		Users->push_back(ut);
		return true;
	}

	return false;
}

bool Fabrica::Add(Motor *m) {
	if (!Tem_User_Atual(__FUNCTION__)) {
		return false;
	}

	// Adicionar o motor se não estiver na lista
	if (User_Atual->Posso_Adicionar() && find(Motores->begin(), Motores->end(), m) == Motores->end()) {
		Motores->push_back(m);
		return true;
	}

	return false;
}

void Fabrica::Listar(ostream &f) {}

void Fabrica::Desligar(int id_motor) {
	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		if ((*it)->Get_Id() == id_motor) {
			(*it)->STOP();
			return;
		}
	}
}

ESTADO_MOTOR Fabrica::Get_Estado(int id_motor) {
	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		if ((*it)->Get_Id() == id_motor) {
			return (*it)->Get_Estado();
		}
	}

	return ESTADO_MOTOR::AVARIADO;
}

list<Motor *> Fabrica::Listar_Tipo(string Tipo, ostream &f) {}

bool Fabrica::Manutencao() {
	if (!Tem_User_Atual(__FUNCTION__) || !User_Atual->Posso_Manutencao() || Motores->empty()) {
		return false;
	}

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
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
	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		(*it)->STOP();
	}

	system(fich_video.c_str());
}

int Fabrica::Aviso_Luz(string fich_video) {}

void Fabrica::Aviso_Missel(string fvideo, string festado) {}
