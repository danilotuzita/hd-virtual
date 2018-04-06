#include <cstdlib>
#include <string>
#include <queue>
#include "../Classes/Util.h"
#include "../Classes/HD.h"

using namespace std;

#ifndef COMANDOS
#define COMANDOS

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
		vector<unsigned int> trilha;
		
		bool hdSelecionado;
		
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
		void montaCaminho();
		
		void ls();
		void help();

		
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

};



#endif
