#include <cstdlib>
#include <string>
#include <iostream>
#include "Comandos.h"

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

int n = 0;
string c;

void Comandos::separarComando(){
	
	int i;
	comandoCompleto = comando;
	
	for(i = 0; (int) comando[i] != 32 && (int) comando[i] != 0 ; i++) {
		c += comando[i];
	}
	
	for(; comando[i] != 0; i++){
		parametro += comando[i];
	}
	parametro = parametro;
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
	comando = _comando;
	removeEspacosComeco();
	separarComando();
}

Comandos::Comandos(string _comando): a(12){
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

bool Comandos::validarComando(int printar){
	
	bool ret;
	n = 0;
	if(e0()){
		ret = true;
	} 
	else {
		ret = false;
		if(printar){
			cout << endl << comandoCompleto << endl;
			for(int i = 0; i < n; i++){
				cout << "_";
			}
			cout << "^" << endl;
		}
	}
	
	return ret;
}


// AUTOMATOS

bool e0(){
	int m = 0;
	n++;
	
	if(c[m] != 0){
		if(c[m] == ' ') return e0();
		else if(c[m] == 'c') return e1();
		else if(c[m] == '?') return e6();
		else if(c[m] == 'r') return e8();
		else if(c[m] == 'd') return e12();
		else if(c[m] == 'l') return e13();
		else if(c[m] == 'f') return e14();
		else if(c[m] == 'm') return e18();
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

