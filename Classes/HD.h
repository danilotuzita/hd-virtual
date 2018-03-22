#include <vector>
#include <stdio.h>
#include <sstream>

#ifndef HD_H
#define HD_H

#include "Bloco.h"
#include "Util.h"

#define _128MB 1048576

#define BYTE_HEADER_NOME 0
#define SIZE_HEADER_NOME 64

#define BYTE_HEADER_TAMANHO 64
#define SIZE_HEADER_TAMANHO 4

#define POS_HEADER 0

class HD
{
	public:
		HD();
		~HD();
		
		erro createHD(string, int);
		void headHD();
		
		void propriedadesHD();
		
	private:
		vector<Bloco> hd;
		string nome;
		FILE* fp;
		int TAM;
};



#endif
