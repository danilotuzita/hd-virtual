#include <cstdlib>
#include <iostream>
#include "comandos/Comandos.h"

using namespace std;

int main(){

	Comandos c;
	
	//c.setComando("cat > a");
	//c.validarComando();

	c.setComando("      cate > a");
	c.validarComando(1);
	
	cout << endl << "Comando completo: " << c.getComandoCompleto()
		 << endl << "Comando: " << c.getComando()
		 << endl << "Parametros: " << c.getParametros();

	return 0;
}
