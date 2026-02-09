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
#include "expression/SymbolManager.h"
using namespace inf;
using namespace expression;
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
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_A, ClosureNumber(number::Integer(1)));
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_B, ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_A, ADD, SYMBOL_B);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_A, ClosureNumber(number::Integer(1)));
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_B, ClosureNumber(number::Integer(2)));
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e(SYMBOL_A, ADD, -SYMBOL_B);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
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
		LOCAL_SYMBOL_SUBSTITUTION(a, ClosureNumber(number::Integer(1)));
		SymbolWrapper b = std::make_shared<Symbol>("b");
		LOCAL_SYMBOL_SUBSTITUTION(b, ClosureNumber(number::Integer(2)));
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
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e2(SYMBOL_D, ADD,
			SYMBOL_E, SUB, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1, MUL, e2);
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
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e2(SYMBOL_D, ADD,
			SYMBOL_E, SUB, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(expression::ClosureNumber(1), DIV, e0, DIV, e1, DIV, e2);
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
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e2(SYMBOL_D, ADD,
			SYMBOL_E, SUB, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0 * e2, DIV, e1);
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
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(SYMBOL_D, MUL,
			SYMBOL_E, DIV, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1, MUL, e2);
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
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(SYMBOL_D, MUL,
			SYMBOL_E, DIV, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1, DIV, e2);
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
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e1(SYMBOL_A, MUL,
			SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e2(SYMBOL_D, MUL,
			SYMBOL_E, DIV, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e1, DIV, e0, DIV, e2);
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
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_D, POWER,
			SYMBOL_E, POWER, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1, MUL, e2);
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
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, POWER,
			SYMBOL_B, POWER, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_D, POWER,
			SYMBOL_E, POWER, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1, DIV, e2);
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
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_D, ROOT,
			SYMBOL_E, ROOT, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1, MUL, e2);
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
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e1(SYMBOL_A, ROOT,
			SYMBOL_B, ROOT, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e2(SYMBOL_D, ROOT,
			SYMBOL_E, ROOT, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1, DIV, e2);
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
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e2(SYMBOL_D, LOGARITHM,
			SYMBOL_E, LOGARITHM, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, MUL, e1, MUL, e2);
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
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(number::Integer(123), ADD,
			number::Integer(456), SUB, number::Integer(789));
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e1(SYMBOL_A, LOGARITHM,
			SYMBOL_B, LOGARITHM, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e2(SYMBOL_D, LOGARITHM,
			SYMBOL_E, LOGARITHM, SYMBOL_F);
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e(e0, DIV, e1, DIV, e2);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B, MUL, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_D, POWER, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, POWER, SYMBOL_D, POWER, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B, MUL, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, POWER, SYMBOL_E, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, POWER, SYMBOL_E, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B, ADD, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, POWER, SYMBOL_E, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, SUB, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, SUB, SYMBOL_B, SUB, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, POWER, SYMBOL_E, POWER, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B, MUL, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_D, ROOT, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(e0, ROOT, SYMBOL_D, ROOT, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B, MUL, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, ROOT, SYMBOL_E, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_C, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_D, ROOT, SYMBOL_E, ROOT, e0);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, MUL, SYMBOL_B, MUL, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_D, LOGARITHM, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_MUL_DIV> e0(SYMBOL_A, DIV, SYMBOL_B, DIV, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_D, LOGARITHM, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, POWER, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, POWER, SYMBOL_B, POWER, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_D, LOGARITHM, SYMBOL_E);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, ROOT, SYMBOL_B);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_C);
		e.ExpandForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> e0(SYMBOL_A, ROOT, SYMBOL_B, ROOT, SYMBOL_C);
		expression::Expression<OPERATOR_TYPE_LOGARITHM> e(e0, LOGARITHM, SYMBOL_D, LOGARITHM, SYMBOL_E);
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
		expression::Expression<OPERATOR_TYPE_ADD_SUB> e0(SYMBOL_A, ADD, SYMBOL_B, ADD, SYMBOL_C);
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
		const inf::Infinitesimal unit;
		std::cout << "unit infinitesimal:" << unit.GetString() << std::endl;
	}

	{
		const inf::Infinitesimal addend;
		std::cout << "infinitesimal sum:" << (addend + addend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend;
		const inf::Infinitesimal subtrahend;
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend;
		const inf::Infinitesimal subtrahend(number::Fraction(1, 2));
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal minuend(number::Integer(1, false));
		const inf::Infinitesimal subtrahend(number::Fraction(1, 2));
		std::cout << "infinitesimal difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinitesimal dividend(number::Integer(1, false));
		const inf::Infinitesimal divisor(number::Fraction(1, 2));
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
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>(number::Fraction(1, 2));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 10));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>(number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 10));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>(number::Fraction(1, 5));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 100));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>(number::Fraction(1, 10));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		inf::Infinitesimal::SetIgnoreLine(number::Fraction(1, 100));
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinitesimal>(number::Fraction(1, 3));
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
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>(number::Fraction(3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, -expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinitesimal>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinitesimal>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const inf::Infinity unit;
		std::cout << "unit Infinity:" << unit.GetString() << std::endl;
	}

	{
		const inf::Infinity addend;
		std::cout << "Infinity sum:" << (addend + addend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend;
		const inf::Infinity subtrahend;
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend;
		const inf::Infinity subtrahend(number::Fraction(1, 2));
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity minuend(number::Integer(1, false));
		const inf::Infinity subtrahend(number::Fraction(1, 2));
		std::cout << "Infinity difference:" << (minuend - subtrahend).GetString() << std::endl;
	}

	{
		const inf::Infinity dividend(number::Integer(1, false));
		const inf::Infinity divisor(number::Fraction(1, 2));
		std::cout << "Infinity quotient:" << dividend / divisor << std::endl;
	}

	{
		const number::Integer divisor(2);
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_INFINITY, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer divisor(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>(number::Fraction(1, 2));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, DIV, divisor);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>(number::Fraction(1, 3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}


	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>(number::Fraction(1, 5));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>(number::Fraction(1, 10));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o, MUL, multiplier, MUL, number::Integer(10));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const number::Integer multiplier(2);
		std::shared_ptr<expression::Symbol> o = std::make_shared<inf::Infinity>(number::Fraction(1, 3));
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
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>(number::Fraction(3));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, MUL, -expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o1 = std::make_shared<inf::Infinity>(number::Fraction(2));
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(o1, DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::shared_ptr<expression::Symbol> o2 = std::make_shared<inf::Infinity>(number::Fraction(3, 1, false));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(number::Integer(1), DIV, expression::SymbolWrapper(o2));
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_A, ROOT, SYMBOL_B, ROOT, SYMBOL_INFINITESIMAL);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const expression::SymbolWrapper o1(std::make_shared<inf::Infinitesimal>(number::Integer(2)));
		const expression::SymbolWrapper o2(std::make_shared<inf::Infinitesimal>(number::Integer(3)));
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_A, ROOT, SYMBOL_B, ROOT, o1, POWER, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const expression::SymbolWrapper o(std::make_shared<inf::Infinitesimal>(number::Integer(2)));
		const expression::SymbolWrapper oo(std::make_shared<inf::Infinity>(number::Integer(3)));
		expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> e(SYMBOL_A, DIV, SYMBOL_B, MUL, o, MUL, oo);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_A, ROOT, SYMBOL_B, ROOT, SYMBOL_INFINITY);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		const expression::SymbolWrapper o1(std::make_shared<inf::Infinity>(number::Integer(2)));
		const expression::SymbolWrapper o2(std::make_shared<inf::Infinity>(number::Integer(3)));
		expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT> e(SYMBOL_A, ROOT, SYMBOL_B, ROOT, o1, POWER, o2);
		e.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
	}

	{
		std::cout << "derivative:" << std::endl;
		Infinitesimal::SetIgnoreLine(number::Integer(1));
		const expression::ClosureNumber exponent(number::Integer(2));
		const auto x_increment = SYMBOL_X + SYMBOL_INFINITESIMAL;
		const auto y_increment = x_increment ^ exponent;
		const auto y = SYMBOL_X ^ exponent;
		const auto delta_y = y_increment - y;
		const auto derivative = delta_y / SYMBOL_INFINITESIMAL;
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper &symbol) {return false; });
		const auto expands = derivative.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			const auto collects = expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			expression::SymbolWrapper::SetSubstitutionCondition();
			std::visit([](auto& collect) {
				const auto collects = collect.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
				std::visit([](auto& collect) {
					assert(collect.GetString() == "2*x");
				}, collects.back());
			}, collects.back());
		}, expands.back());
		std::cout << std::endl << "(x^2)'=2*x" << std::endl;
	}

	{
		std::cout << "derivative:" << std::endl;
		Infinitesimal::SetIgnoreLine(number::Integer(1));
		const expression::ClosureNumber exponent(number::Integer(3));
		const auto x_increment = SYMBOL_X + SYMBOL_INFINITESIMAL;
		const auto y_increment = x_increment ^ exponent;
		const auto y = SYMBOL_X ^ exponent;
		const auto delta_y = y_increment - y;
		const auto derivative = delta_y / SYMBOL_INFINITESIMAL;
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const auto expands = derivative.ExpandForwardOutput(std::cout);
		std::visit([](auto& expand) {
			const auto collects = expand.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
			expression::SymbolWrapper::SetSubstitutionCondition();
			std::visit([](auto& collect) {
				const auto collects = collect.CollectForwardOutput(std::cout); std::cout << std::endl << std::endl;
				std::visit([](auto& collect) {
					assert(collect.GetString() == "3*(x^2)");
				}, collects.back());
			}, collects.back());
		}, expands.back());
		std::cout << std::endl << "(a^3)'=3*(x^2)" << std::endl;
	}

	{
		expression::SymbolWrapper n(std::make_shared<expression::Symbol>("n"));
		LOCAL_SYMBOL_SUBSTITUTION(n, SYMBOL_INFINITY);
		const auto n_reciprocal = expression::ClosureNumber(1) / n;
		auto e_factor = expression::ClosureNumber(1) + n_reciprocal;
		expression::SymbolWrapper e_factor_symbol(std::make_shared<expression::Symbol>("e_factor"));
		LOCAL_SYMBOL_SUBSTITUTION(e_factor_symbol, e_factor);

		expression::SymbolWrapper ln_a(std::make_shared<expression::Symbol>("ln(a)"));
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_B, ln_a);

		const auto nb = n * SYMBOL_B;

		const auto nb_reciprocal = expression::ClosureNumber(1) / nb;

		const auto a = e_factor_symbol ^ nb;
		LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_A, a);

		{
			LOCAL_SYMBOL_LOCK(e_factor_symbol);
			a.CollectForwardOutput(std::cout);
		}
		
		const auto a_nb_reciprocal = SYMBOL_A ^ nb_reciprocal;
		
		{
			LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return symbol.Name() != INFINITESIMAL_NAME; });
			auto expands = a_nb_reciprocal.ExpandForwardOutput(std::cout);
			auto collects = e_factor.CollectForwardOutput(std::cout);
			std::visit([](auto& expand, auto& collect) {
				assert(expand == collect);
			}, expands.back(), collects.back());
		}
		
		const auto construct_numerator = e_factor - expression::ClosureNumber(1);
		auto construct = construct_numerator / nb_reciprocal;
		
		{
			LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
			auto collects = construct.CollectForwardOutput(std::cout);
			std::visit([&ln_a](auto& collect) {
				assert(collect.GetString() == SYMBOL_B.GetString());
			}, collects.back());
		}
		auto substitution = construct.Substitution(e_factor, a_nb_reciprocal).Substitution(nb, SYMBOL_INFINITY);
		
		const auto x_increment = SYMBOL_X + SYMBOL_INFINITESIMAL;
		const auto y_increment = SYMBOL_A ^ x_increment;
		const auto y = SYMBOL_A ^ SYMBOL_X;
		const auto delta_y = y_increment - y;
		const auto derivative = delta_y / SYMBOL_INFINITESIMAL;
		
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const auto alternatings = derivative.AlternatingForwardOutput(std::cout);
		const auto collects = (substitution * y).AlternatingForwardOutput(std::cout);
		std::visit([](auto& alternating, auto& collect) {
			assert(alternating == collect);
		}, alternatings.back(), collects.back());

		std::cout << std::endl << "(a^x)'=(a^x)*ln(a)" << std::endl;
	}
	
	{
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const expression::SymbolWrapper f_x(std::make_shared<expression::Symbol>("f(x)"));
		const expression::SymbolWrapper f_x_increment(std::make_shared<expression::Symbol>("f(x + o)"));
		const auto delta_y = f_x_increment - f_x;
		const auto f_x_derivative = delta_y / SYMBOL_INFINITESIMAL;

		const expression::SymbolWrapper constant(std::make_shared<expression::Symbol>("c"));
		const auto f_x_composite = constant * f_x;
		const auto f_x_increment_composite = constant * f_x_increment;
		const auto composite_delta_y = f_x_increment_composite - f_x_composite;
		const auto composite_derivative = composite_delta_y / SYMBOL_INFINITESIMAL;

		const auto f_x_derivative_mul = constant * f_x_derivative;

		auto composite_derivatives = composite_derivative.CollectForwardOutput(std::cout);
		auto f_x_derivative_muls = f_x_derivative_mul.CollectForwardOutput(std::cout);
		std::visit([](auto& composite_derivative, auto& derivative_mul) {
			if (derivative_mul == composite_derivative) {
				std::cout << std::endl << "(c*f(x))'=c*(f'(x))" << std::endl;
			}
		}, composite_derivatives.back(), f_x_derivative_muls.back());
	}

	{
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const expression::SymbolWrapper u_x(std::make_shared<expression::Symbol>("u(x)"));
		const expression::SymbolWrapper u_x_increment(std::make_shared<expression::Symbol>("u(x + o)"));
		const auto u_delta_y = u_x_increment - u_x;
		const auto u_x_derivative = u_delta_y / SYMBOL_INFINITESIMAL;

		const expression::SymbolWrapper v_x(std::make_shared<expression::Symbol>("v(x)"));
		const expression::SymbolWrapper v_x_increment(std::make_shared<expression::Symbol>("v(x + o)"));
		const auto v_delta_y = v_x_increment - v_x;
		const auto v_x_derivative = v_delta_y / SYMBOL_INFINITESIMAL;


		{
			const auto derivative_sum = u_x_derivative + v_x_derivative;
			auto derivative_sums = derivative_sum.CollectForwardOutput(std::cout);

			const auto sum_delta_y = (u_x_increment - u_x) + (v_x_increment - v_x);
			const auto sum_derivative = sum_delta_y / SYMBOL_INFINITESIMAL;

			std::visit([&sum_derivative](auto& derivative_sum) {
				if (derivative_sum == sum_derivative) {
					std::cout << std::endl << "(u(x) + v(x))'=u'(x) + v'(x)" << std::endl;
				}
			}, derivative_sums.back());
		}


		{
			const auto derivative_difference = u_x_derivative - v_x_derivative;
			auto derivative_differences = derivative_difference.CollectForwardOutput(std::cout);

			const auto difference_delta_y = (u_x_increment - u_x) - (v_x_increment - v_x);
			const auto difference_derivative = difference_delta_y / SYMBOL_INFINITESIMAL;
			auto difference_derivatives = difference_derivative.CollectForwardOutput(std::cout);

			std::visit([](auto& derivative_difference, auto& difference_derivative) {
				if (derivative_difference == difference_derivative) {
					std::cout << std::endl << "(u(x) - v(x))'=u'(x) - v'(x)" << std::endl;
				}
			}, derivative_differences.back(), difference_derivatives.back());
		}
			
	}

	{
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return symbol.Name() != INFINITESIMAL_NAME; });
		expression::SymbolWrapper u_x(std::make_shared<expression::Symbol>("u(x)"));

		expression::SymbolWrapper u_x_increment(std::make_shared<expression::Symbol>("u(x + o)"));
		const auto u_delta_y = u_x_increment - u_x;
		const auto u_x_derivative = u_delta_y / SYMBOL_INFINITESIMAL;

		expression::SymbolWrapper v_x(std::make_shared<expression::Symbol>("v(x)"));
		expression::SymbolWrapper v_x_increment(std::make_shared<expression::Symbol>("v(x + o)"));

		const auto v_delta_y = v_x_increment - v_x;
		const auto v_x_derivative = v_delta_y / SYMBOL_INFINITESIMAL;
		

		{
			const auto u_v_increment = u_x_increment * v_x_increment;
			const auto u_v = u_x * v_x;
			
			const auto u_increment_v = u_x_increment * v_x;
			const auto construct = ((u_v_increment - u_increment_v).Substitution(u_x_increment, u_x) + (u_increment_v - u_v)) / SYMBOL_INFINITESIMAL;
			
			auto expands = construct.CollectForwardOutput(std::cout);
			
			
			const auto u_x_derivative_cross = u_x_derivative * v_x;
			const auto v_x_derivative_cross = v_x_derivative * u_x;
			const auto product_derivative = u_x_derivative_cross + v_x_derivative_cross;
			auto alternatings = product_derivative.AlternatingForwardOutput(std::cout);
			
			std::visit([](auto &alternating, auto& expand) {
				assert(alternating == expand);
			}, alternatings.back(), expands.back());

			std::cout << std::endl << "(u(x) * v(x))'=u'(x) * v(x) + v'(x) * u(x)" << std::endl;
		}


		{
			const auto u_v_increment = u_x_increment / v_x_increment;
			const auto u_v = u_x / v_x;

			const auto u_increment_v_x = u_x_increment * v_x;
			const auto v_increment_u_x = v_x_increment * u_x;
			const auto difference = (u_increment_v_x - v_increment_u_x) / (v_x * v_x_increment * SYMBOL_INFINITESIMAL);

			{
				auto collects0 = ((u_v_increment - u_v) / SYMBOL_INFINITESIMAL).CollectForwardOutput(std::cout);
				auto collects1 = difference.CollectForwardOutput(std::cout);
				std::visit([](auto& collect0, auto& collect1) {
					assert(collect0 == collect1);
				}, collects0.back(), collects1.back());
			}

			const auto u_v_product = u_x * v_x;
			const auto construct = ((u_increment_v_x - u_v_product) + (u_v_product - v_increment_u_x)) / ((v_x ^ expression::ClosureNumber(2)) * SYMBOL_INFINITESIMAL);
			
			{
				auto collects0 = construct.CollectForwardOutput(std::cout);

				auto collects1 = (((u_x_derivative * v_x) - (v_x_derivative * u_x)) / (v_x ^ expression::ClosureNumber(2))).CollectForwardOutput(std::cout);
				std::visit([](auto& collect0, auto& collect1) {
					assert(collect0 == collect1);
				}, collects0.back(), collects1.back());
			}
			std::cout << std::endl << "(u(x) / v(x))'=(u'(x) * v(x) - v'(x) * u(x)) / v(x)^2" << std::endl;
		}
		
	}

	{
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const auto x_inf_reciprocal = (SYMBOL_X + SYMBOL_INFINITESIMAL).Reciprocal();
		const auto x_reciprocal = expression::Expression<OPERATOR_TYPE_MUL_DIV>::Reciprocal(SYMBOL_X);
		const auto derivative = (x_inf_reciprocal - x_reciprocal) / SYMBOL_INFINITESIMAL;
		auto collects = derivative.CollectForwardOutput(std::cout);
		std::visit([](auto& collect) {
			expression::SymbolWrapper::SetSubstitutionCondition();
			collect.CollectForwardOutput(std::cout);
			}, collects.back());
		std::cout << std::endl << "(1/x)'=-1/x^2" << std::endl;
	}


	{
		LOCAL_SYMBOL_SUBSTITUTION_CONDITION([](const expression::SymbolWrapper& symbol) {return false; });
		const auto e = (expression::ClosureNumber(1) + SYMBOL_INFINITESIMAL) ^ SYMBOL_INFINITY;
		const expression::SymbolWrapper e_symbol(std::make_shared<expression::Symbol>("e"));
		const auto ln = e | e_symbol;
		ln.ExpandForwardOutput(std::cout); std::cout << "=1" << std::endl;
		std::cout << std::endl << "ln(1+o)/o=1" << std::endl;

		const auto y_increment = (SYMBOL_X + SYMBOL_INFINITESIMAL) | e_symbol;
		const auto y = SYMBOL_X | e_symbol;
		const auto delta_y = (y_increment - y).SetSort(false);
		const auto derivative = delta_y / SYMBOL_INFINITESIMAL;
		{
			LOCAL_SYMBOL_LOCK(SYMBOL_INFINITESIMAL);
			auto alternatings = derivative.AlternatingForwardOutput(std::cout, false);
			std::visit([](auto &alternating) {
				LOCAL_SYMBOL_SUBSTITUTION(SYMBOL_A, SYMBOL_INFINITESIMAL);
				expression::SymbolWrapper::SetSubstitutionCondition();
				alternating.Substitution(SYMBOL_INFINITESIMAL, SYMBOL_A * SYMBOL_X).CollectForwardOutput(std::cout);
			}, alternatings.back());
		}
		std::cout << std::endl << "(ln(x))'=1/x" << std::endl;

		{
			auto collects = ((SYMBOL_X | e_symbol) * (SYMBOL_A | e_symbol).Reciprocal()).CollectForwardOutput(std::cout);
			std::visit([](auto &collect) {
				assert(collect.GetString() == "x|a");
			}, collects.back());
		}
		std::cout << std::endl << "(log(x,a))'=1/(x*ln(a))" << std::endl;

	}
#endif

	getchar();
	return 0;
}
