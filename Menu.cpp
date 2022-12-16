#include "Menu.h"

Menu::Menu(Fabrica *f) {
	ptr_fabrica = f;
}

void Menu::iniciar() {
	int option;

	do {
		Uteis::Limpar_Terminal();

		cout << "  ____                             _           _       _       " << endl;
		cout << " |  _ \\                           (_)         | |     | |     " << endl;
		cout << " | |_) | ___ _ __ ___ ________   ___ _ __   __| | ___ | |      " << endl;
		cout << " |  _ < / _ \\ '_ ` _ \\______\\ \\ / / | '_ \\ / _` |/ _ \\| |" << endl;
		cout << " | |_) |  __/ | | | | |      \\ V /| | | | | (_| | (_) |_|     " << endl;
		cout << " |____/ \\___|_| |_| |_|       \\_/ |_|_| |_|\\__,_|\\___/(_)  " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha uma opção                     ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Fábrica                           │" << endl;
		cout << "│ 2 · Utilizadores                      │" << endl;
		cout << "│ 3 · Motores                           │" << endl;
		cout << "│ 4 · Sensores                          │" << endl;
		cout << "│ 5 · Sair                              │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> option;
	} while (option < 1 || option > 5);

	switch (option) {
	case 1:
		fabrica();
		break;

	case 2:
		utilizadores();
		break;

	case 3:
		motores();
		break;

	case 4:
		sensores();
		break;

	case 5:
		sair();
		break;
	}
}

void Menu::fabrica() {
	int option;

	do {
		Uteis::Limpar_Terminal();

		cout << "  ______    _          _              " << endl;
		cout << " |  ____|  | |        (_)             " << endl;
		cout << " | |__ __ _| |__  _ __ _  ___ __ _    " << endl;
		cout << " |  __/ _` | '_ \\| '__| |/ __/ _` |  " << endl;
		cout << " | | | (_| | |_) | |  | | (_| (_| |   " << endl;
		cout << " |_|  \\__,_|_.__/|_|  |_|\\___\\__,_|" << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha uma opção                     ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Carregar um ficheiro              │" << endl;
		cout << "│ 2 · Listar estado atual               │" << endl;
		cout << "│ 3 · Listar estado de um tipo de motor │" << endl;
		cout << "│ 4 · Iniciar manutenção                │" << endl;
		cout << "│ 5 · Ranking dos fracos                │" << endl;
		cout << "│ 6 · Ranking does mais trabalhadores   │" << endl;
		cout << "│ 7 · Relatório                         │" << endl;
		cout << "│ 8 · Tudo a trabalhar                  │" << endl;
		cout << "│ 9 · Voltar                            │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> option;
	} while (option < 1 || option > 9);

	Uteis::Limpar_Terminal();

	switch (option) {
	case 1: {
		if (!ptr_fabrica->Get_User_Atual()) {
			cout << "Não tem permissões para carregar um ficheiro! Tente adicionar um Administrador através do menu de "
					"Utilizadores"
				 << endl;

			Uteis::Pausar();

			break;
		}

		string filename = ler_nome_fich();

		if (ptr_fabrica->Load(filename)) {
			cout << "Ficheiro carregado com sucesso!" << endl;
		} else {
			cout << "Erro ao carregar o ficheiro!" << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 2: {
		ptr_fabrica->Listar();

		Uteis::Pausar();

		break;
	}

	case 3: {
		fabrica_motor();
		break;
	}

	case 4: {
		if (ptr_fabrica->Manutencao()) {
			cout << "Manutenção iniciada com sucesso!" << endl;
		} else {
			cout << "Erro ao iniciar a manutenção!" << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 5: {
		ptr_fabrica->Ranking_Dos_Fracos();

		Uteis::Pausar();

		break;
	}

	case 6: {
		ptr_fabrica->Ranking_Dos_Mais_Trabalhadores();

		Uteis::Pausar();

		break;
	}

	case 7: {
		string filename = ler_nome_fich();
		ptr_fabrica->Relatorio(filename);

		Uteis::Pausar();

		break;
	}

	case 8: {
		list<Motor *> *motores = ptr_fabrica->Get_Motores();
		list<Sensor *> *sensores = ptr_fabrica->Get_Sensores();

		if (motores->empty() && sensores->empty()) {
			cout << "Não existe nada para colocar a trabalhar!" << endl;
		} else {
			int segundos;

			cout << "Durante quanto tempo pretende que a fábrica esteja a trabalhar? (em segundos)" << endl;
			cin >> segundos;

			Uteis::Limpar_Terminal();

			cout << "A colocar os motores e os sensores a trabalhar durante " << segundos << " segundos..." << endl;

			while (segundos--) {
				time_t tempo = ptr_fabrica->Get_Time();
				cout << "Motores e sensores estão a trabalhar no tempo simulado: " << asctime(localtime(&tempo));

				for (list<Motor *>::iterator it = motores->begin(); it != motores->end(); it++) {
					(*it)->RUN();
				}

				for (list<Sensor *>::iterator it = sensores->begin(); it != sensores->end(); it++) {
					(*it)->Ler_Valor();
				}

				RelogioFabrica::Wait(1);
			}

			cout << "Trabalho terminado!" << endl;

			for (list<Motor *>::iterator it = motores->begin(); it != motores->end(); it++) {
				(*it)->STOP(false);
			}
		}

		Uteis::Pausar();

		break;
	}

	case 9: {
		break;
	}
	}
}

void Menu::fabrica_motor() {
	int tipo;

	do {
		Uteis::Limpar_Terminal();

		cout << " __  __       _                " << endl;
		cout << "|  \\/  |     | |              " << endl;
		cout << "| \\  / | ___ | |_ ___  _ __   " << endl;
		cout << "| |\\/| |/ _ \\| __/ _ \\| '__|" << endl;
		cout << "| |  | | (_) | || (_) | |      " << endl;
		cout << "|_|  |_|\\___/ \\__\\___/|_|   " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha o tipo de motor               ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Motor de Combustão                │" << endl;
		cout << "│ 2 · Motor Elétrico                    │" << endl;
		cout << "│ 3 · Motor de Indução                  │" << endl;
		cout << "│ 4 · Cancelar                          │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> tipo;
	} while (tipo < 1 || tipo > 4);

	switch (tipo) {
	case 1:
		ptr_fabrica->Listar_Tipo("MCOMBUSTAO");
		break;

	case 2:
		ptr_fabrica->Listar_Tipo("MELETRICO");
		break;

	case 3:
		ptr_fabrica->Listar_Tipo("MINDUCAO");
		break;

	case 4:
		return;
	}

	Uteis::Pausar();
}

void Menu::utilizadores() {
	int option;

	do {
		Uteis::Limpar_Terminal();

		cout << " _    _                       " << endl;
		cout << "| |  | |                      " << endl;
		cout << "| |  | |___  ___ _ __ ___     " << endl;
		cout << "| |  | / __|/ _ \\ '__/ __|   " << endl;
		cout << "| |__| \\__ \\  __/ |  \\__ \\" << endl;
		cout << " \\____/|___/\\___|_|  |___/  " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha uma opção                     ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Criar utilizador                  │" << endl;
		cout << "│ 2 · Informações do utilizador atual   │" << endl;
		cout << "│ 3 · Listar utilizadores               │" << endl;
		cout << "│ 4 · Apagar utilizador                 │" << endl;
		cout << "│ 5 · Voltar                            │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> option;
	} while (option < 1 || option > 5);

	Uteis::Limpar_Terminal();

	switch (option) {
	case 1: {
		string id, nome;

		cout << "Id: ";
		cin >> id;

		cout << "Nome: ";
		cin >> nome;

		User *u = utilizadores_criar(id, nome);
		if (u != nullptr) {
			if (ptr_fabrica->Add(u)) {
				cout << "Utilizador criado com sucesso!" << endl;
			} else {
				cout << "Erro ao criar utilizador!" << endl;
			}
		} else {
			cout << "Motor não criado." << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 2: {
		User *ut = ptr_fabrica->Get_User_Atual();

		if (ut != nullptr) {
			ut->Print();
		} else {
			cout << "Não há utilizador atual!" << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 3: {
		list<User *> *users = ptr_fabrica->Get_Users();

		if (users->empty()) {
			cout << "Não há utilizadores!" << endl;
		} else {
			for (list<User *>::iterator it = users->begin(); it != users->end(); it++) {
				(*it)->Print();
			}
		}

		Uteis::Pausar();

		break;
	}

	case 4: {
		list<User *> *users = ptr_fabrica->Get_Users();

		if (users->empty()) {
			cout << "Não há utilizadores!" << endl;
		} else {
			string id;
			bool erased = false;

			cout << "Introduza o id do utilizador a apagar: ";
			cin >> id;

			for (list<User *>::iterator it = users->begin(); it != users->end(); it++) {
				if ((*it)->Get_Id() == id) {
					users->erase(it);
					erased = true;
					break;
				}
			}

			if (erased) {
				cout << "Utilizador apagado com sucesso!" << endl;
			} else {
				cout << "Utilizador não encontrado!" << endl;
			}
		}

		Uteis::Pausar();

		break;
	}

	case 5: {
		break;
	}
	}
}

User *Menu::utilizadores_criar(string id, string nome) {
	int tipo;

	do {
		Uteis::Limpar_Terminal();

		cout << " _______ _               " << endl;
		cout << "|__   __(_)              " << endl;
		cout << "   | |   _ _ __   ___    " << endl;
		cout << "   | |  | | '_ \\ / _ \\ " << endl;
		cout << "   | |  | | |_) | (_) |  " << endl;
		cout << "   |_|  |_| .__/ \\___/  " << endl;
		cout << "          | |            " << endl;
		cout << "          |_|            " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha o tipo de utilizador          ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Normal                            │" << endl;
		cout << "│ 2 · Visitante                         │" << endl;
		cout << "│ 3 · Administrador                     │" << endl;
		cout << "│ 4 · Cancelar                          │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> tipo;
	} while (tipo < 1 || tipo > 4);

	switch (tipo) {
	case 1:
		return new Normal(id, nome);

	case 2:
		return new Visitante(id, nome);

	case 3:
		return new Admin(id, nome);

	case 4:
	default:
		return nullptr;
	}
}

void Menu::motores() {
	int option;

	do {
		Uteis::Limpar_Terminal();

		cout << " __  __       _                          " << endl;
		cout << "|  \\/  |     | |                        " << endl;
		cout << "| \\  / | ___ | |_ ___  _ __ ___  ___    " << endl;
		cout << "| |\\/| |/ _ \\| __/ _ \\| '__/ _ \\/ __|" << endl;
		cout << "| |  | | (_) | || (_) | | |  __/\\__ \\  " << endl;
		cout << "|_|  |_|\\___/ \\__\\___/|_|  \\___||___/" << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha uma opção                     ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Criar motor                       │" << endl;
		cout << "│ 2 · Listar motores                    │" << endl;
		cout << "│ 3 · Apagar motor                      │" << endl;
		cout << "│ 4 · Voltar                            │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> option;
	} while (option < 1 || option > 4);

	Uteis::Limpar_Terminal();

	switch (option) {
	case 1: {
		int id;
		string marca;
		float consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria;

		cout << "Id: ";
		cin >> id;

		cout << "Marca: ";
		cin >> marca;

		cout << "Consumo por hora: ";
		cin >> consumo_hora;

		cout << "Temperatura de aviso: ";
		cin >> temperatura_aviso;

		cout << "Temperatura de paragem: ";
		cin >> temperatura_paragem;

		cout << "Probabilidade de avaria: ";
		cin >> prob_avaria;

		Ponto *p = Uteis::Ler_Ponto();

		Motor *m = motores_criar(id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria, p);

		if (m != nullptr) {
			if (ptr_fabrica->Add(m)) {
				cout << "Motor criado com sucesso!" << endl;
			} else {
				cout << "Erro ao criar motor!" << endl;
			}
		} else {
			cout << "Motor não criado." << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 2: {
		list<Motor *> *motores = ptr_fabrica->Get_Motores();

		if (motores->empty()) {
			cout << "Não existem motores!" << endl;
		} else {
			for (list<Motor *>::iterator it = motores->begin(); it != motores->end(); it++) {
				(*it)->Print();
			}
		}

		Uteis::Pausar();

		break;
	}

	case 3: {
		list<Motor *> *motores = ptr_fabrica->Get_Motores();

		if (motores->empty()) {
			cout << "Não existem motores!" << endl;
		} else {
			int id;
			bool erased = false;

			cout << "Introduza o id do motor a apagar: ";
			cin >> id;

			for (list<Motor *>::iterator it = motores->begin(); it != motores->end(); it++) {
				if ((*it)->Get_Id() == id) {
					motores->erase(it);
					erased = true;
					break;
				}
			}

			if (erased) {
				cout << "Motor apagado com sucesso!" << endl;
			} else {
				cout << "Motor não encontrado!" << endl;
			}
		}

		Uteis::Pausar();

		break;
	}

	case 4: {
		break;
	}
	}
}

Motor *Menu::motores_criar(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
						   float prob_avaria, Ponto *posicao) {
	int tipo;

	do {
		Uteis::Limpar_Terminal();

		cout << " _______ _               " << endl;
		cout << "|__   __(_)              " << endl;
		cout << "   | |   _ _ __   ___    " << endl;
		cout << "   | |  | | '_ \\ / _ \\ " << endl;
		cout << "   | |  | | |_) | (_) |  " << endl;
		cout << "   |_|  |_| .__/ \\___/  " << endl;
		cout << "          | |            " << endl;
		cout << "          |_|            " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha o tipo de motor               ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Motor de combustão                │" << endl;
		cout << "│ 2 · Motor elétrico                    │" << endl;
		cout << "│ 3 · Motor a indução                   │" << endl;
		cout << "│ 4 · Cancelar                          │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> tipo;
	} while (tipo < 1 || tipo > 4);

	switch (tipo) {
	case 1:
		return new MCombostao(ptr_fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria,
							  posicao);

	case 2:
		return new MEletrico(ptr_fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria,
							 posicao);

	case 3:
		return new MInducao(ptr_fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria,
							posicao);

	case 4:
	default:
		return nullptr;
	}
}

void Menu::sensores() {
	int option;

	do {
		Uteis::Limpar_Terminal();

		cout << "  _____                                          " << endl;
		cout << " / ____|                                         " << endl;
		cout << "| (___   ___ _ __  ___  ___  _ __ ___  ___       " << endl;
		cout << " \\___ \\ / _ \\ '_ \\/ __|/ _ \\| '__/ _ \\/ __|" << endl;
		cout << " ____) |  __/ | | \\__ \\ (_) | | |  __/\\__ \\  " << endl;
		cout << "|_____/ \\___|_| |_|___/\\___/|_|  \\___||___/   " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha uma opção                     ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Criar sensor                      │" << endl;
		cout << "│ 2 · Listar sensores                   │" << endl;
		cout << "│ 3 · Apagar sensor                     │" << endl;
		cout << "│ 4 · Voltar                            │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> option;
	} while (option < 1 || option > 4);

	Uteis::Limpar_Terminal();

	switch (option) {
	case 1: {
		int id;
		string marca;
		float valor_aviso, prob_avaria;

		cout << "Id: ";
		cin >> id;

		cout << "Marca: ";
		cin >> marca;

		cout << "Valor de aviso: ";
		cin >> valor_aviso;

		cout << "Probabilidade de avaria: ";
		cin >> prob_avaria;

		Ponto *p = Uteis::Ler_Ponto();

		Sensor *s = sensores_criar(id, marca, valor_aviso, prob_avaria, p);

		if (s != nullptr) {
			if (ptr_fabrica->Add(s)) {
				cout << "Sensor criado com sucesso!" << endl;
			} else {
				cout << "Erro ao criar sensor!" << endl;
			}
		} else {
			cout << "Sensor não criado." << endl;
		}

		Uteis::Pausar();

		break;
	}

	case 2: {
		list<Sensor *> *sensores = ptr_fabrica->Get_Sensores();

		if (sensores->empty()) {
			cout << "Não existem sensores!" << endl;
		} else {
			for (list<Sensor *>::iterator it = sensores->begin(); it != sensores->end(); it++) {
				(*it)->Print();
			}
		}

		Uteis::Pausar();

		break;
	}

	case 3: {
		list<Sensor *> *sensores = ptr_fabrica->Get_Sensores();

		if (sensores->empty()) {
			cout << "Não existem sensores!" << endl;
		} else {
			int id;
			bool erased = false;

			cout << "Introduza o id do sensor a apagar: ";
			cin >> id;

			for (list<Sensor *>::iterator it = sensores->begin(); it != sensores->end(); it++) {
				if ((*it)->Get_Id() == id) {
					sensores->erase(it);
					erased = true;
					break;
				}
			}

			if (erased) {
				cout << "Sensor apagado com sucesso!" << endl;
			} else {
				cout << "Sensor não encontrado!" << endl;
			}
		}

		Uteis::Pausar();

		break;
	}

	case 4: {
		break;
	}
	}
}

Sensor *Menu::sensores_criar(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao) {
	int tipo;

	do {
		Uteis::Limpar_Terminal();

		cout << " _______ _               " << endl;
		cout << "|__   __(_)              " << endl;
		cout << "   | |   _ _ __   ___    " << endl;
		cout << "   | |  | | '_ \\ / _ \\ " << endl;
		cout << "   | |  | | |_) | (_) |  " << endl;
		cout << "   |_|  |_| .__/ \\___/  " << endl;
		cout << "          | |            " << endl;
		cout << "          |_|            " << endl;

		cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		cout << "┃ Escolha o tipo de sensor              ┃" << endl;
		cout << "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩" << endl;
		cout << "│ 1 · Sensor de Fogo                    │" << endl;
		cout << "│ 2 · Sensor de Fumo                    │" << endl;
		cout << "│ 3 · Sensor de Humidade                │" << endl;
		cout << "│ 4 · Sensor de Luz                     │" << endl;
		cout << "│ 5 · Sensor de Missel                  │" << endl;
		cout << "│ 6 · Sensor de Temperatura             │" << endl;
		cout << "│ 7 · Cancelar                          │" << endl;
		cout << "└───────────────────────────────────────┘" << endl;

		cin >> tipo;
	} while (tipo < 1 || tipo > 7);

	switch (tipo) {
	case 1:
		return new SFogo(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 2:
		return new SFumo(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 3:
		return new SHumidade(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 4:
		return new SLuz(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 5:
		return new SMissel(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 6:
		return new STemperatura(ptr_fabrica, id, marca, valor_aviso, prob_avaria, posicao);

	case 7:
	default:
		return nullptr;
	}
}

void Menu::sair() {
	Uteis::Limpar_Terminal();

	cout << "          _    __     _   __  _     " << endl;
	cout << "     /\\  | |  /_/    (_) /_/ | |   " << endl;
	cout << "    /  \\ | |_ ___     _  __ _| |   " << endl;
	cout << "   / /\\ \\| __/ _ \\   | |/ _` | | " << endl;
	cout << "  / ____ \\ ||  __/   | | (_| |_|   " << endl;
	cout << " /_/    \\_\\__\\___|   | |\\__,_(_)" << endl;
	cout << "                    _/ |            " << endl;
	cout << "                   |__/             " << endl;

	exit(EXIT_SUCCESS);
}

string Menu::ler_nome_fich() {
	string nome_fich;

	cout << "Introduza o nome do ficheiro: ";
	cin >> nome_fich;

	return nome_fich;
}
