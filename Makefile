all: main

main: main.cpp
	g++ -o main main.cpp Fabrica.cpp Menu.cpp Motor.cpp Sensor.cpp tinyxml2.cpp User.cpp
