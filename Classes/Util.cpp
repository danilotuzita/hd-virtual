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

bool Util::compString(const char * str1, const char * str2){
	int i = 0;
	bool ret = false;
	for(i = 0; str1[i] != 0 && str2[i] != 0 && str1[i] == str2[i]; i++);
	if(str1[i] == 0 && str2[i] == 0) ret = true;
	else if(str1[i] != 0 && str2[i] == 0 || str1[i] == 0 && str2[i] != 0 || str1[i] != 0 && str2[i] != 0) ret = false;
	return ret;
	
}

bool Util::verificaExtensao(char * str){
	int i;
	string ext = ""; 
	for(i = 0; str[i] != 0; i++);
	for(int j = i - 1; j >= i - 3; j--){
		ext = str[j] + ext;
	}
	if(ext == ".hd") return true;
	else return false;
}

void Util::listaHDS(){
    DIR           *dirp;
    struct dirent *directory;

    dirp = opendir(".");
    if (dirp)
    {
        while ((directory = readdir(dirp)) != NULL)
        {
		  if(verificaExtensao(directory->d_name)){
			cout << directory->d_name;
		  }
        }

        closedir(dirp);
    }
}

bool Util::hdExiste(string nome){

    if (FILE *file = fopen(nome.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   

}

string Util::trim(string entrada)
{
	string retorno = "";
	for(int i = 0; entrada[i]; i++)
		retorno += entrada[i];
	return retorno;
}

