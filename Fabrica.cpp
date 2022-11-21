#include "Fabrica.h"

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

Fabrica::~Fabrica() {
	delete Users;
	delete Sensores;
	delete Motores;

	cout << "Destruindo Fabrica" << endl;
}

bool Fabrica::Tem_User_Atual(const string fname) {
	if (!User_Atual) {
		cout << "[" << fname << "] Não há nenhum user atual na fábrica" << endl;
		return false;
	}

	return true;
}

MOTOR_LIMITS *Fabrica::Extrair_Limites_Motor(tinyxml2::XMLElement *root, MOTOR_LIMITS *lim) {
	lim->verde = Uteis::Split_String_Pair(root->FirstChildElement("VERDE")->GetText());
	lim->amarelo = Uteis::Split_String_Pair(root->FirstChildElement("AMARELO")->GetText());
	lim->vermelho = Uteis::Split_String_Pair(root->FirstChildElement("VERMELHO")->GetText());
	lim->probabilidade_avaria = root->FirstChildElement("PROB_AVARIA")->IntText();

	return lim;
}

bool Fabrica::Load(const string &ficheiro) {
	using namespace tinyxml2;

	XMLDocument doc;

	doc.LoadFile(ficheiro.c_str());
	if (doc.Error()) {
		cout << "[" << __FUNCTION__ << "] Erro ao abrir ficheiro XML" << endl;
		return false;
	}

	XMLElement *root = doc.FirstChildElement("DADOS");
	if (!root) {
		cout << "[" << __FUNCTION__ << "] [DADOS] Ficheiro XML mal formado" << endl;
		return false;
	}

	{
		XMLElement *definicoes = root->FirstChildElement("DEFINICOES");
		if (!definicoes) {
			cout << "[" << __FUNCTION__ << "] [DEFINICOES] Ficheiro XML mal formado" << endl;
			return false;
		}

		this->nome = definicoes->FirstChildElement("NOME_EMPRESA")->GetText();
		this->hora_inicio = definicoes->FirstChildElement("HORA_INICIO")->IntText();
		this->hora_fecho = definicoes->FirstChildElement("HORA_FECHO")->IntText();
		this->vizinhanca_aviso = definicoes->FirstChildElement("VIZINHANCA_AVISO")->IntText();

		string dimensoes = definicoes->FirstChildElement("DIMENSAO_FABRICA")->GetText();
		Pair *dims = Uteis::Split_String_Pair(dimensoes);
		dimensao_x = dims->Get_X();
		dimensao_y = dims->Get_Y();

		MOTOR_LIMITS lim1, lim2, lim3;

		limites_motores.insert({"MELETRICO", Extrair_Limites_Motor(definicoes->FirstChildElement("MELETRICO"), &lim1)});
		limites_motores.insert(
			{"MCOMBUSTAO", Extrair_Limites_Motor(definicoes->FirstChildElement("MCOMBUSTAO"), &lim2)});
		limites_motores.insert({"MINDUCAO", Extrair_Limites_Motor(definicoes->FirstChildElement("MINDUCAO"), &lim3)});
	}

	{
		XMLElement *motores = root->FirstChildElement("MOTORES");
		if (!motores) {
			cout << "[" << __FUNCTION__ << "] [MOTORES] Ficheiro XML mal formado" << endl;
			return false;
		}

		XMLNode *motor_node = motores->FirstChild();
		while (motor_node) {
			XMLElement *motor = motor_node->ToElement();

			string nome = motor->Name();

			int id = motor->FirstChildElement("ID")->IntText();
			string marca = motor->FirstChildElement("MARCA")->GetText();
			int consumo_hora = motor->FirstChildElement("CONSUMO_HORA")->IntText();
			Ponto *posicao = Uteis::Split_String_Coordenadas(motor->FirstChildElement("POSICAO")->GetText());
			Motor *m;

			if (nome == "MCOMBUSTAO") {
				MOTOR_LIMITS *limites = limites_motores.at("MCOMBUSTAO");
				m = new MCombostao(id, marca, consumo_hora, limites->amarelo->Get_X(), limites->vermelho->Get_X(),
								   limites->probabilidade_avaria, posicao);
			} else if (nome == "MELETRICO") {
				MOTOR_LIMITS *limites = limites_motores.at("MELETRICO");
				m = new MEletrico(id, marca, consumo_hora, limites->amarelo->Get_X(), limites->vermelho->Get_X(),
								  limites->probabilidade_avaria, posicao);
			} else if (nome == "MINDUCAO") {
				MOTOR_LIMITS *limites = limites_motores.at("MINDUCAO");
				m = new MInducao(id, marca, consumo_hora, limites->amarelo->Get_X(), limites->vermelho->Get_X(),
								 limites->probabilidade_avaria, posicao);
			}

			Motores->push_back(m);

			motor_node = motor_node->NextSibling();
		}
	}

	{
		XMLElement *sensores = root->FirstChildElement("SENSORES");
		if (!sensores) {
			cout << "[" << __FUNCTION__ << "] [SENSORES] Ficheiro XML mal formado" << endl;
			return false;
		}

		XMLNode *sensor_node = sensores->FirstChild();
		while (sensor_node) {
			XMLElement *sensor = sensor_node->ToElement();

			string nome = sensor->Name();

			int id = sensor->FirstChildElement("ID")->IntText();
			string marca = sensor->FirstChildElement("MARCA")->GetText();
			int valor_aviso = sensor->FirstChildElement("VALOR_AVISO")->IntText();
			Ponto *posicao = Uteis::Split_String_Coordenadas(sensor->FirstChildElement("POSICAO")->GetText());
			int probabilidade_avaria = sensor->FirstChildElement("PROB_AVARIA")->IntText();

			Sensor *s;

			if (nome == "SLUZ") {
				s = new SLuz(id, marca, valor_aviso, probabilidade_avaria, posicao);
			} else if (nome == "SHUMIDADE") {
				s = new SHumidade(id, marca, valor_aviso, probabilidade_avaria, posicao);
			} else if (nome == "SFUMO") {
				s = new SFumo(id, marca, valor_aviso, probabilidade_avaria, posicao);
			} else if (nome == "SMISSIL") {
				s = new SMissil(id, marca, valor_aviso, probabilidade_avaria, posicao);
			} else if (nome == "SFOGO") {
				s = new SFogo(id, marca, valor_aviso, probabilidade_avaria, posicao);
			} else if (nome == "STEMPERATURA") {
				s = new STemperatura(id, marca, valor_aviso, probabilidade_avaria, posicao);
			}

			Sensores->push_back(s);

			sensor_node = sensor_node->NextSibling();
		}
	}

	return true;
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

void Fabrica::Listar(ostream &f) {
	//
	f << "Nome da fábrica: " << nome << endl;
}

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

	// Caso não seja encontrado um motor, assumir que está avariado
	return ESTADO_MOTOR::AVARIADO;
}

list<Motor *> Fabrica::Listar_Tipo(string Tipo, ostream &f) {
	list<Motor *> motores;

	if (Motores->empty()) {
		f << "[" << __FUNCTION__ << "] Não existem motores na fábrica" << endl;
		return motores;
	}

	f << "Motores do tipo " << Tipo << ":" << endl;

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		if ((*it)->Get_Tipo() == Tipo) {
			f << "ID: " << (*it)->Get_Id() << endl;
			f << "Estado: " << (*it)->Get_Estado() << endl;
			f << "Temperatura: " << (*it)->Get_Temperatura() << endl;

			f << string(10, '-') << endl;

			motores.push_back(*it);
		}
	}

	if (motores.empty()) {
		f << "[" << __FUNCTION__ << "] Não existem motores do tipo " << Tipo << " na fábrica" << endl;
	}

	return motores;
}

bool Fabrica::Manutencao() {
	if (!Tem_User_Atual(__FUNCTION__) || !User_Atual->Posso_Manutencao() || Motores->empty()) {
		return false;
	}

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		(*it)->Set_Temperatura(TEMPERATURA_MANUTENCAO);
		(*it)->Set_Estado(ESTADO_MOTOR::RUN);
		(*it)->Inc_Avarias();
	}

	return true;
}

bool myCmp(Motor *motor1, Motor *motor2) {
	/* float s1_ = atof(Uteis::Split_String(s1, '-').front().c_str());
	float s2_ = atof(Uteis::Split_String(s2, '-').front().c_str()); */

	return motor1->Get_Avarias() < motor2->Get_Avarias();
}

list<string> Fabrica::Ranking_Dos_Fracos() {
	list<Motor *> ranking;

	map<string, int> avarias_marca;

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		string marca = (*it)->Get_Marca();
		avarias_marca[marca] = (avarias_marca[marca] || 0) + (*it)->Get_Avarias();
	}

	sort(ranking.begin(), ranking.end(), myCmp);
}

list<Motor *> Fabrica::Ranking_Dos_Mais_Trabalhadores() {
	/* list<Motor *> mylist;
	sort(mylist.begin(), mylist.end(), myCmp);

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {

		string av =	to_string((*it)->Get_Avarias());
		mylist.push_back( (*it)->Get_Marca() + " - " + av);
	}

	return mylist; */
}

void Fabrica::Relatorio(string fich_xml) {}

int Fabrica::Aviso_Humidade(list<Motor *> &lm) {
	// Guardamos o tamanho inicial da lista pois pode não estar vazia
	size_t tam_inicial = lm.size();

	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "Humidade" && (*it_sensor)->Em_Alerta()) {
			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				Ponto *posicao_sensor = (*it_sensor)->Get_Posicao(), *posicao_motor = (*it_motor)->Get_Posicao();

				if (posicao_sensor->Distancia(*posicao_motor) <= DISTANCIA_MAXIMA_SENSOR_FUMO) {
					lm.push_back(*it_motor);
				}
			}
		}
	}

	return lm.size() - tam_inicial;
}

int Fabrica::Aviso_Fumo(list<Motor *> &lm, string fich_video) {
	// Guardamos o tamanho inicial da lista pois pode não estar vazia
	size_t tam_inicial = lm.size();

	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "Fumo" && (*it_sensor)->Em_Alerta()) {
			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				(*it_motor)->STOP();

				lm.push_back(*it_motor);
			}
		}
	}

	system(fich_video.c_str());

	return lm.size() - tam_inicial;
}

int Fabrica::Aviso_Luz(string fich_video) {
	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "Luz" && (*it_sensor)->Em_Alerta()) {
			system(fich_video.c_str());

			return 1;
		}
	}

	return 0;
}

void Fabrica::Aviso_Missel(string fvideo, string festado) {
	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "Missel" && (*it_sensor)->Em_Alerta()) {
			ofstream f(festado);

			Listar(f);

			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				Desligar((*it_motor)->Get_Id());
			}
		}
	}

	system(fvideo.c_str());
}
