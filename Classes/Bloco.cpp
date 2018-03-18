#include "Bloco.h"

Bloco::Bloco()
{
//	for(int i = 0; i < MAX_BIT; i++)
//		setBit(i , false);
	omitBWar = false;
	omitBErr = false;
	
	omitWar = false;
	omitErr = false;
}

Bloco::~Bloco()
{
}

// ============= UTILS ============= //
void Bloco::printByte(int byte)
{
	if(byte >= MAX_BYTE)
		return;
	Util u;
	bitset<8> bs;
	
	for(int i = 0; i < 8; i++)
		bs[i] = getBit(byte * 8 + i);
	
	u.formatByte(byte, bs);
}

void Bloco::printRange(int sByte, int steps)
{
	for(int i = sByte; i < sByte + steps; i++)
		printByte(i);
}

void Bloco::printAll()
{
	
	for(int byte = 0; byte < MAX_BYTE; byte++)
	{
		if(byte == 4 || byte == 5 || byte == 32)
			cout<<"--------\n";
		
		printByte(byte);
	}
}


// ============= BIT ============= //
bool Bloco::setBit(int bit, bool value)
{
	if(bit >= MAX_BIT)
	{
		if(omitBErr == false)
			cout<<"ERRO(Bloco.setBit: IMPOSSIVEL ACESSAR O BIT "<<bit;
		return false;
	}
	b[bit] = value;
	return true;
}

bool Bloco::getBit(int bit)
{
	if(bit >= MAX_BIT)
	{
		if(omitBErr == false)
			cout<<"ERRO(Bloco.setBit: IMPOSSIVEL ACESSAR O BIT "<<bit<<"!!!\n";
		return false;
	}
	return b[bit];
}


// ============= BYTE ============= //
void Bloco::setByte(int byte, char value)
{
	bool bit;
	int byte_bit = byte * 8;
	
	for(int i = 0; i < 8; i++)
	{
		bit = value % 2;
		value /= 2;
		if(setBit(byte_bit + i, bit) == false)
		{
			cout<<" - BYTE: "<<byte<<endl;
			break;	
		}
	}
}

bitset<8> Bloco::getByte(int byte)
{
	bitset<8> ret;
	int bit = byte * 8;
	
	for(int i = 0; i < 8; i++)
		ret[i] = getBit(bit + i);
		
	return ret;
}


// ============= NOME ============= //
void Bloco::setNome(const char* n)
{
	string s = n;
	setDados(NOME_BYTE, NOME_SIZE, s);
}

string Bloco::getNome()
{
	string ret = getDados(NOME_BYTE, NOME_SIZE);
	return ret;
}

void Bloco::getNome(char ret[NOME_SIZE])
{
	string str = getDados(NOME_BYTE, NOME_SIZE);
	strcpy(ret, str.c_str());
}


// ============= DADOS ============= //
void Bloco::setDados(int byte, const string value)
{
	int maxByte = byte + value.length();
	if(maxByte > 127)
	{
		if(omitWar == false)
			cout<<"ERRO(Bloco.setDados): IMPOSSIVEL SETAR ESSE VALOR NAS POSICOES "<<byte<<" a "<<maxByte<<" - OVERFLOW BYTE MAXIMO: "<<MAX_BYTE - 1<<"\n";
		return;
	}
	

	for(int i = 0; i < maxByte; i++)
		if(i < value.length())
			setByte(byte++, value[i]);
	setByte(byte, 0);
}

void Bloco::setDados(int byte, int maxSteps, string value) // maxSteps deve considerar o \0 (ex: nome pode ter até 26 caracteres, maxSteps = 27)
{
	if(value.length() > maxSteps - 1 && omitWar == false) // length não considera o \0
		cout<<"AVISO(Bloco.setDados): TAMANHO DA STRING E MAIOR QUE O maxSteps("<<maxSteps<<"), A STRING '"<<value<<"'SERA CORTADA\n";
		
	value.resize(maxSteps - 1); // resize não considera o \0
	setDados(byte, value);
}

void Bloco::setDados(string value)
{
	setDados(DADOS_BYTE, DADOS_SIZE, value);
}

string Bloco::getDados(int byte, int steps)
{
	Util u;
	
	string ret;
	ret.resize(steps);
	
	for(int i = 0; i < steps; i++)
	{
		bitset<8> bs = getByte(byte + i);
		ret[i] = u.getChar(bs);
	}
	ret[steps] = 0;
	return ret;
}

string Bloco::getDados()
{
	return getDados(DADOS_BYTE, DADOS_SIZE);
}












