#include <iostream>

#include "BitSet.h"

int main(){
	std::cout << "calculating" << std::endl;
	const BitSet a(123);
	std::cout << "a:" << a.GetString(10).c_str() << std::endl;
	std::cout << "a:" << a.GetString(2).c_str() << std::endl;
	std::cout << "a:" << a.GetString(16).c_str() << std::endl;
	const BitSet b(456);
	std::cout << "b:" << b << std::endl;
	std::cout << "a+b:" << a + b << std::endl;
	const BitSet c("100", 10);
	std::cout << "c:" << c.GetString(2).c_str() << std::endl;
	getchar();
	return 0;
}
