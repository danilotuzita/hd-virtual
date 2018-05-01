#include "HD.h"

HD::HD()
{
	ultimoBlocoLivre = POS_RAIZ;
	localAtual = POS_RAIZ;
}

HD::~HD()
{
	fp = fopen((nome + ".hd").c_str(), "wb");
	salvaHD();
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
	salvaHD();
	return e;
}

void HD::headHD(){
	Bloco base;
	base.setString(BYTE_HEADER_NOME, SIZE_HEADER_NOME, nome);
	base.setInt(BYTE_HEADER_TAMANHO, TAM);
	hd[POS_HEADER] = base;
}

void HD::raizHD(){
	hd[POS_RAIZ].setFlag(FLAG_NOME, true);
	hd[POS_RAIZ].setFlag(FLAG_OCUPADO, true);
	hd[POS_RAIZ].setFlag(FLAG_TIPO, TIPO_PASTA);
	hd[POS_RAIZ].setNome((nome + ":"));
	ultimoBlocoLivre = POS_RAIZ + 1;
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
	
	return e;
}

void HD::salvaHD(){
	if (fp != NULL) {
	    for(int i = 0; i < TAM; i++){
	    	string temp = hd[i].getString(0, MAX_BYTE);
			fwrite(temp.c_str(), MAX_BYTE, 1, fp);
		}

		fclose(fp);
	}
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

	hd[0] = bloco;
	
	for(int j = POS_RAIZ; j < TAM; j++) //iterando os blocos
	{
        for(int i = 0; i < MAX_BYTE; i++) //lendo 1 Bloco
		{
			fread(&buffer, 1, 1, fp);
			bloco.setByte(i, buffer);
		}

		hd[j] = bloco;
		
		if(hd[j].isFree() && ultimoBlocoLivre == POS_RAIZ)
            ultimoBlocoLivre = j;
		else if(!hd[j].isFree() && ultimoBlocoLivre == (j - 1) && (j - 1) != POS_RAIZ)
		{
            blocosLivres.push(ultimoBlocoLivre);
            ultimoBlocoLivre = POS_RAIZ;
		}
	}
	
	return e;
}

unsi HD::getFreeBlock()
{
	unsi i;
	
	if(blocosLivres.empty())
		if(ultimoBlocoLivre >= TAM)
			return 0;
		else
			return ultimoBlocoLivre++;		

	i = blocosLivres.front();
	blocosLivres.pop();
	return i;
}

int HD::validaNome(unsigned int pai, unsigned int filho)
{
	queue<unsigned int> filhos = abrePasta(pai);
	
	bool tipo = getTipo(filho);
	string nome = getNome(filho);
	
	while(!filhos.empty())
	{
		unsigned int i = filhos.front();
		filhos.pop();
		
		if(getTipo(i) == tipo)
			if(getNome(i) == nome)
				return 0; // já existe um arquivo com esse nome
				
		if(i == filho)
			return -1;    // o arquivo já é filho dessa pasta
	}
	
	return 1;             // o arquivo pode ser linkado a essa pasta
}

int HD::validaNome(unsigned int pai, bool tipo, string nome)
{
	queue<unsigned int> filhos = abrePasta(pai);
	
	nome.resize(NOME_SIZE);
	
	while(!filhos.empty())
	{
		unsigned int i = filhos.front();
		filhos.pop();
		
		if(getTipo(i) == tipo)
			if(getNome(i) == nome)
				return 0; // já existe um arquivo com esse nome			
	}
	
	return 1;             // o arquivo pode ser linkado a essa pasta
}

void HD::deleta(unsigned int pai, unsigned int filho)
{
	if(!getUndo()) // ctrlz == 0
	{
		setUndo(pai);
		deletaRef(pai, filho);
		
		while(!desfaz.empty())
			desfaz.pop();
	}
	deleta(filho);
}

void HD::deleta(unsigned int bloco)
{
	desfaz.push(bloco);
	if(getTipo(bloco) == TIPO_PASTA)
		deletaPasta(bloco);
	else
		deletaArquivo(bloco);
	
	recalEspacosLivres();
}

void HD::deletaRef(unsigned int bloco, unsigned int ref)
{
	if(bloco > TAM || !hd[bloco].temNome() || hd[bloco].isFree())
		return;
	
	while(bloco)
	{
		int i = hd[bloco].handleBytePos();
			
		for(; i < MAX_BYTE; i += 4)
		{
			if(ref == hd[bloco].getInt(i))
			{
				hd[bloco].setInt(i, 0);
				return;
			}
		}
		
		bloco = hd[bloco].getMemoria();
	}
}

erro HD::undo()
{
	erro e;
	e.status = true;
	e.mensagem = "Nao e possivel desfazer a remocao";	
	
	if(!ctrlz)
		return e;
	
	int bloco;
	while(!desfaz.empty())
	{
		bloco = desfaz.front();
		desfaz.pop();
		if(ctrlz)
		{
			addPasta(ctrlz, bloco);
			setUndo(0); // ctrlz = 0
		}	
		
		hd[bloco].setFlag(FLAG_OCUPADO, true);
	}
	
	recalEspacosLivres();
	
	e.status = false;
	return e;	
}

void HD::setUndo(unsi value)
{
	ctrlz = value;
}

unsi HD::getUndo()
{
	return ctrlz;
}

unsi HD::copy(unsigned int bloco)
{
	if(getTipo(bloco) == TIPO_PASTA)
		return copiaPasta(bloco);
	return copiaArquivo(bloco);
}

unsi HD::copiaPasta(unsigned int bloco)
{
	queue<unsi> pasta = abrePasta(bloco);
	unsi raiz = criaPasta(getNome(bloco));
	
	while(!pasta.empty())
	{
		addPasta(raiz, copy(pasta.front()));
		pasta.pop();
	}
	return raiz;
}

unsi HD::copiaArquivo(unsigned int bloco)
{
	return criaArquivo(getNome(bloco), leArquivo(bloco));
}

unsi HD::criaArquivo(string nome, string dados)
{
	unsi i = getFreeBlock();
	hd[i].clearDados();
	
	unsi primeiroBloco = i;
	if(i == -1)
		return -1; // HD ESTA SEM ESPACO
	
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
		
		if(dados.size())
		{
			unsi next = getFreeBlock();
			if(next == -1)
			{	
				deletaArquivo(primeiroBloco);
				return -1; // HD ESTA SEM ESPACO
			}
			
			hd[i].setMemoria(next); // o bloco atual aponta para o proximo bloco livre
			i = next;
		}
	}
	
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

void HD::deletaArquivo(unsigned int bloco)
{
	if(bloco > TAM || !hd[bloco].temNome() || hd[bloco].isFree() || hd[bloco].isFolder())
		return;
	
	while(bloco)
	{
		int next = hd[bloco].getMemoria();
		hd[bloco].desocupa();
		bloco = next;
	}
}

unsi HD::criaPasta(string nome)
{
	unsi i = getFreeBlock();
	if(!i)
		return i;
	
	hd[i].clearDados();
	hd[i].setFlag(FLAG_NOME, true);
	hd[i].setFlag(FLAG_OCUPADO, true);
	hd[i].setFlag(FLAG_TIPO, TIPO_PASTA);
	hd[i].setNome(nome);
	
	return i;
}

unsi HD::criaPasta()
{
	unsi i = getFreeBlock();
	if(!i)
		return 0;
	
	hd[i].clearDados();
	hd[i].setFlag(FLAG_NOME, false);
	hd[i].setFlag(FLAG_OCUPADO, true);
	hd[i].setFlag(FLAG_TIPO, TIPO_PASTA);
	
	return i;
}

erro HD::addPasta(unsigned int pai, unsigned int filho)
{
	erro e;
	e.status = false;
	e.mensagem = "";
	switch(validaNome(pai, filho))
	{
		case -1:
			e.mensagem = "Arquivo/Pasta ja esta na pasta";
			e.status = true;
			return e;
			
		case  0: // já existe um aquivo com esse nome
			deleta(filho);
			e.mensagem = "Ja existe um aquivo/pasta com esse nome";
			e.status = true;
			return e;
	}
	
	if(hd[pai].isFolder())
	{
		while(hd[pai].getMemoria())      // vai para o ultimo link
			pai = hd[pai].getMemoria();
		
		int pos = hd[pai].getFreeSpace();
		if(pos == -1)
		{
			hd[pai].setMemoria(criaPasta());
			pai = hd[pai].getMemoria();
			pos = hd[pai].getFreeSpace();
		}
		
		hd[pai].setInt(pos, filho);
	}
	return e;
}

queue<unsigned int> HD::abrePasta(unsigned int pai)
{
	queue<unsigned int> pastas;
	
	do
	{
		int i = hd[pai].handleBytePos();
		
		for(i; i < MAX_BYTE; i += 4)
		{
			unsigned int temp = hd[pai].getInt(i);
			if(temp)
				pastas.push(temp);
		}
		
		pai = hd[pai].getMemoria();
	}while(pai);
	
	return pastas;
}

void HD::deletaPasta(unsigned int bloco)
{
	if(bloco > TAM || !hd[bloco].temNome() || hd[bloco].isFree() || !hd[bloco].isFolder())
		return;
	
	while(bloco)
	{
		int byte = hd[bloco].handleBytePos();
		
		for(; byte < MAX_BYTE; byte += 4)
		{
			int filho = hd[bloco].getInt(byte);
			if(filho)
				deleta(bloco, filho);
		}
		
		hd[bloco].desocupa();
		bloco = hd[bloco].getMemoria();
	}
}

erro HD::renomear(unsigned int pai, unsigned int bloco, string novoNome){
	erro e;
	e.status = false;
	e.mensagem = "";
	switch(validaNome(pai, getTipo(bloco), novoNome))
	{
		case 0: // já existe um aquivo com esse nome
			e.mensagem = "Ja existe um aquivo/pasta com esse nome";
			e.status = true;
			break;
			
		case 1:
			hd[bloco].setNome(novoNome);
			break;
	}
	
	return e;
}

int HD::localizaObjeto(unsigned int pai, string filho, bool tipo){
	
	unsigned int pos;
	
	queue<unsigned int> pasta = abrePasta(pai);
	
	while(!pasta.empty()){
		
		pos = pasta.front();
		if(getTipo(pos) == tipo)
			if(filho == getNome(pos))
				return pos;
				
		pasta.pop();
	}
	
	return 0;
}

void HD::recalEspacosLivres(){
	
	ultimoBlocoLivre = POS_RAIZ;
	
	while (!blocosLivres.empty())  blocosLivres.pop();
	
	for(int j = POS_RAIZ; j < TAM; j++) //iterando os blocos
	{
		if(hd[j].isFree() && ultimoBlocoLivre == POS_RAIZ)
		{
            ultimoBlocoLivre = j;
		}
		else if(!hd[j].isFree() && ultimoBlocoLivre == (j - 1) && (j - 1) != POS_RAIZ)
		{
            blocosLivres.push(ultimoBlocoLivre);
            ultimoBlocoLivre = POS_RAIZ;
		}
	}
}

// UTIL
void HD::propriedadesHD(string * mensagem){
	Util u; 
	mensagem[0] = "Nome: " + hd[POS_HEADER].getString(BYTE_HEADER_NOME, SIZE_HEADER_NOME);
	mensagem[1] = "Tamanho: " + u.itos((int)hd[POS_HEADER].getInt(BYTE_HEADER_TAMANHO)) + "kb";
}

unsi HD::getTamanho(){
	return TAM;
}

// prints
void HD::print(int bloco)
{
	hd[bloco].printAll();
}

void HD::printChain(int pos)
{
	if(pos > TAM || !hd[pos].temNome() || hd[pos].isFree())
		return;
	
	int next = pos;
	do
	{
		hd[next].printBloco();
		cout<<endl;
		next = hd[next].getMemoria();
	}while(next);
}

void HD::printHD(bool tipo)
{
	for(int i = 1; i < TAM; i++)
	{
		if(!hd[i].isFree() && hd[i].temNome())
		{
			cout<<"BLOCO "<<i<<": \n";
			printChain(i);
		}
	}
}

void HD::printHD()
{
	for(int i = 1; i < TAM; i++)
	{
		if(!hd[i].isFree())
		{
			cout<<"BLOCO "<<i<<": \n";
			hd[i].printBloco();
			cout<<endl;
		}
	}
}

// get
string HD::getNome(unsigned int pos)
{
	return u.trim(hd[pos].getNome());
}

bool HD::getTipo(unsigned int pos)
{
	return hd[pos].isFolder();
}

// posicoes
unsi HD::getLocalAtual(){
	return localAtual;
}

void HD::setLocalAtual(unsigned int pos){
	localAtual = pos;
}


