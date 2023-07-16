#include <iostream>

#include "Integer.h"
#include "Fraction.h"
#include "Series.hpp"
#include "Imaginary.h"

int main(){
	std::cout << "calculating" << std::endl;
	{
		const Natural a(123, 10);
		std::cout << "a:" << a.GetStringRadix(10) << std::endl;
		std::cout << "a:" << a.GetStringRadix(2) << std::endl;
		std::cout << "a:" << a.GetStringRadix(16) << std::endl;
		const Natural b(456, 10);
		std::cout << "b:" << b << std::endl;
		std::cout << "a+b:" << a + b << std::endl;
		const Natural c("100", 10);
		std::cout << "c:" << c.GetStringRadix(2).c_str() << std::endl;
		const Natural d("10000000000000000000000000000000000000000000000000", 10);
		const Natural e("3", 10);
		const Natural &f = d / e;
		std::cout << "d / e:" << f << std::endl;
		std::cout << "f:" << f * e << std::endl;
		std::cout << "d % e:" << d % e << std::endl;
	}
	{
		const Integer a(Natural("1"), false);
		const Integer b(Natural("10000000000000000000000000000000000000000000000000"));
		std::cout << "a + b:" << a + b << std::endl;
	}
	{
		const Fraction a(Natural("1"), Natural("3"));
		const Integer b(Natural(3, 10));
		std::cout << "a, b = " << a << "," << b << std::endl;
		std::cout << "a + b = " << a + b << std::endl;
		std::cout << "b + a = " << b + a << std::endl;
		std::cout << "a - b = " << a - b << std::endl;
		std::cout << "a = " << a.GetDecimal(10, 100) << std::endl;
		std::cout << "a = " << a.GetDecimal(2, 10) << std::endl;
		std::cout << "1 / 30 = " << Fraction(Natural("1"), Natural("30")).GetDecimalRadix(10, 10) << std::endl;
		std::cout << "3 / 1 = " << Fraction(Natural("3"), Natural("1")).GetDecimalRadix(10, 10) << std::endl;
		std::cout << "5 / 4 = " << Fraction(Natural("5"), Natural("4")).GetDecimalRadix(10, 10) << std::endl;
		std::cout << "0 / 1 = " << Fraction(Natural("0"), Natural("1")).GetDecimalRadix(10, 10) << std::endl;
		std::cout << Fraction(Natural("123456789")).SetPointPos(0).GetDecimalRadix(10, 10) << std::endl;
		std::cout << Fraction(Natural("123456789")).SetPointPos(18).GetDecimalRadix(10, 32) << std::endl;
		Fraction c(Natural("999999"));
		c.SetPointPos(6);
		std::cout << "c = " << c.GetDecimal(10, 10) << std::endl;
		std::cout << "c = " << c.GetDecimal(10, 5) << std::endl;
		std::cout << "c = " << c.GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
		Fraction d(Natural("888888"));
		d.SetPointPos(6);
		std::cout << "d = " << d.GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
	}
	{
		std::cout << "e = " << Series<Fraction>(
			[](const uint64_t index) {
			return Fraction(Natural(1, 10), !Integer(index - 1));
		}).Summation(20).GetMonomial().GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << "2^256=" << Integer(2).Power(Integer(256)).GetStringRadix(10) << std::endl;
	}
	{
		std::cout << Natural("39135395").Root(Natural(5, 10)).GetString() << std::endl;
		std::cout << Natural("10000000000000000000000000000000000").Root(Natural(2, 10)).GetString() << std::endl;
		std::cout << Natural("100000000000000000000000000000000000").Root(Natural(2, 10)).GetString() << std::endl;
		std::cout << Natural("10010101010010100010100011", 2).Root(Natural(5, 2)).GetString() << std::endl;
		std::cout << Natural("25528A3", 16).Root(Natural(5, 16)).GetString() << std::endl;
	}
	{
		std::cout << Integer(2).Power(Integer(0)).GetStringRadix(10) << std::endl;
		std::cout << Integer(3, false).Power(Integer(3, false)) << std::endl;
		std::cout << Imaginary(Integer(1)) << std::endl;
		std::cout << Integer(4, false).Root(Integer(2)) << std::endl;
		std::cout << Integer(8, false).Root(Integer(3)) << std::endl;
		std::cout << Fraction(1, 3).Power(Fraction(1, 3)) << std::endl;
	}
	{
		std::cout << Imaginary(Integer(1)) + Imaginary(Integer(2)) << std::endl;
		std::cout << Imaginary(Integer(1)) - Imaginary(Integer(2)) << std::endl;
		std::cout << Imaginary(Integer(1)) * Imaginary(Integer(2)) << std::endl;
		std::cout << Imaginary(Integer(1)) / Imaginary(Integer(2)) << std::endl;

		std::cout << Imaginary(Fraction(1, 2)) + Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << Imaginary(Fraction(1, 2)) - Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << Imaginary(Fraction(1, 2)) * Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << Imaginary(Fraction(1, 2)) / Imaginary(Fraction(1, 3)) << std::endl;

		std::cout << (Imaginary(Fraction(1, 2)) + Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Imaginary(Fraction(1, 2)) - Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Imaginary(Fraction(1, 2)) * Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Imaginary(Fraction(1, 2)) / Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
	}
	{
		std::cout << Complex(Integer(1), Integer(1)) + Complex(Integer(1), Integer(2)) << std::endl;
		std::cout << Complex(Integer(1), Integer(1)) - Complex(Integer(1), Integer(2)) << std::endl;
		std::cout << Complex(Integer(1), Integer(1)) * Complex(Integer(1), Integer(2)) << std::endl;
		std::cout << Complex(Integer(1), Integer(1)) / Complex(Integer(1), Integer(2)) << std::endl;

		std::cout << Complex(Fraction(1, 2), Fraction(1, 3)) + Complex(Fraction(1, 2), Fraction(1, 3)) << std::endl;
		std::cout << Complex(Fraction(1, 2), Fraction(1, 3)) - Complex(Fraction(1, 2), Fraction(1, 3)) << std::endl;
		std::cout << Complex(Fraction(1, 2), Fraction(1, 3)) * Complex(Fraction(1, 2), Fraction(1, 3)) << std::endl;
		std::cout << Complex(Fraction(1, 2), Fraction(1, 3)) / Complex(Fraction(1, 2), Fraction(1, 3)) << std::endl;

		std::cout << (Complex(Fraction(1, 2), Fraction(1, 3)) + Complex(Fraction(1, 2), Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Complex(Fraction(1, 2), Fraction(1, 3)) - Complex(Fraction(1, 2), Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Complex(Fraction(1, 2), Fraction(1, 3)) * Complex(Fraction(1, 2), Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (Complex(Fraction(1, 2), Fraction(1, 3)) / Complex(Fraction(1, 2), Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
	}
	getchar();
	return 0;
}
