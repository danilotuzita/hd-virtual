#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

char Util::getChar(bitset<1024> b, int byte)
{
	int bitS = byte * 8;
	char ret = 0;
	for(int i = bitS; i < bitS + 8; i++)
		ret += b[i] * pow(2, i);

	return ret;
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

std::string Util::itos(int number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

void Util::printHex(bitset<8> b)
{
	cout<<setw(2)<<hex<<(int)getChar(b)<<" ";
}

void Util::printChar(bitset<8> b)
{
	char c = getChar(b);
	if(c > 31 || c == 20 || c == 0)
		cout<<setw(2)<<c<<" ";	
	else
		cout<<setw(2)<<(int)c<<" ";
}

//#include "Util.h"
//
//Util::Util()
//{
//}
//
//Util::~Util()
//{
//}
//
//char Util::getChar(bitset<1024> b, int byte)
//{
//	int bitS = byte * 8;
//	char ret = 0;
//	for(int i = bitS; i < bitS + 8; i++)
//		ret += b[i] * pow(2, i);
//
//	return ret;
//}
//
//char Util::getChar(bitset<8> b)
//{
//	char ret = 0;
//	for(int i = 0; i < 8; i++)
//		ret += b[i] * pow(2, i);
//		
//	return ret;
//}
//
//void Util::formatByte(int byte, bitset<8> b)
//{
//	if(byte < 10)
//		cout<<"BYTE 00"<<byte<<": ";
//	else if(byte < 100)
//		cout<<"BYTE 0"<<byte<<": ";
//	else
//		cout<<"BYTE "<<byte<<": ";
//	
//	for(int i = 0; i < 8; i++)
//		cout<<b[i];
//	
//	char c = getChar(b);
//	
//	if(c < 10)
//		cout<<" | DEC:   "<<(int)c<<" - CHAR: "<<c<<endl;
//	else if(c == 10)
//		cout<<" | DEC:   "<<(int)c<<" - CHAR: \\n"<<endl;
//	else if(c < 100)
//		cout<<" | DEC:  "<<(int)c<<" - CHAR: "<<c<<endl;
//	else
//		cout<<" | DEC: "<<(int)c<<" - CHAR: "<<c<<endl;
//}
//
//std::string Util::itos(int number)
//{
//     std::ostringstream ss;
//     ss << number;
//     return ss.str();
//}
//
//
//string Util::itob(int num)
//{
//	stringstream ss;
//
//	// the number is converted to string with the help of stringstream
//	ss << num;
//	string ret;
//	ss >> ret;
//
//	// Append zero chars
//	int str_length = ret.length();
//	for (int i = 0; i < 4 - str_length; i++)
//		ret = "0" + ret;
//	return ret;
//}
