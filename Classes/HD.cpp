#include "HD.h"

template <typename T>
std::string NumberToString ( T Number )
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}


HD::HD()
{
}

HD::~HD()
{
    for(int i = 0; i < TAM; i++){
		string temp = hd[i].getDados(0, MAX_BYTE);
		fwrite(temp.c_str(), MAX_BYTE, 1, fp);
	}

	fclose(fp);
}

erro HD::createHD(string n, int t)
{
	nome = n;
	n += ".hd";

	fp = fopen(n.c_str(), "wb");
	TAM = (t * 1024) / MAX_BYTE;
	
	erro e;
	e.status = true;
	e.mensagem = "ERRO CRIANDO O HD" + n;
	
	if(TAM > _128MB)
        return e;
        
	hd.resize(TAM);
	
	Bloco base;
	
	for(int i = 0; i < TAM; i++)
	    hd[i] = base;

    headHD();

	e.status = false;
	return e;
}

void HD::headHD(){
	Bloco base;
	base.setDados(BYTE_HEADER_NOME, SIZE_HEADER_NOME, nome);
	string s = NumberToString <int>(TAM);
	base.setDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO, s);
	hd[POS_HEADER] = base;
cout << 7;
}

void HD::propriedadesHD(){

	cout << "Nome: " << hd[POS_HEADER].getDados(BYTE_HEADER_NOME, SIZE_HEADER_NOME) << endl;
	int temp_tam = (atoi(hd[POS_HEADER].getDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO).c_str()) * MAX_BYTE) / 1024;
	cout << "Tamanho: " << temp_tam << "kb" << endl;

}


