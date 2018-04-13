#include "includes.h"

using namespace std;

/*
void main2()
{
	string arquivo = "Prepared is me marianne pleasure likewise debating. Wonder an unable except better stairs do ye admire. His and eat secure sex called esteem praise. So moreover as speedily differed branched ignorant. Tall are her knew poor now does then. Procured to contempt oh he raptures amounted occasion. One boy assure income spirit lovers set. \nResidence certainly elsewhere something she preferred cordially law. Age his surprise formerly mrs perceive few stanhill moderate. Of in power match on truth worse voice would. Large an it sense shall an match learn. By expect it result silent in formal of. Ask eat questions abilities described elsewhere assurance. Appetite in unlocked advanced breeding position concerns as. Cheerful get shutters yet for repeated screened. An no am cause hopes at three. Prevent behaved fertile he is mistake on.";
	
	HD hd;
	hd.createHD("NOME DO HHD", 64);
	
	int a = hd.criaPasta("PASTA01");
	int b = hd.criaPasta("PASTA02");
	int f = hd.criaArquivo("ARQUIVO", arquivo);
	int c = hd.criaPasta("PASTA03");
	int d = hd.criaPasta("PASTA04");
	int e = hd.criaPasta("PASTA05");
	
	hd.addPasta(POS_RAIZ, a);
	hd.addPasta(POS_RAIZ, b);
	hd.addPasta(a, c);
	hd.addPasta(a, d);
	hd.addPasta(d, e);
	hd.addPasta(d, f);
	
	hd.printHD();
	cout<<"-------DELETANDO A PASTA01-------\n";
	hd.deleta(POS_RAIZ, a);	
	hd.printHD();
	system("PAUSE");
}
*/

int main(){
	
	//main2();
	//return 0;
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
		else {
			if(linha == "exit" && c.getHDSelecionado()){
				linha = "";
				c.closeHD();
			}
		}
	}
	return 0;
}
