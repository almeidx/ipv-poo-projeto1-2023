all: main

main: main.cpp
	g++ -o main main.cpp Fabrica.cpp Motor.cpp Sensor.cpp tinyxml2.cpp User.cpp
