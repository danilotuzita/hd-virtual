#ifndef UTIL_H
#define UTIL_H

#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

class Util
{
	public:
		Util();
		~Util();
		char getChar(bitset<8>);
		void formatByte(int, bitset<8>);
	private:
};

#endif