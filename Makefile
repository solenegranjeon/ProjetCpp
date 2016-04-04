
all: main

main:	main.o Simulation.o Environment.o Population.o Bacteria.o ImagePPM.o
	g++ -g main.o  Simulation.o Environment.o Population.o Bacteria.o ImagePPM.o -o main 
	
main.o: main.cpp Simulation.o Environment.o Population.o Bacteria.o ImagePPM.o
	g++ -c main.cpp -o main.o --std=c++11 -O4

ImagePPM.o: ImagePPM.cpp ImagePPM.h Simulation.h Environment.h Population.h Bacteria.h
	g++ -c ImagePPM.cpp -o ImagePPM.o --std=c++11 -O4
	
Simulation.o: Simulation.cpp Simulation.h Environment.h Population.h Bacteria.h
	g++ -c Simulation.cpp -Wall -Wextra -o Simulation.o --std=c++11 -O4
	
Environment.o: Environment.cpp Environment.h Population.h Bacteria.h
	g++ -c Environment.cpp -Wall -Wextra -o Environment.o --std=c++11 -O4
	
Population.o: Population.cpp Population.h Bacteria.h
	g++ -c Population.cpp -Wall -Wextra -o Population.o --std=c++11 -O4
	
Bacteria.o: Bacteria.cpp Bacteria.h
	g++ -c Bacteria.cpp -Wall -Wextra -o Bacteria.o --std=c++11 -O4
		
clean:
	rm -f *.o
