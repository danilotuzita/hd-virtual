CC=g++

FLAG= -c -Wall

all:compilar limpar

compilar: main.o Comandos.o Util.o Bloco.o
	$(CC) main.o Comandos.o -o main

main.o: main.cpp
	$(CC) $(FLAG) main.cpp

Comandos.o: Compilador/Comandos.cpp
	$(CC) $(FLAG) Compilador/Comandos.cpp

Util.o: Classes/Util.cpp
	$(CC) $(FLAG) Classes/Util.cpp

Bloco.o: Classes/Bloco.cpp
	$(CC) $(FLAG) Classes/Bloco.cpp

limpar:
	rm -rf *.o
