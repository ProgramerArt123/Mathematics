#include <iostream>

#define NUMBER_TEST
#define EXPRESSION_TEST_COLLECT
#define EXPRESSION_TEST_EXPAND
#define INF_TEST

#ifdef NUMBER_TEST
#include "number/Integer.h"
#include "number/Fraction.h"
#include "number/Imaginary.h"
#include "number/Root.h"
#include "number/Logarithm.h"
#include "number/Complex.h"
using namespace number;
#endif

#ifdef EXPRESSION_TEST_COLLECT
#include "expression/Series.hpp"
#include "expression/Expression.hpp"
#include "expression/ExpressionDeformationer.h"
#include "expression/Imaginary.h"
using namespace expression;
#endif

#ifdef EXPRESSION_TEST_EXPAND
#include "expression/Series.hpp"
#include "expression/Expression.hpp"
#include "expression/ExpressionDeformationer.h"
#include "expression/Imaginary.h"
using namespace expression;
#endif

#ifdef INF_TEST
#include "expression/Expression.hpp"
#include "inf/Infinitesimal.h"
#include "inf/Infinity.h"
using namespace inf;
#endif

int main() {
	std::cout << "calculating" << std::endl;
#ifdef NUMBER_TEST
	{
		const Natural a(123);
		std::cout << "a:" << a.GetStringRadix(10) << std::endl;
		std::cout << "a:" << a.GetStringRadix(2) << std::endl;
		std::cout << "a:" << a.GetStringRadix(16) << std::endl;
		const Natural b(456);
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
		const Integer b(Natural(3));
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
		std::cout << Fraction(Natural("123456789")).Point(0).GetDecimalRadix(10, 10) << std::endl;
		std::cout << Fraction(Natural("123456789")).Point(18).GetDecimalRadix(10, 32) << std::endl;
		Fraction c(Natural("999999"));
		std::cout << "c = " << c.Point(6).GetDecimal(10, 10) << std::endl;
		std::cout << "c = " << c.Point(6).GetDecimal(10, 5) << std::endl;
		std::cout << "c = " << c.Point(6).GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
		Fraction d(Natural("888888"));
		std::cout << "d = " << d.Point(6).GetDecimal(10, 5, [](char last) {return last >= '5'; }) << std::endl;
	}
	{
		std::cout << "2^256=" << Fraction::Power(2, 256).GetStringRadix(10) << std::endl;
	}
	{
		std::cout << Natural("39135395").Root(Natural(5)).first.GetString() << std::endl;
		std::cout << Natural("10000000000000000000000000000000000").Root(Natural(2)).first.GetString() << std::endl;
		std::cout << Natural("100000000000000000000000000000000000").Root(Natural(2)).first.GetString() << std::endl;
		std::cout << Natural("10010101010010100010100011", 2).Root(Natural(5)).first.GetString() << std::endl;
		std::cout << Natural("25528A3", 16).Root(Natural(5)).first.GetString() << std::endl;
	}
	{
		std::cout << Fraction::Power(2, 0).GetStringRadix(10) << std::endl;
		std::cout << Fraction::Power(Integer(3, false), (Integer(3, false))) << std::endl;
		std::cout << number::Imaginary(Integer(1)) << std::endl;
	}
	{
		std::cout << number::Imaginary(Integer(1)) + number::Imaginary(Integer(2)) << std::endl;
		std::cout << number::Imaginary(Integer(1)) - number::Imaginary(Integer(2)) << std::endl;
		std::cout << number::Imaginary(Integer(1)) * number::Imaginary(Integer(2)) << std::endl;
		std::cout << number::Imaginary(Integer(1)) / number::Imaginary(Integer(2)) << std::endl;

		std::cout << number::Imaginary(Fraction(1, 2)) + number::Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << number::Imaginary(Fraction(1, 2)) - number::Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << number::Imaginary(Fraction(1, 2)) * number::Imaginary(Fraction(1, 3)) << std::endl;
		std::cout << number::Imaginary(Fraction(1, 2)) / number::Imaginary(Fraction(1, 3)) << std::endl;

		std::cout << (number::Imaginary(Fraction(1, 2)) + number::Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (number::Imaginary(Fraction(1, 2)) - number::Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (number::Imaginary(Fraction(1, 2)) * number::Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
		std::cout << (number::Imaginary(Fraction(1, 2)) / number::Imaginary(Fraction(1, 3))).GetDecimalRadix(10, 2) << std::endl;
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
		std::cout << "8192#2 = " << Natural(8192).Logarithm(Natural(2)).first << std::endl;
		std::cout << "10000#10 = " << Natural(10000).Logarithm(Natural(10)).first << std::endl;
		std::cout << "10000#100 = " << Natural(10000).Logarithm(Natural(100)).first << std::endl;
	}
	{
		std::cout << number::Logarithm(Fraction(100000000000), Fraction(2)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Logarithm(Fraction(100000000000, 33), Fraction(3)).GetDecimal(10, 20) << std::endl;
		std::cout << number::Logarithm(Fraction(5, 27), Fraction(17, 7)).GetDecimal(10, 20) << std::endl;
	}
	{
		std::cout << number::Logarithm(Fraction(81), Fraction(36)).GetDecimal(10, 20) << std::endl;
	}
#endif
#ifdef EXPRESSION_TEST_COLLECT
	{
		std::cout << "e = " << expression::Series<number::Fraction>(
			[](const uint64_t index) {
			return number::Fraction(number::Natural(1), number::Natural(index - 1).Factorial());
		}).Approximation(20).GetMonomialAdd().GetDecimal(10, 20,
			[](char last) {return number::Natural::GetValue(last) >= LITERAL_DEFAULT_RADIX / 2; }) << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	//{
	//	expression::Expression<OPERATOR_TYPE_ADD_SUB> e(number::Integer(123, false), ADD,
	//		number::Integer(456), SUB, number::Integer(789, false));

	//	std::cout << ExpressionDeformationer<OPERATOR_TYPE_ADD_SUB>(e.OutPutString()).Deformation(e) << std::endl;
	//}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(456), ADD, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(number::Integer(123), MUL, e0);
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		try {
			expression::Expression<OPERATOR_TYPE_MUL_DIV> e(number::Integer(123), DIV, number::Integer(0));
			e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD, number::Integer(456));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(number::Integer(789), SUB, number::Integer(123));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(e0, MUL, e1, DIV, e0);
		e2.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(number::Integer(123), MUL, number::Integer(456), DIV, number::Integer(789));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD, number::Integer(456));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(e0, OPERATOR_TYPE_MUL(), number::Integer(789));
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD, number::Integer(456));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(number::Integer(789), MUL, e0);
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(number::Integer(123), MUL, number::Integer(456));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(e0, ADD, number::Integer(789));
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(number::Integer(123), MUL, number::Integer(456));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(e0, ADD, e0);
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(number::Integer(123), MUL, number::Integer(456), DIV, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(e0, ADD, e0, SUB, number::Integer(789));
		e1.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	
	{
		try {
			expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(0));
			expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e0);
			e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(e0, MUL, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, number::Integer(2), ADD, e0, ADD, number::Integer(123));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, number::Integer(123), SUB, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(4), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(9), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(8), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e2(number::Integer(8), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1, ADD, e2, ADD, number::Integer(123));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), ROOT, number::Integer(2), POWER, expression::ClosureNumber(2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(2), ROOT, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), ROOT, number::Integer(2), POWER, expression::ClosureNumber(0));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(number::Integer(5), DIV, number::Integer(6));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), ROOT, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_A, ADD, SYMBOL_B);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(number::Integer(3), MUL, e1);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e3(number::Integer(8), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e4(number::Integer(3), MUL, e3);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e5(number::Integer(8), ROOT, number::Integer(6));
		auto s = std::make_shared<Symbol>("x");
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(number::Integer(1), ADD, e0, ADD, e2, ADD, e4, ADD, e5, ADD, s);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(5));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(number::Integer(3), MUL, e1);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e3(number::Integer(8), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e4(number::Integer(3), MUL, e3);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e5(number::Integer(8), ROOT, number::Integer(6));
		auto s = std::make_shared<Symbol>("x");
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), MUL, e0, MUL, e2, MUL, e4, MUL, e5, MUL, s);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(3), POWER, number::Integer(2, false));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(number::Integer(3), DIV, e1);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e3(number::Integer(8), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e4(number::Integer(3, false), MUL, e3);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e5(number::Integer(8), POWER, number::Integer(6));
		auto s = std::make_shared<Symbol>("x");
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(number::Integer(1), SUB, e0, ADD, e2, ADD, e4, SUB, e5, ADD, s);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(5, false));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(number::Integer(3, false), MUL, e1);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e3(number::Integer(8), POWER, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e4(number::Integer(3), MUL, e3);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e5(number::Integer(8, false), POWER, number::Integer(6, false));
		auto s = std::make_shared<Symbol>("x");
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), MUL, e0, DIV, e2, MUL, e4, MUL, e5, MUL, s);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(2), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(e0.GetOpposite(), MUL, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(9), ROOT, number::Integer(6));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(number::Integer(9), LOGARITHM, number::Integer(3));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(number::Integer(3), LOGARITHM, number::Integer(9));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), POWER, SYMBOL_A, ROOT, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2, false), POWER, SYMBOL_A, ROOT, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2, false), POWER, -SYMBOL_A, ROOT, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_A, POWER, e0, ROOT, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(-SYMBOL_A, POWER, e0, ROOT, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3), ROOT, number::Integer(2, false));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(-SYMBOL_A, POWER, e0, ROOT, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3), ROOT, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), POWER, e0, ROOT, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(3), LOGARITHM, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_B, POWER, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(3), LOGARITHM, -SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_B, POWER, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(SYMBOL_B, LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), POWER, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		try {
			expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(SYMBOL_B, LOGARITHM, number::Integer(2, false));
			expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), POWER, e0);
			e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		}
		catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(2), POWER, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3), POWER, SYMBOL_A);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, number::Integer(3));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(number::Integer(3, false), POWER, SYMBOL_A);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, number::Integer(3));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, POWER, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, POWER, number::Integer(3, false));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(-SYMBOL_A, POWER, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(-SYMBOL_A, POWER, number::Integer(3));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, -SYMBOL_A);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, SYMBOL_A);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, SYMBOL_A);
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e1);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(SYMBOL_A, LOGARITHM, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(number::Integer(5), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e0(SYMBOL_A, LOGARITHM, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(number::Integer(3), POWER, number::Integer(2, false));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_IMAGINARY, ADD, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(-SYMBOL_IMAGINARY, ADD, -SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_IMAGINARY, SUB, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_IMAGINARY, ADD, -SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_IMAGINARY, SUB, -SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, MUL, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, MUL, SYMBOL_IMAGINARY, MUL, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, DIV, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, DIV, -SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, DIV, SYMBOL_IMAGINARY, DIV, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(SYMBOL_IMAGINARY, DIV, -SYMBOL_IMAGINARY, DIV, SYMBOL_IMAGINARY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_IMAGINARY, POWER, number::Integer(2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(-SYMBOL_IMAGINARY, POWER, number::Integer(2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_IMAGINARY, POWER, number::Integer(1), POWER, number::Integer(1), POWER, number::Integer(1));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_IMAGINARY, POWER, number::Integer(1), POWER, number::Integer(1, false), POWER, number::Integer(1));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_IMAGINARY, POWER, number::Integer(0));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(-SYMBOL_IMAGINARY, POWER, number::Integer(0));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_IMAGINARY, POWER, number::Integer(0), POWER, number::Integer(1), POWER, number::Integer(2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		SYMBOL_A.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(1)));
		SYMBOL_B.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_A, ADD, SYMBOL_B);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		SYMBOL_B.SetSubstitution();
		SYMBOL_A.SetSubstitution();
	}

	{
		SYMBOL_A.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(1)));
		SYMBOL_B.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_A, ADD, -SYMBOL_B);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		SYMBOL_B.SetSubstitution();
		SYMBOL_A.SetSubstitution();
	}

	{
		auto a = std::make_shared<Symbol>("a");
		a->SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(1)));
		auto b = std::make_shared<Symbol>("b");
		b->SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(a, SUB, b);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		SymbolWrapper a = std::make_shared<Symbol>("a");
		a.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(1)));
		SymbolWrapper b = std::make_shared<Symbol>("b");
		b.SetSubstitution<ClosureNumber>(ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(-a, SUB, -b);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

#endif
#ifdef EXPRESSION_TEST_EXPAND
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(number::Integer(123), MUL,
			number::Integer(456), MUL, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(2), POWER, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, ADD, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(number::Integer(123), MUL,
			number::Integer(456), MUL, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e1, SUB, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(2), POWER, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e1, SUB, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e1, SUB, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(number::Integer(2), POWER, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(number::Integer(3), LOGARITHM, number::Integer(2));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(e0, SUB, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}
	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(SYMBOL_A, ADD,
			SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(number::Integer(123), MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(SYMBOL_A, ADD,
			SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(SYMBOL_A, ADD,
			SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(expression::ClosureNumber(1), DIV, e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(SYMBOL_A, ADD,
			SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e1(SYMBOL_A, ADD,
			SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(expression::ClosureNumber(1), DIV, e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(SYMBOL_A, MUL,
			SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(SYMBOL_A, MUL,
			SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(SYMBOL_A, MUL,
			SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e1, DIV, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, POWER,
			SYMBOL_B, POWER, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, POWER,
			SYMBOL_B, POWER, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, ROOT,
			SYMBOL_B, ROOT, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, ROOT,
			SYMBOL_B, ROOT, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(SYMBOL_A, LOGARITHM,
			SYMBOL_B, LOGARITHM, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(SYMBOL_A, LOGARITHM,
			SYMBOL_B, LOGARITHM, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, SUB, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, POWER, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, ROOT, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, expression::ClosureNumber(2));
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
		}, expands.back());
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, expression::ClosureNumber(3));
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			}, expands.back());
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, expression::ClosureNumber(number::Integer(3, false)));
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			}, expands.back());
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, expression::ClosureNumber(number::Integer(3, false)), POWER, SYMBOL_C);
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			}, expands.back());
	}

#endif
#ifdef INF_TEST
	{
		const inf::Infinitesimal unit("o");
		std::cout << "unit infinitesimal:" << unit.GetString() << std::endl;
	}

	{
		const inf::Infinitesimal addend("o");
		std::cout << "infinitesimal sum:" << (addend + addend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend("o");
		const inf::Infinitesimal subtrahend("o");
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend("o");
		const inf::Infinitesimal subtrahend("o", number::Fraction(1, 2));
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend("o", number::Integer(1, false));
		const inf::Infinitesimal subtrahend("o", number::Fraction(1, 2));
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal dividend("o", number::Integer(1, false));
		const inf::Infinitesimal divisor("o", number::Fraction(1, 2));
		std::cout << "infinitesimal quotient:" << dividend / divisor << std::endl;
	}

	{
		const number::Integer divisor(2);
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITESIMAL, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(10));
		const number::Integer divisor(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>("o", number::Fraction(1, 2));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 10));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>("o", number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 10));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>("o", number::Fraction(1, 5));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 100));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>("o", number::Fraction(1, 10));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 100));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>("o", number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e0(o, MUL, multiplier, MUL, number::Integer(30));
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e(number::Integer(123), ADD, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITESIMAL, DIV, SYMBOL_INFINITESIMAL);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITESIMAL, MUL, SYMBOL_INFINITESIMAL);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(10));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITESIMAL, MUL, SYMBOL_INFINITESIMAL);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, -expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>("o", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const inf::Infinity unit("oo");
		std::cout << "unit Infinity:" << unit.GetString() << std::endl;
	}

	{
		const inf::Infinity addend("oo");
		std::cout << "Infinity sum:" << (addend + addend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend("oo");
		const inf::Infinity subtrahend("oo");
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend("oo");
		const inf::Infinity subtrahend("oo", number::Fraction(1, 2));
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend("oo", number::Integer(1, false));
		const inf::Infinity subtrahend("oo", number::Fraction(1, 2));
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity dividend("oo", number::Integer(1, false));
		const inf::Infinity divisor("oo", number::Fraction(1, 2));
		std::cout << "Infinity quotient:" << dividend / divisor << std::endl;
	}

	{
		const number::Integer divisor(2);
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITY, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer divisor(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>("oo", number::Fraction(1, 2));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>("oo", number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>("oo", number::Fraction(1, 5));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>("oo", number::Fraction(1, 10));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>("oo", number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e0(o, MUL, multiplier, MUL, number::Integer(30));
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e(number::Integer(123), ADD, e0);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITY, DIV, SYMBOL_INFINITY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITY, MUL, SYMBOL_INFINITY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>("oo", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>("oo", number::Fraction(3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>("oo", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>("oo", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>("oo", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>("oo", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, -expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>("oo", number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>("oo", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>("oo", number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::cout << "derivative:" << std::endl;
		Infinitesimal::SetIgnoreLine(number::Integer(1));
		auto exponent = expression::ClosureNumber(number::Integer(2));
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_X, ADD, SYMBOL_INFINITESIMAL);
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e1(e0, POWER, exponent);
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_X, POWER, exponent);
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e3(e1, SUB, e2);
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(e3, DIV, SYMBOL_INFINITESIMAL);
		LOCAL_SUBSTITUTION_SWITCH;
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			auto collects = expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			expression::SymbolWrapper::SubstitutionOn();
			std::visit([](auto& collect) {
				collect.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			}, collects.back());
		}, expands.back());
	}

	{
		std::cout << "derivative:" << std::endl;
		Infinitesimal::SetIgnoreLine(number::Integer(1));
		auto exponent = expression::ClosureNumber(number::Integer(3));
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_X, ADD, SYMBOL_INFINITESIMAL);
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e1(e0, POWER, exponent);
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_X, POWER, exponent);
		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e3(e1, SUB, e2);
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(e3, DIV, SYMBOL_INFINITESIMAL);
		LOCAL_SUBSTITUTION_SWITCH;
		auto expands = e.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			auto collects = expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			expression::SymbolWrapper::SubstitutionOn();
			std::visit([](auto& collect) {
				collect.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
				}, collects.back());
			}, expands.back());
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> a_x(SYMBOL_A, POWER, SYMBOL_X);
		
		expression::Expression<expression::OPERATOR_TYPE_NONE>::ExpressionSome a_x_derivative;
		
		{
			std::cout << "(a^x)'=";
			expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_X, ADD, SYMBOL_INFINITESIMAL);
			expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, POWER, e0);
			expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e3(e1, SUB, a_x);
			expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(e3, DIV, SYMBOL_INFINITESIMAL);
			LOCAL_SUBSTITUTION_SWITCH;
			auto expands = e.ExpandForwardOutput(std::cout);
			std::visit([&a_x_derivative](auto& expand) {
				std::cout << "=";
				LOCAL_POWER_ROOT_COMMON_SWITCH;
				auto collects = expand.CollectForwardOutput(std::cout);
				a_x_derivative = collects.back();
			}, expands.back()); 
		}

		expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> c(number::Integer(1), ADD, SYMBOL_INFINITESIMAL);

		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> nb(number::Integer(1), DIV, SYMBOL_INFINITY, DIV, SYMBOL_B);
		{
			LOCAL_SUBSTITUTION_SWITCH;
			std::cout << "nb = ";nb.CollectForwardOutput(std::cout);
		}

		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> d;

		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> a;

		{
			std::cout << "a=e^b=";
			a = expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>(c, POWER, SYMBOL_INFINITY, POWER, SYMBOL_B);
			LOCAL_SUBSTITUTION_SWITCH;
			a.CollectForwardOutput(std::cout);
			d = expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>(a, POWER, nb);
			auto expands = d.ExpandForwardOutput(std::cout);
			std::visit([&c](auto& expand) {
				assert(c == expand);
			}, expands.back());
			std::cout << std::endl << "c=" << d << std::endl;
		}
		{
			expression::Expression<expression::OPERATOR_TYPE_ADD_SUB> e0(c, SUB, number::Integer(1));
			expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e1(e0, DIV, nb);
			
			LOCAL_SUBSTITUTION_SWITCH;
			std::cout << "ln(a)=b="; 
			expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e2 = e1.Substitution(c, d);

			{
				auto collects = e2.CollectForwardOutput(std::cout);
				std::visit([](auto& collect) {
					auto expands = collect.ExpandForwardOutput(std::cout);
					std::visit([](auto& expand) {
						auto collects = expand.CollectForwardOutput(std::cout);
						std::visit([](auto& collect) {
							assert(collect.GetString() == "b");
						}, collects.back());
					}, expands.back());
				}, collects.back());
			}
			expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e3 = e2.Substitution(nb, SYMBOL_INFINITESIMAL);
			
			std::visit([&](auto& a_x_derivative) {
				auto e = expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>(a_x_derivative, DIV, a_x);
				auto collects = e.CollectForwardOutput(std::cout);
				std::visit([&](auto& collect) {
					auto e4 = collect.Substitution(SYMBOL_A, a);

					if (e4 == e2) {
						std::cout << "(a^x)'=a^x * ln(a), When the same infinitesimal used" << std::endl;
					}

					if (e4 == e3) {
						std::cout << "(a^x)'=a^x * ln(a), When different infinitesimals used" << std::endl;
					}

				}, collects.back());
			}, a_x_derivative);

		}
	}

#endif

	getchar();
	return 0;
}
