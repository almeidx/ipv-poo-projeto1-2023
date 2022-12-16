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

	this->Relogio = new RelogioFabrica(MULTIPLICADOR_RELOGIO);

	User_Atual = nullptr;
}

Fabrica::Fabrica(User *ut) : Fabrica() {
	User_Atual = ut;
	Users->push_back(ut);
}

Fabrica::~Fabrica() {
	Users->clear();
	delete Users;

	Sensores->clear();
	delete Sensores;

	Motores->clear();
	delete Motores;

	delete Relogio;
}

bool Fabrica::Tem_User_Atual(const string fname) {
	if (!User_Atual) {
		cout << "[" << fname << "] Não há nenhum user atual na fábrica" << endl;
		return false;
	}

	return true;
}

LimitesMotor *Fabrica::Extrair_Limites_Motor(tinyxml2::XMLElement *root) {
	Pair verde = *Uteis::Split_String_Pair(root->FirstChildElement("VERDE")->GetText()),
		 amarelo = *Uteis::Split_String_Pair(root->FirstChildElement("AMARELO")->GetText()),
		 vermelho = *Uteis::Split_String_Pair(root->FirstChildElement("VERMELHO")->GetText());
	int prob_avaria = root->FirstChildElement("PROB_AVARIA")->IntText();

	return new LimitesMotor(verde, amarelo, vermelho, prob_avaria);
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

		list<string> tipos = {"MELETRICO", "MCOMBUSTAO", "MINDUCAO"};

		for (list<string>::iterator it = tipos.begin(); it != tipos.end(); ++it) {
			XMLElement *tipo = definicoes->FirstChildElement(it->c_str());
			if (!tipo) {
				cout << "[" << __FUNCTION__ << "] [" << *it << "] Ficheiro XML mal formado" << endl;
				return false;
			}

			limites_motores[*it] = *Extrair_Limites_Motor(tipo);
		}
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
				LimitesMotor limites = limites_motores.at("MCOMBUSTAO");
				m = new MCombostao(this, id, marca, consumo_hora, limites.Get_Amarelo().Get_X(),
								   limites.Get_Vermelho().Get_X(), limites.Get_Prob_Avaria(), posicao);
			} else if (nome == "MELETRICO") {
				LimitesMotor limites = limites_motores.at("MELETRICO");
				m = new MEletrico(this, id, marca, consumo_hora, limites.Get_Amarelo().Get_X(),
								  limites.Get_Vermelho().Get_X(), limites.Get_Prob_Avaria(), posicao);
			} else if (nome == "MINDUCAO") {
				LimitesMotor limites = limites_motores.at("MINDUCAO");
				m = new MInducao(this, id, marca, consumo_hora, limites.Get_Amarelo().Get_X(),
								 limites.Get_Vermelho().Get_X(), limites.Get_Prob_Avaria(), posicao);
			}

			Add(m);

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
			int prob_avaria = sensor->FirstChildElement("PROB_AVARIA")->IntText();

			Sensor *s;

			if (nome == "SLUZ") {
				s = new SLuz(this, id, marca, valor_aviso, prob_avaria, posicao);
			} else if (nome == "SHUMIDADE") {
				s = new SHumidade(this, id, marca, valor_aviso, prob_avaria, posicao);
			} else if (nome == "SFUMO") {
				s = new SFumo(this, id, marca, valor_aviso, prob_avaria, posicao);
			} else if (nome == "SMISSEL") {
				s = new SMissel(this, id, marca, valor_aviso, prob_avaria, posicao);
			} else if (nome == "SFOGO") {
				s = new SFogo(this, id, marca, valor_aviso, prob_avaria, posicao);
			} else if (nome == "STEMPERATURA") {
				s = new STemperatura(this, id, marca, valor_aviso, prob_avaria, posicao);
			}

			Sensores->push_back(s);

			sensor_node = sensor_node->NextSibling();
		}
	}

	return true;
}

bool Fabrica::Add(User *ut) {
	// Adicionar o user apenas se ainda não estiver na lista de users
	if (User_Atual && User_Atual->Posso_Adicionar()) {
		for (list<User *>::iterator it = Users->begin(); it != Users->end(); ++it) {
			if ((*it)->Get_Id() == ut->Get_Id()) {
				return false;
			}
		}
	}

	Users->push_back(ut);
	User_Atual = ut;

	return true;
}

bool Fabrica::Add(Motor *m) {
	if (!Tem_User_Atual(__FUNCTION__) || !User_Atual->Posso_Adicionar()) {
		return false;
	}

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		if ((*it)->Get_Id() == m->Get_Id()) {
			cout << "[" << __FUNCTION__ << "] Motor com id " << m->Get_Id() << " já existe" << endl;
			return false;
		}
	}

	Motores->push_back(m);

	return true;
}

bool Fabrica::Add(Sensor *s) {
	if (!Tem_User_Atual(__FUNCTION__) || !User_Atual->Posso_Adicionar()) {
		return false;
	}

	for (list<Sensor *>::iterator it = Sensores->begin(); it != Sensores->end(); ++it) {
		if ((*it)->Get_Id() == s->Get_Id()) {
			cout << "[" << __FUNCTION__ << "] Sensor com id " << s->Get_Id() << " já existe" << endl;
			return false;
		}
	}

	Sensores->push_back(s);

	return true;
}

string Fabrica::Get_Estado_Cor(Motor *m) {
	LimitesMotor lim = limites_motores.at(m->Get_Tipo());
	float temp = m->Get_Temperatura();

	if (temp >= lim.Get_Vermelho().Get_X()) {
		return "VERMELHO";
	} else if (temp >= lim.Get_Amarelo().Get_X()) {
		return "AMARELO";
	} else {
		return "VERDE";
	}
}

void Fabrica::Listar(ostream &f) {
	XMLWriter writer(f);

	writer.WriteStartElement("DADOS");

	{
		writer.WriteStartElement("DEFINICOES");

		writer.WriteElementString("NOME_EMPRESA", nome);
		writer.WriteElementString("HORA_INICIO", to_string(hora_inicio));
		writer.WriteElementString("HORA_FECHO", to_string(hora_fecho));
		writer.WriteElementString("VIZINHANCA_AVISO", to_string(vizinhanca_aviso));
		writer.WriteElementString("DIMENSAO_FABRICA", to_string(dimensao_x) + "," + to_string(dimensao_y));

		for (map<string, LimitesMotor>::iterator it = limites_motores.begin(); it != limites_motores.end(); ++it) {
			string nome = it->first;
			LimitesMotor limites = it->second;

			writer.WriteStartElement(nome);

			writer.WriteElementString("VERDE", limites.Get_Verde().To_String());
			writer.WriteElementString("AMARELO", limites.Get_Amarelo().To_String());
			writer.WriteElementString("VERMELHO", limites.Get_Vermelho().To_String());
			writer.WriteElementString("PROB_AVARIA", to_string(limites.Get_Prob_Avaria()));

			writer.WriteEndElement();
		}

		writer.WriteEndElement();
	}

	{
		writer.WriteStartElement("MOTORES");

		for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
			Motor *m = *it;

			writer.WriteStartElement(m->Get_Tipo());

			writer.WriteElementString("ID", to_string(m->Get_Id()));
			writer.WriteElementString("MARCA", m->Get_Marca());
			writer.WriteElementString("CONSUMO_HORA", Uteis::Float_To_String_Precisao(m->Get_Consumo_Hora()));
			writer.WriteElementString("POSICAO", m->Get_Posicao()->To_String());
			writer.WriteElementString("VALOR_TEMP_ATUAL", Uteis::Float_To_String_Precisao(m->Get_Temperatura()));
			writer.WriteElementString("ESTADO_ATUAL", m->Get_Estado_String());
			writer.WriteElementString("ESTADO_COR", Get_Estado_Cor(m));

			writer.WriteEndElement();
		}

		writer.WriteEndElement();
	}

	{
		writer.WriteStartElement("SENSORES");

		for (list<Sensor *>::iterator it = Sensores->begin(); it != Sensores->end(); ++it) {
			Sensor *s = *it;

			writer.WriteStartElement(s->Get_Tipo());

			writer.WriteElementString("ID", to_string(s->Get_Id()));
			writer.WriteElementString("MARCA", s->Get_Marca());
			writer.WriteElementString("VALOR_AVISO", Uteis::Float_To_String_Precisao(s->Get_Valor_Aviso()));
			writer.WriteElementString("POSICAO", s->Get_Posicao()->To_String());
			writer.WriteElementString("PROB_AVARIA", Uteis::Float_To_String_Precisao(s->Get_Prob_Avaria()));
			writer.WriteElementString("VALOR_ATUAL", Uteis::Float_To_String_Precisao(s->Get_Valor_Atual()));

			writer.WriteEndElement();
		}

		writer.WriteEndElement();
	}

	writer.WriteEndElement();
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
			f << "Id:          " << (*it)->Get_Id() << endl;
			f << "Estado:      " << (*it)->Get_Estado_String() << endl;
			f << "Temperatura: " << Uteis::Float_To_String_Precisao((*it)->Get_Temperatura()) << endl;

			f << string(15, '-') << endl;

			motores.push_back(*it);
		}
	}

	if (motores.empty()) {
		f << "[" << __FUNCTION__ << "] Não existem motores do tipo " << Tipo << " na fábrica" << endl;
	}

	return motores;
}

bool Fabrica::Manutencao() {
	if (!Tem_User_Atual(__FUNCTION__) || !User_Atual->Posso_Manutencao() || (Motores->empty() && Sensores->empty())) {
		return false;
	}

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		string tipo = (*it)->Get_Tipo();
		LimitesMotor limites = limites_motores[tipo];
		(*it)->Set_Temperatura(Uteis::Generate_Random_Float(0, limites.Get_Verde().Get_X()));
	}

	for (list<Sensor *>::iterator it = Sensores->begin(); it != Sensores->end(); ++it) {
		(*it)->Set_Valor_Atual(Uteis::Generate_Random_Float(0.0f, (*it)->Get_Valor_Aviso() - 1.0f));
	}

	return true;
}

bool Fabrica::Sort_Marcas(pair<string, int> a, pair<string, int> b) {
	return a.second < b.second;
}

list<string> Fabrica::Ranking_Dos_Fracos() {
	list<string> ranking;

	if (Motores->empty()) {
		return ranking;
	}

	map<string, int> avarias_marca;

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		string marca = (*it)->Get_Marca();
		int curr;

		if (avarias_marca.count(marca) == 0) {
			curr = 0;
		} else {
			curr = avarias_marca[marca];
		}

		avarias_marca[marca] = curr + (*it)->Get_Avarias();
	}

	vector<pair<string, int>> vec{avarias_marca.begin(), avarias_marca.end()};

	sort(vec.begin(), vec.end(), Sort_Marcas);

	for (vector<pair<string, int>>::iterator it = vec.begin(); it != vec.end(); ++it) {
		ranking.push_back(it->first);
	}

	return ranking;
}

bool Fabrica::Sort_Motores(Motor *m1, Motor *m2) {
	return m1->Get_Horas_Trabalho() < m2->Get_Horas_Trabalho();
}

list<Motor *> Fabrica::Ranking_Dos_Mais_Trabalhadores() {
	list<Motor *> trabalhadores;

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		trabalhadores.push_back((*it));
	}

	trabalhadores.sort(Sort_Motores);

	return trabalhadores;
}

void Fabrica::Relatorio(string fich_xml) {
	ofstream f(fich_xml);
	XMLWriter writer(f);

	writer.WriteStartElement("DADOS");

	writer.WriteStartElement("MOTORES");

	for (list<Motor *>::iterator it = Motores->begin(); it != Motores->end(); ++it) {
		Motor *m = *it;
		string tipo = m->Get_Tipo();

		writer.WriteStartElement(tipo);

		writer.WriteElementString("ID", to_string(m->Get_Id()));
		writer.WriteElementString("MARCA", m->Get_Marca());
		writer.WriteElementString("CONSUMO_ATUAL", Uteis::Float_To_String_Precisao(m->Get_Consumo_Atual()));
		writer.WriteElementString("POSICAO", m->Get_Posicao()->To_String());
		writer.WriteElementString("ESTADO_ATUAL", m->Get_Estado_String());

		writer.WriteEndElement();
	}

	writer.WriteEndElement();
	writer.WriteEndElement();
}

int Fabrica::Aviso_Humidade(list<Motor *> &lm) {
	// Guardamos o tamanho inicial da lista pois pode não estar vazia
	size_t tam_inicial = lm.size();

	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "SHUMIDADE" && (*it_sensor)->Em_Alerta()) {
			Ponto *posicao_sensor = (*it_sensor)->Get_Posicao();
			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				Ponto *posicao_motor = (*it_motor)->Get_Posicao();

				if (abs(posicao_sensor->Distancia(*posicao_motor)) <= DISTANCIA_MAXIMA_SENSOR_FUMO) {
					(*it_motor)->STOP();

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
		if ((*it_sensor)->Get_Tipo() == "SFUMO" && (*it_sensor)->Em_Alerta()) {
			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				(*it_motor)->STOP();

				lm.push_back(*it_motor);
			}
		}
	}

	system((PLAYER_VIDEO " " + fich_video).c_str());

	return lm.size() - tam_inicial;
}

int Fabrica::Aviso_Luz(string fich_video) {
	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "SLUZ" && (*it_sensor)->Em_Alerta()) {
			system((PLAYER_VIDEO " " + fich_video).c_str());

			return 1;
		}
	}

	return 0;
}

void Fabrica::Aviso_Missel(string fvideo, string festado) {
	for (list<Sensor *>::iterator it_sensor = Sensores->begin(); it_sensor != Sensores->end(); ++it_sensor) {
		if ((*it_sensor)->Get_Tipo() == "SMISSEL" && (*it_sensor)->Em_Alerta()) {
			ofstream f(festado);

			Listar(f);

			for (list<Motor *>::iterator it_motor = Motores->begin(); it_motor != Motores->end(); ++it_motor) {
				Desligar((*it_motor)->Get_Id());
			}
		}
	}

	system((PLAYER_VIDEO " " + fvideo).c_str());
}
