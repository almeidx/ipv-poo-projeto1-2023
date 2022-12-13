#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
	string id, nome;

public:
	User();
	User(string id, string nome);
	~User();

	string Get_Nome() {
		return nome;
	}
	string Get_Id() {
		return id;
	}

	virtual bool Posso_Adicionar() {
		return false;
	}
	virtual bool Posso_Remover() {
		return false;
	}
	virtual bool Posso_Listar() {
		return false;
	}
	virtual bool Posso_Run() {
		return false;
	}
	virtual bool Posso_Manutencao() {
		return false;
	}

	virtual string Get_Tipo() {
		return "User";
	}

	void Print();
};

class Admin : public User {
public:
	Admin(string id, string nome) : User(id, nome) {}

	bool Posso_Adicionar() {
		return true;
	}
	bool Posso_Remover() {
		return true;
	}
	bool Posso_Listar() {
		return true;
	}
	bool Posso_Run() {
		return true;
	}
	bool Posso_Manutencao() {
		return true;
	}

	string Get_Tipo() {
		return "Admin";
	}
};

class Normal : public User {
public:
	Normal(string id, string nome) : User(id, nome) {}

	bool Posso_Adicionar() {
		return true;
	}
	bool Posso_Listar() {
		return true;
	}
	bool Posso_Run() {
		return true;
	}
	bool Posso_Manutencao() {
		return true;
	}

	string Get_Tipo() {
		return "Normal";
	}
};

class Visitante : public User {
public:
	Visitante(string id, string nome) : User(id, nome) {}

	bool Posso_Listar() {
		return true;
	}

	string Get_Tipo() {
		return "Visitante";
	}
};

#endif // USER_H
