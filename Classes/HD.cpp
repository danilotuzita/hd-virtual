#include "HD.h"
#include "Util.h"

HD::HD()
{
	ultimoBlocoLivre = 0;
	localAtual = POS_RAIZ;
}

HD::~HD()
{
	//cout<<"fechando arq"<<endl;
	if (fp != NULL) {
	    for(int i = 0; i < TAM; i++){
			string temp = hd[i].getDados(0, MAX_BYTE);
			fwrite(temp.c_str(), MAX_BYTE, 1, fp);
		}
	
		fclose(fp);
	}
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
    raizHD();
    
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

void HD::raizHD(){

	Bloco raiz;

	raiz.setMemoria(0);

	raiz.setFlag(FLAG_OCUPADO, true);
	raiz.setFlag(FLAG_NOME, true);
	raiz.setFlag(FLAG_TIPO, true);

	char nome[27] = "c:";
	raiz.setNome(nome);
	
	raiz.setAreaDados("");
	
	hd[POS_RAIZ] = raiz;
}

void HD::propriedadesHD(string * mensagem){

	mensagem[0] = "Nome: " + hd[POS_HEADER].getDados(BYTE_HEADER_NOME, SIZE_HEADER_NOME);
	int temp_tam = (atoi(hd[POS_HEADER].getDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO).c_str()) * MAX_BYTE) / 1024;
	mensagem[1] = "Tamanho: " + u.itos(temp_tam) + "kb";

}

erro HD::openHD(string nomeHD){

 	erro e;
	e.status = false;
	e.mensagem.clear();

    //cout<<"abrindo: "<<nomeHD<<endl;

	nome = nomeHD;

	nomeHD += ".hd";

	//cout<<"abrindo: "<<nomeHD<<endl;

	fp = fopen (nomeHD.c_str(), "rb");

	if (fp==NULL) {
		e.status = true;
		e.mensagem = "Nao foi possivel abrir o HD selecionado";
		return e;
	}

	carregaHD();
	
	fclose(fp);
	fp = fopen (nomeHD.c_str(), "wb");

	return e;
	
}

erro HD::carregaHD(){

    erro e;
    Util u;
	char buffer;
	Bloco bloco;
    hd.clear();

	for(int i = 0; i < MAX_BYTE; i++)
	{
		fread (&buffer, 1, 1, fp);
		bloco.setByte(i, buffer);
	}

	TAM = atoi(bloco.getDados(BYTE_HEADER_TAMANHO, SIZE_HEADER_TAMANHO).c_str());
	hd.resize(TAM);

	bloco.setFlag(FLAG_OCUPADO, true);
	hd[0] = bloco;
	
	for(int j = 1; j < TAM; j++) //iterando os blocos
	{
        for(int i = 0; i < MAX_BYTE; i++) //lendo 1 Bloco
		{
			fread (&buffer, 1, 1, fp);
			bloco.setByte(i, buffer);
		}

		hd[j] = bloco;
		
		if(!hd[j].getFlag(FLAG_OCUPADO) && ultimoBlocoLivre == 0)
		{
            ultimoBlocoLivre = j;
		}
		else if(hd[j].getFlag(FLAG_OCUPADO) && ultimoBlocoLivre == (j - 1) && (j - 1) != 0)
		{
            blocosLivres.push(ultimoBlocoLivre);
            ultimoBlocoLivre = 0;
		}
	}
	
	return e;
}

erro HD::criarArquivo(string nome, string conteudo){
	return criarConteudo(nome, conteudo, false);
}

erro HD::criarPasta(string nome){
	return criarConteudo(nome, "", true);
}

erro HD::criarConteudo(string nome, string conteudo, bool tipo){

	erro e;
	Util u;

	e.status = false;
	e.mensagem.clear();
	
	int pos;
	int prox = ultimoBlocoLivre;

	if(blocosLivres.empty())
	{
		pos = ultimoBlocoLivre;
		prox++;
	} 
	else
	{
        pos = blocosLivres.front();
        blocosLivres.pop();
	}

    hd[pos].setMemoria(0);
    
    hd[pos].setFlag(FLAG_OCUPADO, true);
	hd[pos].setFlag(FLAG_NOME, true);
	hd[pos].setFlag(FLAG_TIPO, tipo);
	
	hd[pos].setNome(nome.c_str());
	
	hd[pos].setAreaDados(conteudo);

	string areaDados = hd[localAtual].getAreaDados();

	int i;
	for(i = 0; areaDados[i] != 0; i++);
	areaDados.resize(i);

    areaDados += u.itob(pos);

    hd[localAtual].setAreaDados(areaDados);

    ultimoBlocoLivre = prox;

	return e;
}
