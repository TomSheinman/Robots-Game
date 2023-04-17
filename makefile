all: Ass4

Ass4: main.o Robot.o Game.o Map.o
	g++ main.o Robot.o Game.o Map.o -o Ass4 

main.o: main.cpp Game.h
	g++ -c main.cpp

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp

Game.o : Game.cpp Game.h Map.h
	g++ -c Game.cpp

Map.o : Map.cpp Map.h Robot.h
	g++ -c Map.cpp

clean : 
	@echo 'cleaning'
	rm –f *.o

