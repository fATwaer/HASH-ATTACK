#include "MD5.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/* after the transform string "abcd" , the text should be "0xe2fc714c44727ee9395f324cd2e7f331f" */ 

int main(int argc, char** argv) {
	std::cout << "0x" <<md5("abcd") << std::endl; 
	return 0;
}
