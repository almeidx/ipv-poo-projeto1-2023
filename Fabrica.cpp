#include "Fabrica.h"

typedef struct MotorLimits {
	Pair verde, amarelo, vermelho;
	int probabilidade_avaria;
} MotorLimits;

Fabrica::Fabrica() {
	nome = "???";
	hora_inicio = -1;
	hora_fecho = -1;
	vizinhanca_aviso = -1;
	dimensao_x = -1;
	dimensao_y = -1;

	this->Users = new list<User *>;
	this->Sensores = new list<Sensor *>;
	this->Motores = new list<Motor *>;

	User_Atual = nullptr;
}

Fabrica::Fabrica(User *ut) : Fabrica() {
	User_Atual = ut;
	Users->push_back(ut);
}

Fabrica::~Fabrica() { cout << "Destruindo Fabrica" << endl; }

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

	{
		XMLElement *definicoes = root->FirstChildElement("DEFINICOES");
		if (!definicoes) {
			cout << "Ficheiro XML mal formado" << endl;
			return false;
		}

		this->nome = definicoes->FirstChildElement("NOME_EMPRESA")->GetText();
		this->hora_inicio = definicoes->FirstChildElement("HORA_INICIO")->IntText();
		this->hora_fecho = definicoes->FirstChildElement("HORA_FECHO")->IntText();
		this->vizinhanca_aviso = definicoes->FirstChildElement("VIZINHANCA_AVISO")->IntText();

		string dimensoes = root->FirstChildElement("DIMENSAO_FABRICA")->GetText();
		int *dim = Uteis::Split_String_Coordenadas(dimensoes);
		dimensao_x = dim[0];
		dimensao_y = dim[1];
	}

	{
		XMLElement *motores = root->FirstChildElement("MOTORES");
		if (!motores) {
			cout << "Ficheiro XML mal formado" << endl;
			return false;
		}

		XMLNode *motor_node = motores->FirstChild();
		while (motor_node) {
			XMLElement *motor = motor_node->ToElement();

			string nome = motor->Name();

			int id = motor->FirstChildElement("ID")->IntText();
			string marca = motor->FirstChildElement("MARCA")->GetText();
			int consumo_hora = motor->FirstChildElement("CONSUMO_HORA")->IntText();

			int *dims = Uteis::Split_String_Coordenadas(motor->FirstChildElement("DIMENSOES")->GetText());
			Motor *m;

			if (nome == "MCOMBUSTAO") {
				m = new MCombostao(id, marca, consumo_hora, dims[0], dims[1]);
			} else if (nome == "MELETRICO") {
				m = new MEletrico(id, marca, consumo_hora, dims[0], dims[1]);
			} /*else if (nome == "MINDUCAO") {
				m = new MInducao(id, marca, consumo_hora, dims[0], dims[1]);
			}*/

			Add(m);
		}
	}
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
