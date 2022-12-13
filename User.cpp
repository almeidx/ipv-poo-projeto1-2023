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

void User::Print() {
	cout << string(10, '-') << " USER " << string(10, '-') << endl;
	cout << "Id:   " << Get_Id() << endl;
	cout << "Nome: " << Get_Nome() << endl;
	cout << "Tipo: " << Get_Tipo() << endl;
	cout << string(27, '-') << endl;
}
