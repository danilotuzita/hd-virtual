#include <cstdlib>
#include <iostream>
#include "Comandos.h"
#include "Automatos.hpp"

using namespace std;

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

Comandos::Comandos(string _comando){
	setComando(_comando);
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
        hd.openHD(nomeHD);
	}
	else{
		if(e0()){
	        if(getComando() == "clear") system("cls");
			else if(getComando() == "create") create();
			else if(getComando() == "remove") remove();
			else if(getComando() == "format") format();
			else if(getComando() == "move") move();
			else if(getComando() == "df") df();
			else if(getComando() == "cat") cat();
	 		else if(getComando() == "cd") cd();
			else if(getComando() == "ls") ls();
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
	return nomeHD;
}

// Funções de comando

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
					e = hd.createHD(a.t1, atoi(a.t2.c_str()));
					if(!e.status){
						cout << "HD " << a.t1 << " criado com sucesso (tamanho: " << atoi(a.t2.c_str()) * MAX_BYTE << " bytes)" << endl;
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
			else cout << "Criar um arquivo com o nome: " << t.t2 << endl;
			
			
		}
		else if(t.t1 == "-d"){
	        if(t.t2 == ""){
				e.mensagem = "Informe o nome da pasta";
				e.status = true;
			}
			else cout << "Criar uma pasta com o nome: " << t.t2 << endl;
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

void Comandos::remove(){
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
			else cout << "Remover um hd com o nome: " << t.t2 << endl;
		}
		else if(t.t1 == "-f"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do arquivo";
				e.status = true;
			}
			else cout << "Remover um arquivo com o nome: " << t.t2 << endl;
		}
		else if(t.t1 == "-d"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome da pasta";
				e.status = true;
			}
			else cout << "Remover uma pasta com o nome: " << t.t2 << endl;
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
	if(f0()){
		if(t.t1 == "-hd"){
			if(t.t2 == ""){
				e.mensagem = "Informe o nome do hd";
				e.status = true;
			}
			else cout << "Formatar o hd com o nome: " << t.t2 << endl;
		}
		else{
			cout << "Comando para formatar bla bla bla bla \n";
		}
	}
	else {
		e.mensagem = "Parametro invalido para o formatar e bla bla bla bla\n";
		e.status = true;
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
	hd.propriedadesHD(mensagem);
	for(n = 0; n < 2; n++){
		cout << mensagem[n] << endl;
	}
}

void Comandos::cat(){
	cout << "Ler conteudo do arquivo: " << getParametros();
}

void Comandos::cd(){
	cout << "Ir para: " << getParametros();
}

void Comandos::ls(){
	t = separar(getParametros());
	if(t.t1 == "-h"){
		cout << "Listar HD'S \n";
	}
	else {
		cout << "Listar pastas e arquivos\n";
	}
}

void Comandos::help(){
	t = separar(getParametros());
	cout << "Ajuda do parametro " << t.t1 << endl;
}
