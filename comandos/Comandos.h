#include <cstdlib>
#include <string>

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
		
	public:
	
		Comandos(string _comando = "");
		void setComando(string _comando);
		void removeEspacosComeco();
		string getComandoCompleto();
		string getComando();
		string getParametros();
		void separarComando();
		bool validarComando(int printar = 0);
		int a;


};



#endif
