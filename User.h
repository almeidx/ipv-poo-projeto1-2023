#ifndef USER_H
#define USER_H

#include "UserPermissions.h"
#include <iostream>

using namespace std;

class User {
	string id;
	string nome;

	static const int permissions;

public:
	User(string id, string nome);
	~User();
	string Get_Name() { return nome; }
	string Get_Id() { return id; }
};

class Admin : public User {
	static const int permissions = UserPermissions::ADICIONAR | UserPermissions::REMOVER | UserPermissions::LISTAR |
								   UserPermissions::RUN | UserPermissions::MANUTENCAO;

public:
	Admin(string id, string nome) : User(id, nome) {}
};

class Normal : public User {
	static const int permissions =
		UserPermissions::ADICIONAR | UserPermissions::LISTAR | UserPermissions::RUN | UserPermissions::MANUTENCAO;

public:
	Normal(string id, string nome) : User(id, nome) {}
};

class Visitante : public User {
	static const int permissions = UserPermissions::LISTAR;

public:
	Visitante(string id, string nome) : User(id, nome) {}
};

#endif // USER_H
