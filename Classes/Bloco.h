#ifndef BLOCO_H
#define BLOCO_H

#include "Util.h"

#define MP_SIZE 4
#define FLAG_SIZE 1
#define NOME_SIZE 27
#define DADOS_SIZE 96

#define MP_BIT 0
#define FLAG_BIT 32
#define NOME_BIT 40
#define DADOS_BIT 256
#define MAX_BIT 1024

#define MP_BYTE 0
#define FLAG_BYTE 4
#define NOME_BYTE 5
#define DADOS_BYTE 32
#define MAX_BYTE 128

using namespace std;

class Bloco
{
	public:
		Bloco();
		~Bloco();
		
		//BIT
		bool setBit(int, bool);
		bool getBit(int);
		
		
		//BYTE
		void setByte(int, char);
		bitset<8> getByte(int);
		
		
		//UTILS
		void printByte(int);
		void printRange(int, int);
		void printAll();
		
		
		//NOME
		void setNome(const char*);
		void getNome(char[27]);
		string getNome();
		
		
		//DADOS
		void setDados(const string); //set nos bytes de dados
		void setDados(int, const string);
		void setDados(int, int, string);
		
		string getDados();//set nos bytes de dados
		string getDados(int, int);
		
	private:
		bitset<128*8> b;
		
		bool omitBWar; //avisos base set/get bit/byte
		bool omitBErr; //err base set/get bit/byte
		bool omitWar;
		bool omitErr;
};

#endif

