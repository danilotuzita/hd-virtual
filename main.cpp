#include "includes.h"

using namespace std;

int main(){
	system("title HD GAMMA");
	cout << "FEI [versao 1.0]\n(c) 2018 FEI - CC6270 (Giovanni/Danilo/Guilherme) Todos os direitos reservados.\n\n";


	Comandos c;
	c.validarComando();
	
	string linha = "";
	erro e;

	while(linha != "exit"){
		cout << (c.getNomeHD() == "" ? "gamma> " : c.getNomeHD() + "> ");
  		linha.clear();
		getline(cin, linha);
		c.setComando(linha);
		e = c.validarComando();
		if(e.status){
            system("echo \033[31m ");
			cout << "Comando nao reconhecido\n";
			cout << linha << endl;
			cout << e.mensagem << endl;
			system("echo \033[0m");
			e.status = false;
		}
	}
	return 0;
}
