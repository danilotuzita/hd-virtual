#include "includes.h"

using namespace std;

int main(){

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
	

	system("pause");
	//system("bomdia.txt");
	return 0;
}

