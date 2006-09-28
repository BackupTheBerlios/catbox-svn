CC = g++
OBJ = main.o cdisplay.o cball.o csurface.o cinput.o cgame.o cpaddle.o
CFLAGS = -c -Wall `sdl-config --cflags`

main: $(OBJ)
	g++ $(OBJ) -o main -Wall `sdl-config --libs` 
main.o: main.cpp
	g++ main.cpp $(CFLAGS)
cdisplay.o: cdisplay.cpp
	g++ cdisplay.cpp $(CFLAGS)
cball.o: cball.cpp
	g++ cball.cpp $(CFLAGS)
csurface.o: csurface.cpp
	g++ csurface.cpp $(CFLAGS)
cinput.o: cinput.cpp
	g++ cinput.cpp $(CFLAGS)
cgame.o: cgame.cpp
	g++ cgame.cpp $(CFLAGS)
cpaddle.o: cpaddle.cpp
	g++ cpaddle.cpp $(CFLAGS)
