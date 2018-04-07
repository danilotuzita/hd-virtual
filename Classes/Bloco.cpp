#include "Bloco.h"

Bloco::Bloco()
{
	bool cale_a_boca = true;
	omitBWar = cale_a_boca;
	omitBErr = false;
	
	omitWar = cale_a_boca;
	omitErr = false;
}

Bloco::~Bloco()
{
}

// UTILS
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
		if(byte == FLAG_BYTE || byte == NOME_BYTE || byte == DADOS_BYTE)
			cout<<"--------\n";
		
		printByte(byte);
	}
}

void Bloco::printBloco()
{
	Util u;
	cout<<"HEX: ";
	for(int byte = 0; byte < MAX_BYTE; byte++)
	{
		if(byte == FLAG_BYTE || byte == NOME_BYTE || (byte == DADOS_BYTE) && temNome())
			cout<<" | ";
		
		u.printHex(getByte(byte));
	}
	cout<<"\nCHR: ";
	for(int byte = 0; byte < MAX_BYTE; byte++)
	{
		if(byte == FLAG_BYTE || byte == NOME_BYTE || (byte == DADOS_BYTE) && temNome())
			cout<<" | ";

		u.printChar(getByte(byte));
	}
		
	cout<<endl;
}

// BIT
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


// BYTE
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


// DADOS
void Bloco::desocupa()
{
	setFlag(FLAG_OCUPADO, false);	
}

// STR
void Bloco::setString(int byte, const string value)
{
	int maxByte = byte + value.length();
	if(maxByte > MAX_BYTE)
	{
		if(omitWar == false)
			cout<<"ERRO(Bloco.setString): IMPOSSIVEL SETAR ESSE VALOR NAS POSICOES "<<byte<<" a "<<maxByte<<" - OVERFLOW BYTE MAXIMO: "<<MAX_BYTE - 1<<"\n";
		return;
	}
	

	for(int i = 0; i <= maxByte; i++)
		if(i < value.length())
			setByte(byte++, value[i]);
}

string Bloco::setString(int byte, int maxSteps, string value) // maxSteps deve considerar o \0 (ex: nome pode ter até 26 caracteres, maxSteps = 27)
{
	if(value.length() > maxSteps && omitWar == false) // length não considera o \0
		cout<<"AVISO(Bloco.setString): TAMANHO DA STRING E MAIOR QUE O TAMANHO PERMITIDO("<<maxSteps<<"), A STRING '"<<value<<"' SERA CORTADA\n";
	
	string ret = "";
	if(value.size() > maxSteps)
		ret = value.substr(maxSteps);
	
	value.resize(maxSteps); // resize não considera o \0
	setString(byte, value);
	return ret;
}

string Bloco::getString(int byte, int steps)
{
	Util u;
	
	string ret;
	
	for(int i = 0; i < steps; i++)
	{
		bitset<8> bs = getByte(byte + i);
		ret += u.getChar(bs);
	}
	ret[steps] = 0;
	return ret;
}

// INT
void Bloco::setInt(int byte, unsigned int value)
{
	for(int i = 0; i < MP_SIZE; i++)
	{
		int pot = pow(MAX_BIT, MP_SIZE - i - 1);
		setByte(i + byte, value / pot);
		value = value % pot;
	}
}

unsigned int Bloco::getInt(int byte)
{
	unsigned int ret = 0;
	int iterador = 0;
	Util u;
	for(int i = MP_SIZE - 1; i >= 0; i--)
	{
		int pot = pow(MAX_BIT, iterador);
		ret += u.getChar(getByte(i + byte)) * pot;
		iterador++;
	}
		
	return ret;
}

int Bloco::getFreeSpace()
{
	int i;
	if(temNome())
		i = DADOS_BYTE;
	else
		i = NOME_BYTE;

	for(i; i < MAX_BYTE; i += 4)
		if(getInt(i) == 0)
			return i;
}

// ----------------------------------------------// --- // ----------------------------------------------//

// MEMORIA
void Bloco::setMemoria(int value)
{
	setInt(MP_BYTE, value);
}

unsigned int Bloco::getMemoria()
{
	return getInt(MP_BYTE);
}


// FLAG
void Bloco::setFlag(int bit, bool value)
{
	if(bit < 7)
		setBit(FLAG_BIT + bit, value);
	else
	    if(omitErr == false)
	        cout<<"ERRO(Bloco.setFlag)\n";
}

bool Bloco::getFlag(int bit)
{
	if(bit < 7)
		return b[FLAG_BIT + bit];
	return false;
}

bool Bloco::isFree()
{
	return !getBit(FLAG_BIT + FLAG_OCUPADO);
}

bool Bloco::temNome()
{
	return getBit(FLAG_BIT + FLAG_NOME);
}

bool Bloco::isFolder()
{
	return getBit(FLAG_BIT + FLAG_TIPO);
}


//  NOME
void Bloco::setNome(string n)
{
	setString(NOME_BYTE, NOME_SIZE, n);
}

string Bloco::getNome()
{
	string ret = getString(NOME_BYTE, NOME_SIZE);
	return ret;
}

void Bloco::getNome(char ret[NOME_SIZE])
{
	string str = getString(NOME_BYTE, NOME_SIZE);
	strcpy(ret, str.c_str());
}


// DADOS
string Bloco::setDados(string value)
{
	if(temNome())
		return setString(DADOS_BYTE, DADOS_SIZE, value);
	return setString(NOME_BYTE, NOME_SIZE + DADOS_SIZE, value);
}

string Bloco::getDados()
{
	if(temNome())
		return getString(DADOS_BYTE, DADOS_SIZE);
	return getString(NOME_BYTE, NOME_SIZE + DADOS_SIZE);
}

