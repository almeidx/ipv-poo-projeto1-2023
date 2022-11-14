#include "Sensor.h"

Sensor::Sensor(string id, string marca, float valor, float probabilidade_avaria) {
    this->id = id;
    this->marca = marca;
    this->valor = valor;
    this->probabilidade_avaria = probabilidade_avaria;
}

Sensor::~Sensor() {}

SensorLuz::~SensorLuz()
{

}

SensorHumidade::~SensorHumidade()
{

}

SensorFumo::~SensorFumo()
{
}

SensorMisseis::~SensorMisseis()
{
}


SensorFogo::~SensorFogo()
{
}

SensorTemperatura::~SensorTemperatura()
{
}
