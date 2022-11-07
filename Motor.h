#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <string>
using namespace std;

class Motor
{
    string ID;
    string MARCA;
    float CONSUMO_HORA;
    float TEMPERATUDA_AVISO;
    float TEMPERATURA_PARAGEM;
    float PROBABILIDADE_AVARIDA;

public:
    Motor();
    ~Motor();
    bool RUN();
    void START();
    void RESTART();
    bool STOP();
    void ESTOU_QUENTE();
};

#endif
