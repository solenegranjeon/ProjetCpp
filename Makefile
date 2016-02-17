
all: main

main:	main.o Simulation.o Environment.o Population.o Bacteria.o
	g++ -g main.o  Simulation.o Environment.o Population.o Bacteria.o -o main 
	
main.o: main.cpp Simulation.o Environment.o Population.o Bacteria.o
	g++ -c main.cpp -o main.o --std=c++11 -g
	
Simulation.o: Simulation.cpp Simulation.h Environment.h Population.h Bacteria.h
	g++ -c Simulation.cpp -Wall -Wextra -o Simulation.o --std=c++11 -g
	
Environment.o: Environment.cpp Environment.h Population.h Bacteria.h
	g++ -c Environment.cpp -Wall -Wextra -o Environment.o --std=c++11 -g
	
Population.o: Population.cpp Population.h Bacteria.h
	g++ -c Population.cpp -Wall -Wextra -o Population.o --std=c++11 -g
	
Bacteria.o: Bacteria.cpp Bacteria.h
	g++ -c Bacteria.cpp -Wall -Wextra -o Bacteria.o --std=c++11 -g	
		
clean:
	rm -f *.o
