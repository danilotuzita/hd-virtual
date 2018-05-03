#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <bitset>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <dirent.h>
#include <stdio.h>

using namespace std;

typedef struct {
	string mensagem;
	bool status;
} erro;

typedef struct{
	string t1;
	string t2;
} split;

class Util
{
	public:
		Util();
		~Util();
		char getChar(bitset<8>);
		char getChar(bitset<1024>, int);
		void formatByte(int, bitset<8>);
		void printPropriedade(string);
		string itos(int);
		
		bool compString(const char *, const char *);
		bool verificaExtensao(char *);
		void listaHDS();
		bool hdExiste(string);
		
		void printHex(bitset<8>);
		void printChar(bitset<8>);	
		
		string trim(string);
		split separar(string, char, bool = false);
		
	private:
};

#endif
