#include <vector>
#include <stdio.h>
#include <sstream>
#include <queue>

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
#define POS_RAIZ 1

class HD
{
	public:
		HD();
		~HD();
		
		erro createHD(string, int);
		
		erro openHD(string);
		erro carregaHD();
		
		void propriedadesHD(string *);
		
		erro criarArquivo(string, string);
		erro criarPasta(string);
		
	private:
		vector<Bloco> hd;
		string nome;
		FILE* fp;
		int TAM;
		Util u;
		
		int localAtual;
		
		int ultimoBlocoLivre;
		queue<int> blocosLivres;
		
		void headHD();
		void raizHD();
		erro criarConteudo(string, string, bool);
};



#endif
