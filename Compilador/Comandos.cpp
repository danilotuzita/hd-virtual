<<<<<<< cd50def45a1fdbf34c56f53a80a297d7c037898a
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
=======
#include <cstdlib>
#include <string>
#include <iostream>
#include "Comandos.h"
#include "../Classes/Util.h"

using namespace std;

bool e0();
bool e1();
bool e2();
bool e3();
bool e4();
bool e5();
bool e6();
bool e7();
bool e8();
bool e9();
bool e10();
bool e11();
bool e12();
bool e13();
bool e14();
bool e15();
bool e16();
bool e17();
bool e18();
bool e19();
bool e20();
bool e21();
bool c0();
bool c1();
bool c2();
bool f0();

int n = 0;
string c;

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
	erro e;
	
	e.status = false;
	e.mensagem = "";
	
	split t;
	t.t1 = "";
	t.t2 = "";
	
	if(e0()){
		if(getComando() == "create"){
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
					else cout << "Criar um hd com o nome: " << t.t2 << endl;
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
		else if(getComando() == "remove"){
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
		else if(getComando() == "format"){
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
 		else if(getComando() == "cat"){
			cout << "Ler conteudo do arquivo: " << getParametros();
		}
 		else if(getComando() == "cd"){
			cout << "Ir para: " << getParametros();
		}
		else if(getComando() == "move"){
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
		else if(getComando() == "ls"){
			t = separar(getParametros());
			if(t.t1 == "-h"){
				cout << "Listar HD'S \n";
			}
			else {
				cout << "Listar pastas e arquivos\n";
			}
		}
 		else if(getComando() == "df"){
			cout << "Propriedade do hd\n";
		}
		else if(getComando() == "?"){
			t = separar(getParametros());
			cout << "Ajuda do parametro " << t.t1 << endl;
		}
	}
	else{
		e.status = true;
		for(int i = 0; i < n - 1; i++){
			e.mensagem += "_";
		}
		e.mensagem += "^";
	}
	
	return e;
}

// AUTOMATOS

bool e0(){
	int m = 0;
	n++;
	
	if(c[m] != 0){
		if(c[m] == 'c') return e1();
		else if(c[m] == '?') return e6();
		else if(c[m] == 'r') return e8();
		else if(c[m] == 'd') return e12();
		else if(c[m] == 'l') return e13();
		else if(c[m] == 'f') return e14();
		else if(c[m] == 'm') return e18();
		else if(c[m] == 'e') return e20();
		else return false;
	}
	else{
		return true;
	}
}

bool e1(){
	int m = n;
	n++;
	if(c[m] == 'r') return e2();	
	else if(c[m] == 'a') return e7();
	else if(c[m] == 'd') return e6();
	else return false;
}

bool e2(){
	int m = n;
	n++;
	if(c[m] == 'e') return e3();
	else return false;
}

bool e3(){
	int m = n;
	n++;
	if(c[m] == 'a') return e4();
	else return false;
}

bool e4(){
	int m = n;
	n++;
	if(c[m] == 't') return e5();
	else return false;
}

bool e5(){
	int m = n;
	n++;
	if(c[m] == 'e') return e6();
	else return false;
}

bool e6(){
	if(c[n] == '\0') return true;
	else return false;
}

bool e7(){
	int m = n;
	n++;
	if(c[m] == 't') return e6();
	else return false;
}

bool e8(){
	int m = n;
	n++;
	if(c[m] == 'e') return e9();
	else return false;
}

bool e9(){
	int m = n;
	n++;
	if(c[m] == 'm') return e10();
	else return false;
}

bool e10(){
	int m = n;
	n++;
	if(c[m] == 'o') return e11();
	else return false;
}

bool e11(){
	int m = n;
	n++;
	if(c[m] == 'v') return e5();
	else return false;
}

bool e12(){
	int m = n;
	n++;
	if(c[m] == 'f') return e6();
	else return false;
}

bool e13(){
	int m = n;
	n++;
	if(c[m] == 's') return e6();
	else return false;
}

bool e14(){
	int m = n;
	n++;
	if(c[m] == 'o') return e15();
	else return false;
}

bool e15(){
	int m = n;
	n++;
	if(c[m] == 'r') return e16();
	else return false;
}

bool e16(){
	int m = n;
	n++;
	if(c[m] == 'm') return e17();
	else return false;
}

bool e17(){
	int m = n;
	n++;
	if(c[m] == 'a') return e7();
	else return false;
}

bool e18(){
	int m = n;
	n++;
	if(c[m] == 'o') return e19();
	else return false;
}

bool e19(){
	int m = n;
	n++;
	if(c[m] == 'v') return e5();
	else return false;
}

bool e20(){
	int m = n;
	n++;
	if(c[m] == 'x') return e21();
	else return false;
}

bool e21(){
	int m = n;
	n++;
	if(c[m] == 'i') return e7();
	else return false;
}

// AUTOMATO CREATE

bool c0(){
	int m = 0;
	n++;

	if(c[m] != 0){
		if(c[m] == '-'){
			n++;
			m++;
			if(c[m] == 'h') return c1();
			else if(c[m] == 'f') return c2();
			else if(c[m] == 'd') return c2();
			else return false;
		}
		else if(c[m] == '?') return c2();
		else return false;
	}
	else{
		return false;
	}
}

bool c1(){
	int m = n;
	n++;
	if(c[m] == 'd') return c2();
	else return false;
}

bool c2(){
	if(c[n] == '\0') return true;
	else return false;
}

bool f0(){
	return c == "-hd" ? true : false;
}
>>>>>>> Detalhando comandos
