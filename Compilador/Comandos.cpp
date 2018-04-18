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
	parametro.clear();
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
	        if(getComando() == "clear") system("cls");
			else if(getComando() == "create") create();
			else if(getComando() == "remove") remover();
			else if(getComando() == "format") format();
			else if(getComando() == "move") move();
			else if(getComando() == "df") df();
			else if(getComando() == "cat") cat();
	 		else if(getComando() == "cd") cd();
			else if(getComando() == "ls") ls();
			else if(getComando() == "rename") renomear();
			else if(getComando() == "typehd") typehd();
			else if(getComando() == "?") help();
		}
		else{
			e.status = true;
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
						cout << "HD " << a.t1 << " criado com sucesso (tamanho: " << atoi(a.t2.c_str()) * MAX_BYTE << " bytes)" << endl;
						hdSelecionado = true;
					} else {
						cout << "Erro: " << e.mensagem << endl;
					}
				}
			}
		}
		else if(t.t1 == "-f"){
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
                
				hd->addPasta(hd->getLocalAtual(), ret);
                
				if(ret != -1){
					cout << "Arquivo " << t.t2 << " gravado com sucesso!" << endl;
				} else {
					cout << "Erro: " << e.mensagem << endl;
				}
			}
		}
		else if(t.t1 == "-d"){
	        if(t.t2 == ""){
				e.mensagem = "Informe o nome da pasta";
				e.status = true;
			}
			else {
                
				int ret = hd->criaPasta(t.t2);
                hd->addPasta(hd->getLocalAtual(), ret);
				
				if(ret != -1){
					cout << "Pasta " << t.t2 << " criada com sucesso!" << endl;
				} else {
					cout << "Erro: " << e.mensagem << endl;
				}				
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
	
	int pos;

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
				pos = hd->localizaObjeto(hd->getLocalAtual(), t.t2, TIPO_ARQUIVO);
				if(pos){
					hd->deleta(hd->getLocalAtual(), pos);
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
		    	nomeHD = t.t1;
		    	
			    hdSelecionado = true;
				
			}
			else{
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
	if(t.t1 == ""){
		e.mensagem = "Informe os parametros de origem e destino\n";
		e.status = true;
	}
	else if(t.t2 == ""){
		e.mensagem = "Informe o parametro de destino\n";
		e.status = true;
	}
	else {
		cout << "Enviando arquivo de " << t.t1 << " para " << t.t2 << endl;
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
	
	if(getParametros() == ".."){
		if(trilha.size() != 0){
			trilha.pop_back();
			pos = trilha.size() == 0 ? POS_RAIZ : trilha.back();
			hd->setLocalAtual(pos);
			montaCaminho();
		}
	}
	else{
		pos = hd->localizaObjeto(hd->getLocalAtual(), getParametros(), TIPO_PASTA);
	
		if(!pos){
			cout << "\nPasta " << getParametros() << " nao encontrada" << endl;		
		} 
		else {
			//cout<<"LOCAL: "<<pos<<endl;
			hd->setLocalAtual(pos);
			trilha.push_back(pos);
			montaCaminho();
		}
	}
}

void Comandos::montaCaminho(){
	
	caminho.clear();
	
	if(trilha.size() != 0){
		for(int i = 0; i < trilha.size(); i++){
			caminho += "\\" + hd->getNome(trilha[i]);
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
		
		while(!pasta.empty())
		{
			pos = pasta.front();
			if(hd->getTipo(pos) == TIPO_PASTA) cout << "/";
			cout << hd->getNome(pos) << " | ";
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
		if(t.t1 == "-d"){
			pos = hd->localizaObjeto(hd->getLocalAtual(), nomes.t1, TIPO_PASTA);
			if(pos){
				hd->renomear(pos, nomes.t2);
				cout << "Pasta renomeada\n";
			}
			else {
				cout << "Pasta " << nomes.t1 << " nao encontrada\n";
			}
		}
		else if(t.t1 == "-f"){
			pos = hd->localizaObjeto(hd->getLocalAtual(), nomes.t1, TIPO_ARQUIVO);
			if(pos){
				hd->renomear(pos, nomes.t2);
				cout << "Arquivo renomeado\n";
			}
			else {
				cout << "Arquivo " << nomes.t1 << " nao encontrado\n";
			}
		}
		else {
			cout << "Informe corretamento o objeto a ser renomeado\n";
		}		
	}
		
}

void Comandos::typehd(){
	
	if(hdSelecionado){
		delete hd;
		nomeHD.clear();
	}
	if(u.hdExiste(getParametros() + ".hd")){

        hd = new HD;
        hd->openHD(getParametros());
        
    	nomeHD = getParametros();
    	
	    hd->printHD();
		
	}
	else{
		cout << "HD " << getParametros() << " nao encontrado" << endl;
	}
}

void Comandos::help(){
	t = separar(getParametros());
	cout << "Ajuda do parametro " << t.t1 << endl;
}
