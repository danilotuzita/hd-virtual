#include <vector>
#include <stdio.h>
#include <sstream>
#include <queue>

#ifndef HD_H
#define HD_H

#include "Bloco.h"
#include "Util.h"

#define _128MB 1048576
#define _1KB 1024

#define BYTE_HEADER_NOME 0
#define SIZE_HEADER_NOME (MAX_BYTE / 2)

#define BYTE_HEADER_TAMANHO (MAX_BYTE / 2)
#define SIZE_HEADER_TAMANHO 4

#define POS_HEADER 0
#define POS_RAIZ 1

class HD
{
	public:
		HD();
		~HD();
		
		// BASE
		erro createHD(string, int);
		erro openHD(string);
		erro carregaHD();
		
		// ARQUIVOS
		int getFreeBlock();
		void deleta(unsigned int);
		void deleta(unsigned int, unsigned int);
		
			// arquivo
			int criaArquivo(string, string);
			string leArquivo(unsigned int);
			void deletaArquivo(unsigned int);
			
			// pasta
			int criaPasta(string);
			void addPasta(unsigned int);
			void addPasta(unsigned int, unsigned int);
			queue<unsigned int> abrePasta(unsigned int);
			void deletaPasta(unsigned int);
			void deletaRef(unsigned int, unsigned int);
			
			void renomear(unsigned int, string);
			
			/* localiza arquivo ou pasta dentro de uma pasta 
			e retorna a posicao*/
			int localizaObjeto(unsigned int, string, bool);
		
		// UTIL
		void propriedadesHD(string *);
		int getTamanho();
		
			// print
			void print(int);
			void printChain(int);
			void printHD();
			
			// get
			string getNome(unsigned int);
			bool getTipo(unsigned int);
			
			// posições
			int getLocalAtual();
			void setLocalAtual(unsigned int);
		
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
		void recalEspacosLivres();
		
		erro criarConteudo(string, string, bool);
		
		void salvaHD();
};



#endif
