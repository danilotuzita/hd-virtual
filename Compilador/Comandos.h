<<<<<<< cd50def45a1fdbf34c56f53a80a297d7c037898a
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

=======
#include <cstdlib>
#include <string>
#include "../Classes/Util.h"

using namespace std;

#ifndef COMANDOS
#define COMANDOS

class Comandos{

	private:

		bool validarParametros(int cod_comando, string parametros);
		int getCodComando(char * nome_comando);
		string comando;
		string parametro;
		string comandoCompleto;
		split separar(string);
		
	public:
	
		Comandos(string _comando = "");
		void setComando(string _comando);
		void removeEspacosComeco();
		string getComandoCompleto();
		string getComando();
		string getParametros();
		void separarComando();
		erro validarComando();

};



#endif

>>>>>>> Detalhando comandos
