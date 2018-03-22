#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

char Util::getChar(bitset<8> b)
{
	char ret = 0;
	for(int i = 0; i < 8; i++)
		ret += b[i] * pow(2, i);
		
	return ret;
}

void Util::formatByte(int byte, bitset<8> b)
{
	if(byte < 10)
		cout<<"BYTE 00"<<byte<<": ";
	else if(byte < 100)
		cout<<"BYTE 0"<<byte<<": ";
	else
		cout<<"BYTE "<<byte<<": ";
	
	for(int i = 0; i < 8; i++)
		cout<<b[i];
	
	char c = getChar(b);
	
	if(c < 10)
		cout<<" | DEC:   "<<(int)c<<" - CHAR: "<<c<<endl;
	else if(c == 10)
		cout<<" | DEC:   "<<(int)c<<" - CHAR: \\n"<<endl;
	else if(c < 100)
		cout<<" | DEC:  "<<(int)c<<" - CHAR: "<<c<<endl;
	else
		cout<<" | DEC: "<<(int)c<<" - CHAR: "<<c<<endl;
}



