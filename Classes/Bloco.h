#ifndef BLOCO_H
#define BLOCO_H

#include "Util.h"

#define MP_SIZE 4
#define FLAG_SIZE 1
#define NOME_SIZE 11
#define DADOS_SIZE 16

#define MP_BYTE 0
#define FLAG_BYTE (MP_BYTE + MP_SIZE)
#define NOME_BYTE (FLAG_BYTE + FLAG_SIZE)
#define DADOS_BYTE (NOME_BYTE + NOME_SIZE)
#define MAX_BYTE (DADOS_BYTE + DADOS_SIZE)

#define MP_BIT (MP_BYTE * 8)
#define FLAG_BIT (FLAG_BYTE * 8)
#define NOME_BIT (NOME_BYTE * 8)
#define DADOS_BIT (DADOS_BYTE * 8)
#define MAX_BIT (MAX_BYTE * 8)

#define FLAG_OCUPADO 0
#define FLAG_NOME 1
#define FLAG_TIPO 2 

#define TIPO_PASTA true
#define TIPO_ARQUIVO false

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
		
		
		//DADOS
			//str
			string setString(int, int, string);
			void setString(int, const string);
			string getString(int, int);
			
			//int
			void setInt(int, unsigned int);
			unsigned int getInt(int);
			int getFreeSpace();
		
		
		//UTILS
		void printByte(int);
		void printRange(int, int);
		void printAll();
		
		void printBloco();
		
		
		//MEMORIA
		void setMemoria(int);
		unsigned int getMemoria();
		
		//FLAGS
		void setFlag(int, bool);
		bool getFlag(int);
		
		bool isFree();
		bool temNome();
		bool isFolder();
		
		//NOME
		void setNome(string);
		void getNome(char[NOME_SIZE]);
		string getNome();
		
		//AREA DADOS
		string setDados(string); //set nos bytes de dados
		string getDados();//set nos bytes de dados

	private:
		bitset<MAX_BIT> b;
		
		bool omitBWar; //avisos base set/get bit/byte
		bool omitBErr; //err base set/get bit/byte
		bool omitWar;
		bool omitErr;
};

#endif


