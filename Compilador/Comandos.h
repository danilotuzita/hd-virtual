#include <cstdlib>
#include <string>
#include "../Classes/Util.h"
#include "../Classes/HD.h"

using namespace std;

#ifndef COMANDOS
#define COMANDOS

class Comandos{

	private:

        split t;
        erro e;

		string comando;
		string parametro;
		string comandoCompleto;

		HD hd;
		string nomeHD;
		
		bool validarParametros(int cod_comando, string parametros);
		int getCodComando(char * nome_comando);
		split separar(string);
		
		// Funcões de comando
		void create();
		void format();
		void remove();
		void move();
		void df();
		void cat();
		void cd();
		void ls();
		void help();

		
	public:
	
		Comandos(string _comando = "");
		void setComando(string _comando);
		void removeEspacosComeco();
		string getComandoCompleto();
		string getComando();
		string getParametros();
		void separarComando();
		erro validarComando();
		string getNomeHD();

};



#endif

