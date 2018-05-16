#include <cstdlib>
#include <string>
#include <queue>

#ifndef COMANDOS_H
#define COMANDOS_H

#include "../Classes/Util.h"
#include "../Classes/HD.h"
#include "../Classes/Editor.h"

using namespace std;

class Comandos{

	private:

        split t;
        erro e;
        Util u;

		string comando;
		string parametro;
		string comandoCompleto;

		HD * hd;
		
		string nomeHD;
		string caminho;
		vector<unsi> trilha;
		
		bool hdSelecionado;
		
		bool validarParametros(int cod_comando, string parametros);
		int getCodComando(char * nome_comando);
		split separar(string);
		
		// ==== Funcões de comando
			void create();
			void format();
			void remover();
			void move();
			void renomear();
			void df();
			void cat();
			void copy();
			void editar();

			void cd();
			void montaCaminho();

			void ls();
			void typehd();

			void help();
			void skol();
			void fei();
		
	public:
	
		Comandos(string _comando = "");
		~Comandos();
		void setComando(string _comando);
		void removeEspacosComeco();
		string getComandoCompleto();
		string getComando();
		string getParametros();
		void separarComando();
		erro validarComando();
		string getNomeHD();
		bool getHDSelecionado();
		void closeHD();

};



#endif
