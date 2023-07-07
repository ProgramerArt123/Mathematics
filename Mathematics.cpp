#include <iostream>

#include "BitSet.h"
#include "Integer.h"
#include "Fraction.h"
#include "Series.hpp"

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
		const Integer a(NDecimal("1"), false);
		const Integer b(NDecimal("10000000000000000000000000000000000000000000000000"));
		std::cout << "a + b:" << a + b << std::endl;
	}
	{
		const Fraction a(NDecimal("1"), NDecimal("3"));
		const Integer b(NDecimal(3));
		std::cout << "a, b = " << a << "," << b << std::endl;
		std::cout << "a + b = " << a + b << std::endl;
		std::cout << "b + a = " << b + a << std::endl;
		std::cout << "a - b = " << a - b << std::endl;
		std::cout << "a = " << a.GetDecimal(10, 100) << std::endl;
		std::cout << "a = " << a.GetDecimal(2, 10) << std::endl;
		std::cout << "1 / 30 = " << Fraction(NDecimal("1"), NDecimal("30")).GetDecimal(10, 10) << std::endl;
		std::cout << "3 / 1 = " << Fraction(NDecimal("3"), NDecimal("1")).GetDecimal(10, 10) << std::endl;
		std::cout << "5 / 4 = " << Fraction(NDecimal("5"), NDecimal("4")).GetDecimal(10, 10) << std::endl;
		std::cout << "0 / 1 = " << Fraction(NDecimal("0"), NDecimal("1")).GetDecimal(10, 10) << std::endl;
		std::cout << Fraction(NDecimal("123456789")).SetPointPos(0).GetDecimal(10, 10) << std::endl;
		std::cout << Fraction(NDecimal("123456789")).SetPointPos(18).GetDecimal(10, 32) << std::endl;
		Fraction c(NDecimal("999999"));
		c.SetPointPos(6);
		std::cout << "c = " << c.GetDecimal(10, 10) << std::endl;
		std::cout << "c = " << c.GetDecimal(10, 5) << std::endl;
		std::cout << "c = " << c.GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
		Fraction d(NDecimal("888888"));
		d.SetPointPos(6);
		std::cout << "d = " << d.GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
	}
	{
		std::cout << "e = " << Series<Fraction>(
			[](const uint64_t index) {
			return Fraction(NDecimal(1), !Integer(index - 1));
		}).Summation(20).GetMonomial().GetDecimal(10, 20) << std::endl;
	}
	getchar();
	return 0;
}
