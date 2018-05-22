#include <cstdlib>
#include <iostream>
#include "Comandos.h"
#include "Automatos.hpp"

using namespace std;

Comandos::Comandos(string _comando){
	hd = new HD;
	nomeHD.clear();
	caminho.clear();
	hdSelecionado = false;
	setComando(_comando);
}

Comandos::~Comandos(){
	if(hdSelecionado) delete hd;
}

void Comandos::separarComando(){
	
	int i;
	comandoCompleto = comando;
	
	for(i = 0; (int) comando[i] != 32 && (int) comando[i] != 0 ; i++) {
		c += comando[i];
	}
	
	i++;
	for(; comando[i] != 0; i++){
		parametro += comando[i];
	}
	comando = c;
}

void Comandos::removeEspacosComeco(){
	
	int comeca = 0;
	string p = comando;
	
	comando = "";
	
	for(int i = 0; p[i] != 0; i++){
		if(!comeca){
			if( (int) p[i] != 32){
				comeca = 1;
			}
		}
		if(comeca){
			comando += p[i];
		}
	}
}

void Comandos::setComando(string _comando){
	comando.clear();
	parametro = "";
	n = 0;
	c.clear();
	comando = _comando;
	removeEspacosComeco();
	separarComando();
}

string Comandos::getComandoCompleto(){
	return comandoCompleto;
}

string Comandos::getComando(){
	return comando;
}

string Comandos::getParametros(){
	return parametro;
}

split Comandos::separar(string texto){
	int i;
	split t;
	t.t1.clear();
	t.t2.clear();
	
	for(i = 0; (int) texto[i] != 32 && (int) texto[i] != 0 ; i++) {
		t.t1 += texto[i];
	}
	i++;
	for(; i < texto.size(); i++){
		t.t2 += texto[i];
	}
	return t;
}

erro Comandos::validarComando(){
	
	bool ret;
	n = 0;

	e.status = false;
	e.mensagem.clear();

	t.t1.clear();
	t.t2.clear();
	
	if(getComando()[getComando().size() - 1] == ':'){
    
	    nomeHD = getComando();
        nomeHD.resize(nomeHD.size() -1);
    
        if(hdSelecionado) delete hd;
    
        hd = new HD;
        hd->openHD(nomeHD);
    
	    hdSelecionado = true;
	    
	    //hd->printHD();
	}
	else{
		if(e0()){
	             if(getComando() == "clear")  system("cls");
			else if(getComando() == "create") create();
			else if(getComando() == "remove") remover();
			else if(getComando() == "format") format();
			else if(getComando() == "move")   move();
			else if(getComando() == "df")     df();
			else if(getComando() == "cat")    cat();
	 		else if(getComando() == "cd")     cd();
			else if(getComando() == "ls")     ls();
			else if(getComando() == "rename") renomear();
			else if(getComando() == "typehd") typehd();
			else if(getComando() == "copy")   copy();
			else if(getComando() == "edit")   editar();
			else if(getComando() == "?")      help();
			else if(getComando() == "skol")   skol();
			else if(getComando() == "fei")    fei();
		}
		else{
			e.status = true;
			e.mensagem = "Comando nao reconhecido:\n" + getComandoCompleto() + "\n";
			for(int i = 0; i < n - 1; i++){
				e.mensagem += "_";
			}
			e.mensagem += "^";
		}
	}
	
	return e;
}

string Comandos::getNomeHD(){
	return nomeHD + caminho;
}

bool Comandos::getHDSelecionado(){
	return hdSelecionado;
}

void Comandos::closeHD(){
	if(hdSelecionado){
		delete hd;
		nomeHD.clear();
		caminho.clear();
        hdSelecionado = false;
        n = 0;
		c.clear();
		hd = new HD;
	}
}

// Funes de comando

void Comandos::create(){
	t = separar(getParametros());
	n = 0;
	c.clear();
	c = t.t1;
	if(c0()){
		if(t.t1 == "-hd"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do hd";
				e.status = true;
			}
			else{
				split a = separar(t.t2);
				if(a.t2 == ""){
					e.mensagem = "Informe o tamanho do hd";
					e.status = true;
				} else {
					erro e;
					e = hd->createHD(a.t1, atoi(a.t2.c_str()));
					if(!e.status){
						cout << "HD " << a.t1 << " criado com sucesso (tamanho: " << atoi(a.t2.c_str()) * _1KB << " bytes)" << endl;
						nomeHD = a.t1;
						hdSelecionado = true;
					} else {
						cout << "Erro: " << e.mensagem << endl;
					}
				}
			}
		}
		else if(t.t1 == "-f"){
			hd->setUndo(0);
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do arquivo";
				e.status = true;
			}
			else{
                
				string linha = "";
                linha.clear();
				getline(cin, linha);
                
                linha = linha.size() == 0 ? " " : linha;
                
				int ret = hd->criaArquivo(t.t2, linha);
                
				e = hd->addPasta(hd->getLocalAtual(), ret);
                
				if(!e.status){
					cout << "Arquivo " << t.t2 << " gravado com sucesso!" << endl;
				}
//				else {
//					cout << "Erro: " << e.mensagem << endl;
//				}
			}
		}
		else if(t.t1 == "-d"){
			hd->setUndo(0);
	        if(t.t2 == ""){
				e.mensagem = "Informe o nome da pasta";
				e.status = true;
			}
			else if(t.t2 == ".." || t.t2 == "." || t.t2 == "../"){
				e.mensagem = "Nome invalido para pasta";
				e.status = true;
			}
			else {
                
				int ret = hd->criaPasta(t.t2);
                e = hd->addPasta(hd->getLocalAtual(), ret);
				
				if(!e.status){
					cout << "Pasta " << t.t2 << " criada com sucesso!" << endl;
				} 
//				else {
//					cout << "Erro: " << e.mensagem << endl;
//				}
			}
		}
		else{
			cout << "Comando para criacao de coisas no hd e bla bla bla bla \n";
		}
	}
	else {
		e.mensagem = "Parametro invalido para o create e bla bla bla bla\n";
		e.status = true;
	}
}

void Comandos::remover(){
	
	t = separar(getParametros());
	n = 0;
	c.clear();
	c = t.t1;
	
	int pos = 0, pasta;

	if(c0()){
		if(t.t1 == "-hd"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do hd";
				e.status = true;
			}
			else {
				if(getNomeHD() == t.t2){
					delete hd;
					nomeHD.clear();
					hdSelecionado = false;
					hd = new HD();
				}
				string nome = t.t2 + ".hd"; 
				if( remove( nome.c_str() ) != 0 ){
					cout << "HD " << t.t2 << " nao encontrado" << endl;		
				} 
				else {
					cout << "HD " << t.t2 << " removido com sucesso" << endl;
				}
			}
		}
		else if(t.t1 == "-f"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do arquivo";
				e.status = true;
			}
			else{
				
				
				split caminho = u.separar(t.t2, '/', true);
				
				if(caminho.t1 != ""){
					pasta = hd->localizaObjeto(hd->getLocalAtual(), caminho.t1, TIPO_PASTA);	
				}
				else pasta = hd->getLocalAtual();
				
				if(pasta != 0){
					pos = hd->localizaObjeto(pasta, caminho.t2, TIPO_ARQUIVO);									
				}				
					
				if(pos){
					hd->deleta(pasta, pos);
					cout << "Arquivo " << t.t2 << " removido" << endl;						
				}
				else{
					cout << "\nArquivo " << t.t2 << " nao encontrado" << endl;
				}
			}
		}
		else if(t.t1 == "-d"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome da pasta";
				e.status = true;
			}
			else {
				pos = hd->localizaObjeto(hd->getLocalAtual(), t.t2, TIPO_PASTA);
				if(pos){
					hd->deleta(hd->getLocalAtual(), pos);
					cout << "Arquivo " << t.t2 << " removido" << endl;	
				}
				else{
					cout << "\nPasta " << t.t2 << " nao encontrada" << endl;
				}
			}
		}
		else if(t.t1 == "-u"){
			if(t.t2.size()){
				e.mensagem = "Esse comando nao tem parametro";
				e.status = true;
				return;
			}
			e = hd->undo();
			if(!e.status)
				cout << "Desfazer completo\n";
		}
		else{
			cout << "Comando para remover de coisas no hd e bla bla bla bla \n";
		}
	}
	else {
		e.mensagem = "Parametro invalido para o remove e bla bla bla bla\n";
		e.status = true;
	}
}

void Comandos::format(){
	t = separar(getParametros());
	n = 0;
	c.clear();
	c = t.t1;
	
	if(t.t1 != "?"){
		if(t.t1 == ""){
			e.mensagem = "Informe o nome do hd";
			e.status = true;
		}
		else{
			if(hdSelecionado){
				delete hd;
				nomeHD.clear();
				hdSelecionado = false;
			}
			if(u.hdExiste(t.t1 + ".hd")){

		        hd = new HD;
		        hd->openHD(t.t1);
		        
				int tamanho = hd->getTamanho();
				tamanho = (tamanho * MAX_BYTE) / _1KB;
		        
				delete hd;
		        
		        hd = new HD;
		        hd->createHD(t.t1, tamanho);
		        
		        delete hd;
				nomeHD = t.t1;
				
		        hd = new HD;
		        hd->openHD(nomeHD);
		    	
			    hdSelecionado = true;
			    caminho.clear();
			    trilha.clear();
				
			}
			else{
				hd = new HD;
				cout << "HD " << t.t2 << " nao encontrado" << endl;
			}
		}
	}
	else{
		cout << "Comando para formatar bla bla bla bla \n";
	}
}

void Comandos::move(){
	
	t = separar(getParametros());
	unsi origem = 0, destino = 0, pai = 0;
	
	if(t.t1 == ""){
		e.mensagem = "Informe o tipo de move\n";
		e.status = true;
		return;
	}
	split nomes = separar(t.t2);
	if(nomes.t1 == ""){
		e.mensagem = "Informe os parametros de origem e destino\n";
		e.status = true;
		return;
	}
	else if(nomes.t2 == ""){
		e.mensagem = "Informe o parametro de destino\n";
		e.status = true;
		return;
	}
	else {
		split caminho;
		vector<unsi> temp;
		if(t.t1 == "-f"){
			caminho = u.separar(nomes.t1, '/', true);
			if(caminho.t1 != ""){
				origem = hd->localizaObjeto(hd->getLocalAtual(), caminho.t1, TIPO_PASTA, trilha);	
				pai = origem;
				if(origem == 0){
					e.mensagem = "Origem nao encontrada\n";
					e.status = true;
					return;					
				}
				origem = hd->localizaObjeto(origem, caminho.t2, TIPO_ARQUIVO, trilha);	
				if(origem == 0){
					e.mensagem = "Origem nao encontrada\n";
					e.status = true;
					return;					
				}
			}
			else{
				origem = hd->localizaObjeto(hd->getLocalAtual(), nomes.t1, TIPO_ARQUIVO, trilha);
				pai = hd->getLocalAtual();
				//cout << "Pai: " << pai << " Origem: " << origem << endl;
			}
		}
		else if(t.t1 == "-d"){
			origem = hd->localizaObjeto(hd->getLocalAtual(), nomes.t1, TIPO_PASTA, trilha);
			temp = hd->getTrilha();
			pai = temp.size() == 0 ? hd->getLocalAtual() : temp.back();
		}
		else{
			e.mensagem = "Parametro invalido\n";
			e.status = true;
			return;
		}
		if(origem == 0){
			e.mensagem = "Origem nao encontrada\n";
			e.status = true;
			return;
		}		
		destino = hd->localizaObjeto(hd->getLocalAtual(), nomes.t2, TIPO_PASTA, trilha);
		//cout << "Destino: " << destino << endl;
		if(destino == 0){
			e.mensagem = "Destino nao encontrado\n";
			e.status = true;
			return;
		}		
		hd->deletaRef(pai, origem);
		hd->addPasta(destino, origem);
		cout << (t.t1 == "-f" ? "Arquivo movido " : "Pasta movida ") << "com sucesso" << endl;
	}
}

void Comandos::df(){
	string mensagem[10];
	hd->propriedadesHD(mensagem);
	for(n = 0; n < 2; n++){
		cout << mensagem[n] << endl;
	}
}

void Comandos::cat(){

	int pos = hd->localizaObjeto(hd->getLocalAtual(), getParametros(), TIPO_ARQUIVO);

	if(!pos){
		cout << "\nArquivo " << getParametros() << " nao encontrado" << endl;
	}
	else {
		cout << "\n" << hd->leArquivo(pos) << "\n\n";
	}
}

void Comandos::cd(){

	unsigned int pos;
	
	if(getParametros() == ".." || getParametros() == "../"){
		if(trilha.size() != 0){
			trilha.pop_back();
			pos = trilha.size() == 0 ? POS_RAIZ : trilha.back();
			hd->setLocalAtual(pos);
			montaCaminho();
		}
	}
	else if(getParametros() != "."){
		hd->clearTrilha();
		pos = hd->localizaObjeto(hd->getLocalAtual(), getParametros(), TIPO_PASTA, trilha);
	
		if(!pos){
			cout << "\nPasta " << getParametros() << " nao encontrada" << endl;		
		} 
		else {
			//cout<<"LOCAL: "<<pos<<endl;
			hd->setLocalAtual(pos);
			trilha = hd->getTrilha();
			trilha.push_back(pos);
			montaCaminho();
		}
	}
}

void Comandos::montaCaminho(){
	
	caminho.clear();
	
	if(trilha.size() != 0){
		for(int i = 0; i < trilha.size(); i++){
			caminho += "/" + hd->getNome(trilha[i]);
		}	
	}
}

void Comandos::ls(){
	
	t = separar(getParametros());
	
	//cout<<"localAtual: "<<hd->getLocalAtual()<<endl;

	//hd->printChain(hd->getLocalAtual());

	unsigned int pos;
	queue<unsigned int> pasta;
	
	if(t.t1 == "-hd"){
		cout << "Lista de HD'S: \n";
		u.listaHDS();
	}
	else if(hdSelecionado){
		
		//cout<<"LOCAL: "<<hd->getLocalAtual()<<endl;
		pasta = hd->abrePasta(hd->getLocalAtual());
		int tamanho = 10;
		while(!pasta.empty())
		{
			pos = pasta.front();
			if(hd->getTipo(pos) == TIPO_PASTA) cout << "/";
			cout << hd->getNome(pos);
			if(hd->getTipo(pos) == TIPO_ARQUIVO){
				hd->leArquivo(pos, &tamanho);
				cout << " " << (tamanho * MAX_BYTE) << " bytes ";
			}
			cout << endl;
			pasta.pop();
		}
		cout << endl;
	}
}

void Comandos::renomear(){
	
	t = separar(getParametros());
	
	split nomes;
	nomes = separar(t.t2);
	
	unsigned int pos;
	
	if(nomes.t1 == ""){
		cout << "Informe o nome\n";
	}
	else if(nomes.t2 == ""){
		cout << "Informe o novo nome\n";
	}
	else{
		int loc = hd->getLocalAtual();
		if(t.t1 == "-d"){
			pos = hd->localizaObjeto(loc, nomes.t1, TIPO_PASTA);
			if(pos){
				e = hd->renomear(loc, pos, nomes.t2);
				if(!e.status)
					cout << "Pasta renomeada\n";
			}
			else {
				cout << "Pasta " << nomes.t1 << " nao encontrada\n";
			}
		}
		else if(t.t1 == "-f"){
			pos = hd->localizaObjeto(loc, nomes.t1, TIPO_ARQUIVO);
			if(pos){
				e = hd->renomear(loc, pos, nomes.t2);
				if(!e.status)
					cout << "Arquivo renomeado\n";
			}
			else {
				cout << "Arquivo " << nomes.t1 << " nao encontrado\n";
			}
		}
		else {
			cout << "Informe corretamente o objeto a ser renomeado\n";
		}		
	}
		
}

void Comandos::typehd(){
	if(hdSelecionado) hd->printHD();
	else cout << "Selecione um HD\n";
}

void Comandos::copy(){
	t = separar(getParametros());

	unsigned int origem, destino, pasta;

	if(t.t1 == "-d"){

		split nomes;
		nomes = separar(t.t2);
		if(nomes.t1 == ""){
	        e.mensagem = "Informe o nome da pasta\n";
			e.status = true;
		}
		else {
            if(nomes.t2 == ""){
		        e.mensagem = "Informe o destino\n";
				e.status = true;
			}
			else{
				origem = hd->localizaObjeto(hd->getLocalAtual(), nomes.t1, TIPO_PASTA);
				destino = hd->localizaObjeto(hd->getLocalAtual(), nomes.t2, TIPO_PASTA);
				if(origem == 0){
                    e.mensagem = "Pasta nao localizada\n";
					e.status = true;
				}
				else if(destino == 0){
                    e.mensagem = "Destino nao localizado\n";
					e.status = true;
				}
				else{
					int copia = hd->copy(origem);
					hd->addPasta(destino, copia);
					cout << "Pasta copiada\n";
				}
			}
		}

	}
	else if(t.t1 == "-f"){
		split nomes;
		nomes = separar(t.t2);
		if(nomes.t1 == ""){
	        e.mensagem = "Informe o nome do arquivo\n";
			e.status = true;
		}
		else {
            if(nomes.t2 == ""){
		        e.mensagem = "Informe o destino\n";
				e.status = true;
			}
			else{
				split caminho = u.separar(nomes.t1, '/', true);
				
				if(caminho.t1 != ""){
					pasta = hd->localizaObjeto(hd->getLocalAtual(), caminho.t1, TIPO_PASTA);	
				}
				else pasta = hd->getLocalAtual();
				
				if(pasta != 0){
					origem = hd->localizaObjeto(pasta, caminho.t2, TIPO_ARQUIVO);
					destino = hd->localizaObjeto(hd->getLocalAtual(), nomes.t2, TIPO_PASTA);									
				}

				if(origem == 0){
                    e.mensagem = "Arquivo nao localizado\n";
					e.status = true;
				}
				else if(destino == 0){
                    e.mensagem = "Destino nao localizado\n";
					e.status = true;
				}
				else{
					int copia = hd->copy(origem);
					hd->addPasta(destino, copia);
					cout << "Arquivo copiado\n";
				}
			}
		}
	}
	else {
        e.mensagem = "Parametro nao reconhecido\n";
		e.status = true;
	}
}

void Comandos::editar(){
	if(hdSelecionado){
		int pos = hd->localizaObjeto(hd->getLocalAtual(), getParametros(), TIPO_ARQUIVO);
	
		if(!pos){
			cout << "\nArquivo " << getParametros() << " nao encontrado" << endl;
		}
		else {
			string conteudo = hd->leArquivo(pos);
			string nome = u.trim(hd->getNome(pos));
			Editor ed(u.trim(conteudo));
			cout << "Local: " << hd->getLocalAtual() << endl;
			hd->deleta(hd->getLocalAtual(), pos);
			pos = hd->criaArquivo(nome, ed.conteudo);
			e = hd->addPasta(hd->getLocalAtual(), pos);
			cout << e.status <<"\n Antes: " << conteudo << " -- Depois: " << ed.conteudo << "\n\n";
		}
	}
	else{
		e.mensagem = "Selecone um HD\n";
		e.status = true;
	}
}

void Comandos::help(){
	t = separar(getParametros());
	cout << "Ajuda do parametro " << t.t1 << endl;
}

void Comandos::skol()
{
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------:://///::----:::::-------:::::----::////::--------::::::----------------------------------------------\n---------------------------------------------:+oooooooooo+--/ooooo/----/oooo+:-/+oooooooooo+:-----oooooo----------------------------------------------\n--------------------------------------------+oooo/----:/o:--+ooooo:--/ooooo:-/ooooo+++ooooooo+---:ooooo+----------------------------------------------\n-------------------------------------------/ooooo/----------ooooo+-:ooooo/-:ooo+:------:oooooo+--/ooooo:----------------------------------------------\n-------------------------------------------:ooooooo/-------/ooooo/+oooo/--:oo+----------:oooooo--ooooo+-----------------------------------------------\n--------------------------------------------/oooooooo+:----oooooooooo+----+o/-----------:oooooo-/ooooo/-----------------------------------------------\n----------------------------------------------/+ooooooo+--:ooooooooooo/---oo--------::-:oooooo/-oooooo------------------------------------------------\n------------------------------------------------:/oooooo:-+ooooo:+ooooo/--+/------/oo:+oooooo+-:ooooo/------------------------------------------------\n------------------------------------------//------+ooooo::ooooo+--+ooooo/--/---:+ooooooooooo/--+ooooo----::/:-----------------------------------------\n------------------------------------------ooo/:::/ooooo/-+ooooo:---+ooooo+---/oooooooooooo/---:oooooooooooo/------------------------------------------\n-----------------------------------------/ooooooooooo+:-/oooooo-----/oooooo:-:+ooooooo+/:-----+ooooooooooo/-------------------------------------------\n--------------------------------------------:::::::-------------------://///:---:+oooo/---------------------------------------------------------------\n------------------------------------------------------------------------------------:::/--------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void Comandos::fei()
{
	printf("           `.:/++ooooooooooooooo++/:-`           `-:/+ooooooooooooooo++/:.`            `-:/++oooo+/. \n       .:ossssssssssssssssssssssssssso/-    `-+ssssssssssssssssssssssssssso/.      -/osssssssssssss/\n     -ossssssssssssssssssssssssssssssssso:./ssssssssssssssssssssssssssssssssso: `/ssssssssssssssssss\n   .osssssssso/:----------------/+sssssssssssssssso/:---------------:/+ssssssssosssssssss+/:-/ssssss\n  :sssssss+-`                      ./ssssssssss+-`                      ./ssssssssssss:.     -ssssss\n /ssssss+.                           `/sssssso.                           `/ssssssss:        -ssssss\n-ssssss/                               :ssss/                               :ssssss.         -ssssss\nossssso                                 +sso                                 +ssss-          -ssssss\nssssss:                                 -ss:                                 -ssss           -ssssss\nssssss-           sssssssssssssssssssssssss-           ossssssssssssssssssssssssss           -ssssss\nssssss-           ossssssssssssssssssssssss-           +ooooooosssssssssssssssssss           -ssssss\nssssss-                    ``.:+sssssssssss-                     `-/ssssssssssssss           -ssssss\nssssss-                         `:sssssssss-                         -osssssssssss           -ssssss\nssssss-                           `/sssssss-                           /ssssssssss           -ssssss\nssssss-                             /ssssss-                            /sssssssss           -ssssss\nssssss-                             `ssssss-                            `sssssssss           -ssssss\nssssss-           -------------------osssss-           ::::::::::::::::::sssssssss           -ssssss\nssssss-           sssssssssssssssssssssssss-           ossssssssssssssssssssssssss           -ssssss\nssssss-           sssssssssssssssssssssssss-           ossssssssssssssssssssssssss           -ssssss\nssssss-           sssssssoooooooooooossssss-           ossssssssssssssssssssssssss           -ssssss\nssssss-           ssssss:           `ssssss:           `````````````..:/osssssssss           :ssssss\nssssss-          .ssssss.            ossssso                             ./sssssss           +ssssso\nssssss-         `osssss+             -ssssss/                              .osssss          :ssssss:\nssssss-        -sssssss`              +ssssss+`                             `+ssss        `/ssssss+ \nssssss-     `-+sssssso.                +sssssss/.                            `ssss      `/sssssss+` \nssssss:..-:+ssssssss+`                  :sssssssso/:.........................`osss`.-:/ossssssss:   \nssssssssssssssssss+.                     `/sssssssssssssssssssssssssssssssssssssssssssssssssss/`    \n+sssssssssssssso:`                         `-+sssssssssssssssssssssssssssssssssssssssssssss+-`      \n :+sssssso+/:-`                                .-/+oosssssssssssssssssssssssssssssssso+/-.          \n");
}
