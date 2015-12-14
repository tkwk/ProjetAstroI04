NAME=projetAstro

all: ${NAME}_clean

${NAME}_clean: ${NAME} clean

${NAME}: main.o
	g++ main.o -o ${NAME} -std=c++11

main.o: main.cpp Universe.o
	g++ -c main.cpp -std=c++11

Universe.o: Universe.cpp Particule.o Euler.o Leapfrog.o
	g++ -c Universe.cpp -std=c++11

Particule.o: Particule.cpp
	g++ -c Particule.cpp -std=c++11

Euler.o: Euler.cpp
	g++ -c Euler.cpp -std=c++11

Leapfrog.o: Leapfrog.cpp
	g++ -c Leapfrog.cpp -std=c++11

clean:
	rm -rf *.o
