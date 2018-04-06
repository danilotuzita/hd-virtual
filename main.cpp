#include "includes.h"

using namespace std;

/*
void main2()
{
	string arquivo = "Prepared is me marianne pleasure likewise debating. Wonder an unable except better stairs do ye admire. His and eat secure sex called esteem praise. So moreover as speedily differed branched ignorant. Tall are her knew poor now does then. Procured to contempt oh he raptures amounted occasion. One boy assure income spirit lovers set. \nResidence certainly elsewhere something she preferred cordially law. Age his surprise formerly mrs perceive few stanhill moderate. Of in power match on truth worse voice would. Large an it sense shall an match learn. By expect it result silent in formal of. Ask eat questions abilities described elsewhere assurance. Appetite in unlocked advanced breeding position concerns as. Cheerful get shutters yet for repeated screened. An no am cause hopes at three. Prevent behaved fertile he is mistake on.";
	
	HD hd;
	hd.createHD("NOME DO HHD", 64);
	int a = hd.criaPasta("C://");
	int b = hd.criaPasta("ARQUIVOS");
	int c = hd.criaArquivo("Six started far", arquivo);
	int d = hd.criaPasta("OUTRA");
	int e = hd.criaPasta("OUTRA 2");
	int f = hd.criaArquivo("arquvinho", "bla bla bla");
	
	hd.addPasta(a, b);
	hd.addPasta(b, d);
	hd.addPasta(b, e);
	hd.addPasta(b, f);
	hd.addPasta(b, c);
	
	hd.printChain(b);
	
	queue<unsigned int> pasta = hd.abrePasta(b);
	while(!pasta.empty())
	{
		unsigned int pos = pasta.front();
		cout<<"/"<<hd.getNome(pos)<<"/";
		if(hd.getTipo(pos) == TIPO_ARQUIVO)
			cout<<endl<<hd.leArquivo(pos);
			//hd.printChain(pos);
		pasta.pop();
		cout<<"\n------------\n";
	}
	
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
	}
	return 0;
}
