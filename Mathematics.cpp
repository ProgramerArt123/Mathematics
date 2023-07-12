#include <iostream>

#include "Integer.h"
#include "Fraction.h"
#include "Series.hpp"
#include "Imaginary.h"

int main(){
	std::cout << "calculating" << std::endl;
	{
		const NDecimal a(123, 10);
		std::cout << "a:" << a.GetStringBase(10) << std::endl;
		std::cout << "a:" << a.GetStringBase(2) << std::endl;
		std::cout << "a:" << a.GetStringBase(16) << std::endl;
		const NDecimal b(456, 10);
		std::cout << "b:" << b << std::endl;
		std::cout << "a+b:" << a + b << std::endl;
		const NDecimal c("100", 10);
		std::cout << "c:" << c.GetStringBase(2).c_str() << std::endl;
		const NDecimal d("10000000000000000000000000000000000000000000000000", 10);
		const NDecimal e("3", 10);
		const NDecimal &f = d / e;
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
		const Integer b(NDecimal(3, 10));
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
			return Fraction(NDecimal(1, 10), !Integer(index - 1));
		}).Summation(20).GetMonomial().GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << "2^256=" << Integer(2).Power(Integer(256)).GetStringBase(10) << std::endl;
	}
	{
		std::cout << NDecimal("39135395").Root(NDecimal(5, 10)).GetString() << std::endl;
		std::cout << NDecimal("10000000000000000000000000000000000").Root(NDecimal(2, 10)).GetString() << std::endl;
		std::cout << NDecimal("100000000000000000000000000000000000").Root(NDecimal(2, 10)).GetString() << std::endl;
		std::cout << NDecimal("10010101010010100010100011", 2).Root(NDecimal(5, 2)).GetString() << std::endl;
		std::cout << NDecimal("25528A3", 16).Root(NDecimal(5, 16)).GetString() << std::endl;
	}
	{
		std::cout << Integer(2).Power(Integer(0)).GetStringBase(10) << std::endl;
		std::cout << Integer(3, false).Power(Integer(3, false)) << std::endl;
		std::cout << Imaginary(Integer(1)) << std::endl;
		std::cout << Integer(4, false).Root(Integer(2)) << std::endl;
		std::cout << Integer(8, false).Root(Integer(3)) << std::endl;
	}
	getchar();
	return 0;
}
