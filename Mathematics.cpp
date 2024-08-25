#include <iostream>

#define NUMBER_TEST
//#define EXPRESSION_TEST

#ifdef NUMBER_TEST
#include "number/Integer.h"
#include "number/Fraction.h"
#include "number/Imaginary.h"
#include "number/Root.h"
#include "number/Complex.h"
using namespace number;
#endif

#ifdef EXPRESSION_TEST
#include "expression/Series.hpp"
#include "expression/Expression.hpp"
#include "expression/ExpressionDeformationer.h"
using namespace expression;
#endif

int main() {
	std::cout << "calculating" << std::endl;
#ifdef NUMBER_TEST
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
		std::cout << "2^256=" << Fraction::Power(2, 256).GetStringRadix(10) << std::endl;
	}
	{
		std::cout << Natural("39135395").Root(Natural(5, 10)).first.GetString() << std::endl;
		std::cout << Natural("10000000000000000000000000000000000").Root(Natural(2, 10)).first.GetString() << std::endl;
		std::cout << Natural("100000000000000000000000000000000000").Root(Natural(2, 10)).first.GetString() << std::endl;
		std::cout << Natural("10010101010010100010100011", 2).Root(Natural(5, 2)).first.GetString() << std::endl;
		std::cout << Natural("25528A3", 16).Root(Natural(5, 16)).first.GetString() << std::endl;
	}
	{
		std::cout << Fraction::Power(2, 0).GetStringRadix(10) << std::endl;
		std::cout << Fraction::Power(Integer(3, false), (Integer(3, false))) << std::endl;
		std::cout << Imaginary(Integer(1)) << std::endl;
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
	{
		std::cout << number::Root(2, 2).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(20, 2).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(3, 3).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(30, 3).GetDecimal(10, 20) << std::endl;

		std::cout << number::Root(2, 2, false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(3, Integer(3, false), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(2, false), 2, false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(2, false), Integer(2, false), false).GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << number::Root(2, Fraction(2, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(20, Fraction(2, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(3, Fraction(3, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(30, Fraction(3, 5)).GetDecimal(10, 20) << std::endl;

		std::cout << number::Root(2, Fraction(2, 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(3, Fraction(Integer(3, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(2, false), Fraction(2, 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(2, false), Fraction(Integer(2, false), 5), false).GetDecimal(10, 20) << std::endl;

		std::cout << number::Root(Integer(3, false), Fraction(Integer(3, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(3, false), Fraction(Integer(2, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Integer(3, false), Fraction(Integer(3, false), 4), false).GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << number::Root(Fraction(1, 2), Fraction(2, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(1, 20), Fraction(2, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(1, 3), Fraction(3, 5)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(1, 30), Fraction(3, 5)).GetDecimal(10, 20) << std::endl;

		std::cout << number::Root(Fraction(1, 2), Fraction(2, 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(1, 3), Fraction(Integer(3, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(Integer(1, false), 2), Fraction(2, 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(Integer(1, false), 2), Fraction(Integer(2, false), 5), false).GetDecimal(10, 20) << std::endl;

		std::cout << number::Root(Fraction(Integer(1, false), 3), Fraction(Integer(3, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(Integer(1, false), 3), Fraction(Integer(2, false), 5), false).GetDecimal(10, 20) << std::endl;
		std::cout << number::Root(Fraction(Integer(1, false), 3), Fraction(Integer(3, false), 4), false).GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << Complex(Fraction(1, 2), Fraction(1, 2)).Power(2) << std::endl;
		std::cout << Complex(Fraction(1, 2), Fraction(1, 2)).Power(3) << std::endl;
		std::cout << Complex(Fraction(Integer(1, false), 2), Fraction(1, 2)).Power(3) << std::endl;
	}
	{
		std::cout << "10#2 ~ " << Natural(10).Logarithm(Natural(2)).first << std::endl;
		std::cout << "2#2 = " << Natural(2).Logarithm(Natural(2)).first << std::endl;
		std::cout << "16#2 = " << Natural(16).Logarithm(Natural(2)).first << std::endl;
		std::cout << "10#3 ~ " << Natural(10).Logarithm(Natural(3)).first << std::endl;
	}
#endif
#ifdef EXPRESSION_TEST
	{
		std::cout << "e = " << expression::Series<number::Fraction>(
			[](const uint64_t index) {
			return number::Fraction(number::Natural(1, 10), number::Natural(index - 1).Factorial());
		}).Summation(20).GetMonomial().GetDecimal(10, 20) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e(number::Integer(123), OPERATOR_TYPE_ADD(),
			number::Integer(456), OPERATOR_TYPE_SUB(), number::Integer(789));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e(number::Integer(123, false), OPERATOR_TYPE_ADD(),
			number::Integer(456), OPERATOR_TYPE_SUB(), number::Integer(789, false));

		std::cout << ExpressionDeformationer<OPERATOR_TYPE_0>(e.OutPutString()).Deformation(e) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e0(number::Integer(456), OPERATOR_TYPE_ADD(), number::Integer(789));
		expression::Expression<OPERATOR_TYPE_1> e1(number::Integer(123), OPERATOR_TYPE_MUL(), e0);
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e0(number::Integer(123), OPERATOR_TYPE_ADD(), number::Integer(456));
		expression::Expression<OPERATOR_TYPE_0> e1(number::Integer(789), OPERATOR_TYPE_SUB(), number::Integer(123));
		expression::Expression<OPERATOR_TYPE_1> e2(e0, OPERATOR_TYPE_MUL(), e1, OPERATOR_TYPE_DIV(), e0);
		e2.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_1> e(number::Integer(123), OPERATOR_TYPE_MUL(), number::Integer(456), OPERATOR_TYPE_DIV(), number::Integer(789));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e0(number::Integer(123), OPERATOR_TYPE_ADD(), number::Integer(456));
		expression::Expression<OPERATOR_TYPE_1> e1(e0, OPERATOR_TYPE_MUL(), number::Integer(789));
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e0(number::Integer(123), OPERATOR_TYPE_ADD(), number::Integer(456));
		expression::Expression<OPERATOR_TYPE_1> e1(number::Integer(789), OPERATOR_TYPE_MUL(), e0);
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_1> e0(number::Integer(123), OPERATOR_TYPE_MUL(), number::Integer(456));
		expression::Expression<OPERATOR_TYPE_0> e1(e0, OPERATOR_TYPE_ADD(), number::Integer(789));
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_1> e0(number::Integer(123), OPERATOR_TYPE_MUL(), number::Integer(456));
		expression::Expression<OPERATOR_TYPE_0> e1(e0, OPERATOR_TYPE_ADD(), e0);
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_1> e0(number::Integer(123), OPERATOR_TYPE_MUL(), number::Integer(456), OPERATOR_TYPE_DIV(), number::Integer(789));
		expression::Expression<OPERATOR_TYPE_0> e1(e0, OPERATOR_TYPE_ADD(), e0, OPERATOR_TYPE_SUB(), number::Integer(789));
		e1.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_ADD(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_SUB(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e(e0, OPERATOR_TYPE_MUL(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e(e0, OPERATOR_TYPE_DIV(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e1(e0, OPERATOR_TYPE_MUL(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_ADD(), e1);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, number::Integer(2), OPERATOR_TYPE_ADD(), e0, OPERATOR_TYPE_ADD(), number::Integer(123));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_SUB(), number::Integer(123), OPERATOR_TYPE_SUB(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(4), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(9), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_ADD(), e1);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_2> e2(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_ADD(), e1, OPERATOR_TYPE_ADD(), e2, OPERATOR_TYPE_ADD(), number::Integer(123));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2), OPERATOR_TYPE_POWER(), expression::ClosureNumber(2));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(3));
		expression::Expression<OPERATOR_TYPE_1> e(e0, OPERATOR_TYPE_MUL(), e1);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2), OPERATOR_TYPE_POWER(), expression::ClosureNumber(0));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_1> e0(number::Integer(5), OPERATOR_TYPE_DIV(), number::Integer(6));
		expression::Expression<OPERATOR_TYPE_2> e(number::Integer(2), OPERATOR_TYPE_ROOT(), e0);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_0> e(expression::Symbol("x"), OPERATOR_TYPE_ADD(), expression::Symbol("y"));
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(3));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(3), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e2(number::Integer(3), OPERATOR_TYPE_MUL(), e1);
		expression::Expression<OPERATOR_TYPE_2> e3(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e4(number::Integer(3), OPERATOR_TYPE_MUL(), e3);
		expression::Expression<OPERATOR_TYPE_2> e5(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(6));
		expression::Symbol s("x");
		expression::Expression<OPERATOR_TYPE_0> e(number::Integer(1), OPERATOR_TYPE_ADD(), e0, OPERATOR_TYPE_ADD(), e2, OPERATOR_TYPE_ADD(), e4, OPERATOR_TYPE_ADD(), e5, OPERATOR_TYPE_ADD(), s);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(5));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(3), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e2(number::Integer(3), OPERATOR_TYPE_MUL(), e1);
		expression::Expression<OPERATOR_TYPE_2> e3(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e4(number::Integer(3), OPERATOR_TYPE_MUL(), e3);
		expression::Expression<OPERATOR_TYPE_2> e5(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(6));
		expression::Symbol s("x");
		expression::Expression<OPERATOR_TYPE_1> e(number::Integer(1), OPERATOR_TYPE_MUL(), e0, OPERATOR_TYPE_MUL(), e2, OPERATOR_TYPE_MUL(), e4, OPERATOR_TYPE_MUL(), e5, OPERATOR_TYPE_MUL(), s);
		e.CollectForward(std::cout) << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(3));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(3), OPERATOR_TYPE_POWER(), number::Integer(2, false));
		expression::Expression<OPERATOR_TYPE_1> e2(number::Integer(3), OPERATOR_TYPE_DIV(), e1);
		expression::Expression<OPERATOR_TYPE_2> e3(number::Integer(8), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e4(number::Integer(3, false), OPERATOR_TYPE_MUL(), e3);
		expression::Expression<OPERATOR_TYPE_2> e5(number::Integer(8), OPERATOR_TYPE_POWER(), number::Integer(6));
		expression::Symbol s("x");
		expression::Expression<OPERATOR_TYPE_0> e(number::Integer(1), OPERATOR_TYPE_SUB(), e0, OPERATOR_TYPE_ADD(), e2, OPERATOR_TYPE_ADD(), e4, OPERATOR_TYPE_SUB(), e5, OPERATOR_TYPE_ADD(), s);
		e.CollectForward(std::cout) << std::endl;
	}
	
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(5, false));
		expression::Expression<OPERATOR_TYPE_2> e1(number::Integer(3), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e2(number::Integer(3, false), OPERATOR_TYPE_MUL(), e1);
		expression::Expression<OPERATOR_TYPE_2> e3(number::Integer(8), OPERATOR_TYPE_POWER(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e4(number::Integer(3), OPERATOR_TYPE_MUL(), e3);
		expression::Expression<OPERATOR_TYPE_2> e5(number::Integer(8, false), OPERATOR_TYPE_POWER(), number::Integer(6, false));
		expression::Symbol s("x");
		expression::Expression<OPERATOR_TYPE_1> e(number::Integer(1), OPERATOR_TYPE_MUL(), e0, OPERATOR_TYPE_DIV(), e2, OPERATOR_TYPE_MUL(), e4, OPERATOR_TYPE_MUL(), e5, OPERATOR_TYPE_MUL(), s);
		e.CollectForward(std::cout) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_2> e0(number::Integer(2), OPERATOR_TYPE_ROOT(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_1> e1(e0.GetOpposite(), OPERATOR_TYPE_MUL(), number::Integer(2));
		expression::Expression<OPERATOR_TYPE_0> e(e0, OPERATOR_TYPE_ADD(), e1);
		e.CollectForward(std::cout) << std::endl;
	}
#endif
	getchar();
	return 0;
}
