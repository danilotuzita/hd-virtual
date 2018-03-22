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

#define FLAG_OCUPADO 0
#define FLAG_NOME 1


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
		
		
		//MEMORIA
		void setMemoria(int);
		int getMemoria();
		
		//FLAGS
		void setFlag(int, bool);
		bool getFlag(int);
		
		//NOME
		void setNome(const char*);
		void getNome(char[27]);
		string getNome();
		
		
		//AREA DADOS
		void setAreaDados(const string); //set nos bytes de dados
		string getAreaDados();//set nos bytes de dados
		
		//DADOS
		void setDados(int, int, string);
		void setDados(int, const string);
		
		string getDados(int, int);
		
	private:
		bitset<MAX_BYTE*8> b;
		
		bool omitBWar; //avisos base set/get bit/byte
		bool omitBErr; //err base set/get bit/byte
		bool omitWar;
		bool omitErr;
};

#endif

