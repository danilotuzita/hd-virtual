<<<<<<< cd50def45a1fdbf34c56f53a80a297d7c037898a
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
		cout << "gamma> ";
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

=======
#include "includes.h"

using namespace std;

int main(){
	system("title HD_VIRTUAL");
	cout << "FEI [versao 1.0]\n(c) 2018 FEI - CC6270 - Giovanni/Danilo/Guilherme.\n\n";
/*
//	FILE * f = fopen("bomdia.txt", "wb");
//	fwrite(&b, sizeof(Bloco), 1, f);
//	fclose(f);

//	string str;
//	str = "01234567890";
//	str.resize(10);
//	cout<<str.length()<<" "<<str<<endl;

	Bloco b;
	b.setNome("123456789 123456789 123456789 ");
	b.setDados(110, "123456789017890");
	b.printRange(110, 128);
//	b.setDados("Teste        ''\n'' testando tes8tando\n\n\n\n\n\n\ barra n");
	cout << "Nome: '"<<b.getNome()<<"'"<< endl;
	cout << "Dados: "<<b.getDados()<<endl;
*/

	Comandos c;

	string linha = "";
	erro e;

	while(linha != "exit"){
		cout << "> ";
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

	//system("bomdia.txt");
	return 0;
}

>>>>>>> Detalhando comandos
