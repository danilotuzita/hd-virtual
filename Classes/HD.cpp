#include "HD.h"

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
			string temp = hd[i].getString(0, MAX_BYTE);
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
	TAM = (t * _1KB) / MAX_BYTE;
	
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
	base.setString(BYTE_HEADER_NOME, SIZE_HEADER_NOME, nome);
	base.setInt(BYTE_HEADER_TAMANHO, TAM);
	hd[POS_HEADER] = base;
}

void HD::raizHD(){
	localAtual = criaPasta("c:");
	cout << "Local atual: " << localAtual << endl; 
}

void HD::propriedadesHD(string * mensagem){

	Util u; 
	mensagem[0] = "Nome: " + hd[POS_HEADER].getString(BYTE_HEADER_NOME, SIZE_HEADER_NOME);
	mensagem[1] = "Tamanho: " + u.itos((int)hd[POS_HEADER].getInt(BYTE_HEADER_TAMANHO)) + "kb";

}

erro HD::openHD(string nomeHD){

 	erro e;
	e.status = false;
	e.mensagem.clear();

    //cout<<"abrindo: "<<nomeHD<<endl;

	nome = nomeHD;

	nomeHD += ".hd";

	//cout<<"abrindo: "<<nomeHD<<endl;

	fp = fopen(nomeHD.c_str(), "rb");

	if (fp==NULL) {
		e.status = true;
		e.mensagem = "Nao foi possivel abrir o HD selecionado";
		return e;
	}

	carregaHD();
	
	fclose(fp);
	fp = fopen(nomeHD.c_str(), "wb");

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

	TAM = bloco.getInt(BYTE_HEADER_TAMANHO);
	hd.resize(TAM);

	//bloco.setFlag(FLAG_OCUPADO, true);
	hd[0] = bloco;
	
	for(int j = 1; j < TAM; j++) //iterando os blocos
	{
        for(int i = 0; i < MAX_BYTE; i++) //lendo 1 Bloco
		{
			fread(&buffer, 1, 1, fp);
			bloco.setByte(i, buffer);
		}

		hd[j] = bloco;
		
		if(hd[j].isFree() && ultimoBlocoLivre == 0)
		{
            ultimoBlocoLivre = j;
		}
		else if(!hd[j].isFree() && ultimoBlocoLivre == (j - 1) && (j - 1) != 0)
		{
            blocosLivres.push(ultimoBlocoLivre);
            ultimoBlocoLivre = 0;
		}
	}
	
	return e;
}

int HD::getFreeBlock()
{
	int i;
	
	if(blocosLivres.empty())
		if(ultimoBlocoLivre > TAM)
			return -1;
		else
			return ultimoBlocoLivre++;

	i = blocosLivres.front();
	blocosLivres.pop();
	return i;
}

int HD::criaArquivo(string nome, string dados)
{
	int i = getFreeBlock();
	int primeiroBloco = i;
	if(i == -1)
			return -1; // HD ESTÁ SEM ESPAÇO
	
	//cout<<NOME_SIZE + DADOS_SIZE<<": ";
	while(dados.size())
	{
		if(nome.size())
		{
			hd[i].setNome(nome);
			hd[i].setFlag(FLAG_NOME, true);
			nome = "";
		}
		
		hd[i].setFlag(FLAG_OCUPADO, true);
		hd[i].setFlag(FLAG_TIPO, TIPO_ARQUIVO);
		dados = hd[i].setDados(dados);
		
		int next = getFreeBlock();
		if(next == -1)
			return -1; // HD ESTÁ SEM ESPAÇO
		
		hd[i].setMemoria(next); // o bloco atual aponta para o proximo bloco livre
		i = next;
	}
	//cout<<endl;
	
	return primeiroBloco;
}

string HD::leArquivo(unsigned int pos)
{
	if(pos > TAM || !hd[pos].temNome() || hd[pos].isFree())
		return "";
	
	string retorno = "";
	
	int next = pos;
	do
	{
		retorno += hd[next].getDados();
		next = hd[next].getMemoria();
	}while(next);
	
	return retorno;
}

int HD::criaPasta(string nome)
{
	int i = getFreeBlock();
	if(i == -1)
		return -1;
	
	hd[i].setFlag(FLAG_NOME, true);
	hd[i].setFlag(FLAG_OCUPADO, true);
	hd[i].setFlag(FLAG_TIPO, TIPO_PASTA);
	hd[i].setNome(nome);
	
	return i;
}

void HD::addPasta(unsigned int pai, unsigned int filho)
{
	if(hd[pai].isFolder())
		hd[pai].setInt(hd[pai].getFreeSpace(), filho);
}

queue<unsigned int> HD::abrePasta(unsigned int pai)
{
	queue<unsigned int> pastas;
	
	do
	{
		int i;
		if(hd[pai].temNome())
			i = DADOS_BYTE;
		else
			i = NOME_BYTE;
		
		for(; i < MAX_BYTE; i += 4)
		{
			unsigned int temp = hd[pai].getInt(i);
			if(temp)
				pastas.push(temp);
		}
		
		pai = hd[pai].getInt(MP_BYTE);
	}while(hd[pai].getMemoria() && pai);
	
	return pastas;
}

void HD::print(int bloco)
{
	hd[bloco].printAll();
}

void HD::printChain(int pos)
{
	if(pos > TAM || !hd[pos].temNome() || hd[pos].isFree())
		return ;
	
	int next = pos;
	do
	{
		hd[next].printBloco();
		cout<<endl;
		next = hd[next].getMemoria();
	}while(next);
}

string HD::getNome(unsigned int pos)
{
	return hd[pos].getNome();
}

bool HD::getTipo(unsigned int pos)
{
	return hd[pos].isFolder();
}

int HD::getLocalAtual(){
	return localAtual;
}

void HD::setLocalAtual(unsigned int pos){
	localAtual = pos;
}
