all : trees2

main.o : main.cpp
	g++ -c -g3 main.cpp

trees2 : main.o
	g++ -o ../../$@.exe -g3 main.o

clean :
	rm ../../trees2.exe main.o
