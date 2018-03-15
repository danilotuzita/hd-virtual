CC=g++

FLAG= -c -Wall

all:compilar limpar

compilar: main.o Comandos.o
	$(CC) main.o Comandos.o -o main

main.o: main.cpp
	$(CC) $(FLAG) main.cpp

Comandos.o: comandos/Comandos.cpp
	$(CC) $(FLAG) comandos/Comandos.cpp

limpar:
	rm -rf *.o
