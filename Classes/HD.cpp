#include "HD.h"
#include "Util.h"

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
	string s = u.itos(TAM);
	base.setDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO, s);
	hd[POS_HEADER] = base;
}

void HD::propriedadesHD(string * mensagem){

	mensagem[0] = "Nome: " + hd[POS_HEADER].getDados(BYTE_HEADER_NOME, SIZE_HEADER_NOME);
	int temp_tam = (atoi(hd[POS_HEADER].getDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO).c_str()) * MAX_BYTE) / 1024;
	mensagem[1] = "Tamanho: " + u.itos(temp_tam) + "kb";

}

// TERMINAR
erro HD::openHD(string nomeHD){

	erro e;
	e.status = false;
	e.mensagem.clear();
	
	nomeHD += ".hd";
	
	fp = fopen (nomeHD.c_str(), "wb");
	
	
	if (fp==NULL) {
		e.status = true;
		e.mensagem = "Nao foi possivel abrir o HD selecionado";
	}
}
