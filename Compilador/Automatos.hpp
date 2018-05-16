bool e0();
bool e1();
bool e2();
bool e3();
bool e4();
bool e5();
bool e6();
bool e7();
bool e8();
bool e9();
bool e10();
bool e11();
bool e12();
bool e13();
bool e14();
bool e15();
bool e16();
bool e17();
bool e18();
bool e19();
bool e20();
bool e21();
bool e22();
bool e23();
bool e24();
bool e25();
bool e26();
bool e27();
bool e28();
bool e29();
bool e30();
bool e31();
bool e32();
bool e33();
bool e34();
bool e35();
bool e36();
bool e37();
bool e38();

bool c0();
bool c1();
bool c2();
bool f0();

int n = 0;
string c;
// AUTOMATOS

bool e0(){
	int m = 0;
	n++;

	if(c[m] != 0){
		if(c[m] == 'c') return e1();
		else if(c[m] == '?') return e6();
		else if(c[m] == 'r') return e8();
		else if(c[m] == 'd') return e12();
		else if(c[m] == 'l') return e13();
		else if(c[m] == 'f') return e14();
		else if(c[m] == 'm') return e18();
		else if(c[m] == 'e') return e20();
		else if(c[m] == 't') return e27();
		else if(c[m] == 's') return e32();
		else return false;
	}
	else{
		return true;
	}
}

bool e1(){
	int m = n;
	n++;
	if(c[m] == 'r') return e2();
	else if(c[m] == 'a') return e7();
	else if(c[m] == 'd') return e6();
	else if(c[m] == 'l') return e22();
	else if(c[m] == 'o') return e36();
	else return false;
}

bool e2(){
	int m = n;
	n++;
	if(c[m] == 'e') return e3();
	else return false;
}

bool e3(){
	int m = n;
	n++;
	if(c[m] == 'a') return e4();
	else return false;
}

bool e4(){
	int m = n;
	n++;
	if(c[m] == 't') return e5();
	else return false;
}

bool e5(){
	int m = n;
	n++;
	if(c[m] == 'e') return e6();
	else return false;
}

bool e6(){
	if(c[n] == '\0') return true;
	else return false;
}

bool e7(){
	int m = n;
	n++;
	if(c[m] == 't') return e6();
	else return false;
}

bool e8(){
	int m = n;
	n++;
	if(c[m] == 'e') return e9();
	else return false;
}

bool e9(){
	int m = n;
	n++;
	if(c[m] == 'm') return e10();
	else if(c[m] == 'n') return e25();
	else return false;
}

bool e10(){
	int m = n;
	n++;
	if(c[m] == 'o') return e11();
	else return false;
}

bool e11(){
	int m = n;
	n++;
	if(c[m] == 'v') return e5();
	else return false;
}

bool e12(){
	int m = n;
	n++;
	if(c[m] == 'f') return e6();
	else return false;
}

bool e13(){
	int m = n;
	n++;
	if(c[m] == 's') return e6();
	else return false;
}

bool e14(){
	int m = n;
	n++;
	if(c[m] == 'o') return e15();
	else if(c[m] == 'e') return e35();
	else return false;
}

bool e15(){
	int m = n;
	n++;
	if(c[m] == 'r') return e16();
	else return false;
}

bool e16(){
	int m = n;
	n++;
	if(c[m] == 'm') return e17();
	else return false;
}

bool e17(){
	int m = n;
	n++;
	if(c[m] == 'a') return e7();
	else return false;
}

bool e18(){
	int m = n;
	n++;
	if(c[m] == 'o') return e19();
	else return false;
}

bool e19(){
	int m = n;
	n++;
	if(c[m] == 'v') return e5();
	else return false;
}

bool e20(){
	int m = n;
	n++;
	if(c[m] == 'x') return e21();
	else if(c[m] == 'd') return e38();
	else return false;
}

bool e21(){
	int m = n;
	n++;
	if(c[m] == 'i') return e7();
	else return false;
}

bool e22(){
	int m = n;
	n++;
	if(c[m] == 'e') return e23();
	else return false;
}

bool e23(){
	int m = n;
	n++;
	if(c[m] == 'a') return e24();
	else return false;
}

bool e24(){
	int m = n;
	n++;
	if(c[m] == 'r') return e6();
	else return false;
}

bool e25(){
	int m = n;
	n++;
	if(c[m] == 'a') return e26();
	else return false;
}

bool e26(){
	int m = n;
	n++;
	if(c[m] == 'm') return e5();
	else return false;
}

bool e27(){
	int m = n;
	n++;
	if(c[m] == 'y') return e28();
	else return false;
}

bool e28(){
	int m = n;
	n++;
	if(c[m] == 'p') return e29();
	else return false;
}

bool e29(){
	int m = n;
	n++;
	if(c[m] == 'e') return e30();
	else return false;
}

bool e30(){
	int m = n;
	n++;
	if(c[m] == 'h') return e31();
	else return false;
}

bool e31(){
	int m = n;
	n++;
	if(c[m] == 'd') return e6();
	else return false;
}

bool e32()
{
	int m = n;
	n++;
	if(c[m] == 'k') return e33();
	else return false;
}

bool e33()
{
	int m = n;
	n++;
	if(c[m] == 'o') return e34();
	else return false;
}

bool e34()
{
	int m = n;
	n++;
	if(c[m] == 'l') return e6();
	else return false;
}

bool e35()
{
	int m = n;
	n++;
	if(c[m] == 'i') return e6();
	else return false;
}

bool e36(){
	int m = n;
	n++;
	if(c[m] == 'p') return e37();
	else return false;
}

bool e37(){
	int m = n;
	n++;
	if(c[m] == 'y') return e6();
	else return false;
}

bool e38(){
	int m = n;
	n++;
	if(c[m] == 'i') return e7();
	else return false;
}

// AUTOMATO CREATE

bool c0(){
	int m = 0;
	n++;

	if(c[m] != 0){
		if(c[m] == '-'){
			n++;
			m++;
			if(c[m] == 'h') return c1();
			else if(c[m] == 'f') return c2();
			else if(c[m] == 'd') return c2();
			else if(c[m] == 'u') return c2();
			else return false;
		}
		else if(c[m] == '?') return c2();
		else return false;
	}
	else{
		return false;
	}
}

bool c1(){
	int m = n;
	n++;
	if(c[m] == 'd') return c2();
	else return false;
}

bool c2(){
	if(c[n] == '\0') return true;
	else return false;
}

bool f0(){
	return c == "-hd" ? true : false;
}
