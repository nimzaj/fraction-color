playground: fraction.o main.o
	g++ -std=c++17 fraction.o main.o -o playground

main.o: main.cc
	g++ -std=c++17 -c main.cc

fraction.o: fraction.cc
	g++ -std=c++17 -c fraction.cc

clean:
	rm *.o playground
