#ifndef UTEIS_H
#define UTEIS_H

#include <cmath>
#include <iostream>
#include <list>
#include <sstream>

using namespace std;

class Pair {
	int x, y;

public:
	Pair(int x, int y) {
		this->x = x;
		this->y = y;
	}

	~Pair() {}

	int Get_X() { return x; }
	int Get_Y() { return y; }

	string To_String() { return to_string(Get_X()) + "," + to_string(Get_Y()); }
};

class Ponto : public Pair {
public:
	Ponto(int x, int y) : Pair(x, y) {}
	~Ponto() {}

	float Distancia(Ponto p) { return sqrt(pow(p.Get_X() - Get_X(), 2) + pow(p.Get_Y() - Get_Y(), 2)); }
};

class Uteis {
public:
	// https://stackoverflow.com/a/46931770
	static list<string> Split_String(const string &s, char delim) {
		list<string> result;
		stringstream ss(s);
		string item;

		while (getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	static Ponto *Split_String_Coordenadas(string str) {
		list<string> coords = Uteis::Split_String(str, ',');

		int x = stoi(coords.front()), y = stoi(coords.back());

		return new Ponto(x, y);
	}

	static Pair *Split_String_Pair(string str) {
		list<string> coords = Uteis::Split_String(str, ',');

		int x = stoi(coords.front()), y = stoi(coords.back());

		return new Pair(x, y);
	}

	// https://stackoverflow.com/a/12657984/11252146
	static int Generate_Random_Number(int min, int max) { return rand() % (max - min + 1) + min; }
};

#endif // UTEIS_H
