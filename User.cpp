#include "User.h"

User::User(string id, string nome) {
    this->id = id;
    this->nome = nome;
}

User::~User() {
    cout << "User " << nome << " destroyed" << endl;
}
