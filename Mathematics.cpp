#include <iostream>

#include "BitSet.h"
#include "Integer.h"

int main(){
	std::cout << "calculating" << std::endl;
	{
		const BitSet a(123);
		std::cout << "a:" << a.GetString(10).c_str() << std::endl;
		std::cout << "a:" << a.GetString(2).c_str() << std::endl;
		std::cout << "a:" << a.GetString(16).c_str() << std::endl;
		const BitSet b(456);
		std::cout << "b:" << b << std::endl;
		std::cout << "a+b:" << a + b << std::endl;
		const BitSet c("100", 10);
		std::cout << "c:" << c.GetString(2).c_str() << std::endl;
		const BitSet d("10000000000000000000000000000000000000000000000000", 10);
		const BitSet e("3", 10);
		const BitSet &f = d / e;
		std::cout << "d / e:" << f << std::endl;
		std::cout << "f:" << f * e << std::endl;
		std::cout << "d % e:" << d % e << std::endl;
	}
	{
		const Integer a(BitSet("1"), false);
		const Integer b(BitSet("10000000000000000000000000000000000000000000000000"));
		std::cout << "a + b:" << a + b << std::endl;
	}
	getchar();
	return 0;
}
