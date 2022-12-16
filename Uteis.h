#ifndef UTEIS_H
#define UTEIS_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

using namespace std;

class Pair {
	int x, y;

public:
	Pair() {
		x = 0;
		y = 0;
	}

	Pair(int x, int y) {
		this->x = x;
		this->y = y;
	}

	~Pair() {}

	int Get_X() {
		return x;
	}
	int Get_Y() {
		return y;
	}
	string To_String() {
		return to_string(Get_X()) + "," + to_string(Get_Y());
	}
};

class Ponto : public Pair {
public:
	Ponto(int x, int y) : Pair(x, y) {}

	~Ponto() {}

	float Distancia(Ponto p) {
		return sqrt(pow(p.Get_X() - Get_X(), 2) + pow(p.Get_Y() - Get_Y(), 2));
	}
};

class Uteis {
public:
	static list<string> Split_String(const string &s, char delim) {
		// https://stackoverflow.com/a/46931770
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

	static int Generate_Random_Int(int min, int max) {
		// https://stackoverflow.com/a/12657984/11252146
		return rand() % (max - min + 1) + min;
	}

	static float Generate_Random_Float(float min, float max) {
		// https://stackoverflow.com/a/686373/11252146
		return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}

	static string Float_To_String_Precisao(float f, int precisao = 2) {
		// https://stackoverflow.com/a/29200671/11252146
		stringstream stream;
		stream << fixed << setprecision(precisao) << f;
		return stream.str();
	}

	static void Limpar_Terminal() {
		system("clear");
	}

	static void Sleep(int seconds) {
#ifdef _WIN32
		Sleep(seconds * 1000);
#else
		sleep(seconds);
#endif
	}

	static void Pausar() {
		cout << "Pressione ENTER para continuar...";
		cin.ignore();
		cin.get();
	}

	static Ponto *Ler_Ponto() {
		int x, y;
		string input;

		cout << "Introduza as coordenadas do ponto (x, y): ";
		cin >> input;

		return Split_String_Coordenadas(input);
	}
};

#endif // UTEIS_H
