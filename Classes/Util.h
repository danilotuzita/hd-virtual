<<<<<<< cd50def45a1fdbf34c56f53a80a297d7c037898a
#ifndef UTIL_H
#define UTIL_H

#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

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
		
	private:
};

#endif
=======
#ifndef UTIL_H
#define UTIL_H

#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>

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
		void formatByte(int, bitset<8>);
	private:
};

#endif
>>>>>>> Detalhando comandos
