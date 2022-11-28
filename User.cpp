#include "User.h"

User::User() {
	id = "??";
	nome = "??";
}

User::User(string id, string nome) {
	this->id = id;
	this->nome = nome;
}

User::~User() {
	cout << "User " << nome << " destruído" << endl;
}
