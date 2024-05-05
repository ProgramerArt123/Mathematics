#include <map>

#include "OpenNumber.h"
#include "Expression.hpp"


namespace expression {
	
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> operator+(const OpenNumber &number, const OpenNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> operator-(const OpenNumber &number, const OpenNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> operator*(const OpenNumber &number, const OpenNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> operator/(const OpenNumber &number, const OpenNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		Expression<OPERATOR_TYPE_0> sum(number);
		for (const auto &closure : addition.m_closures) {
			sum = sum + closure;
		}
		for (const auto &open : addition.m_opens) {
			sum = sum + open;
		}
		for (const auto &expression : addition.m_expressions0) {
			sum = sum + expression;
		}
		for (const auto &expression : addition.m_expressions1) {
			sum = sum + expression;
		}
		return sum;
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &addition){
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		Expression<OPERATOR_TYPE_0> difference(number);
		for (const auto &closure : subtrahend.m_closures) {
			difference = difference - closure;
		}
		for (const auto &open : subtrahend.m_opens) {
			difference = difference - open;
		}
		for (const auto &expression : subtrahend.m_expressions0) {
			difference = difference - expression;
		}
		for (const auto &expression : subtrahend.m_expressions1) {
			difference = difference - expression;
		}
		return difference;
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}

	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		Expression<OPERATOR_TYPE_1> multiple(number);
		for (const auto &closure : multiplier.m_closures) {
			multiple = multiple * closure;
		}
		for (const auto &open : multiplier.m_opens) {
			multiple = multiple * open;
		}
		for (const auto &expression : multiplier.m_expressions0) {
			multiple = multiple * expression;
		}
		for (const auto &expression : multiplier.m_expressions1) {
			multiple = multiple * expression;
		}
		return multiple;
	}

	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		Expression<OPERATOR_TYPE_1> quotient(number);
		for (const auto &closure : divisor.m_closures) {
			quotient = quotient / closure;
		}
		for (const auto &open : divisor.m_opens) {
			quotient = quotient / open;
		}
		for (const auto &expression : divisor.m_expressions0) {
			quotient = quotient / expression;
		}
		for (const auto &expression : divisor.m_expressions1) {
			quotient = quotient / expression;
		}
		return quotient;
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &addition) {
		Expression<OPERATOR_TYPE_0> sum(number);
		if (!sum.m_closures.empty()) {
			sum.m_closures.front() += addition;
		}
		else {
			sum.m_closures.push_back(addition);
			sum.SetNodeOperator<OPERATOR_TYPE_ADD>();
		}
		return sum;
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &subtrahend) {
		Expression<OPERATOR_TYPE_0> difference(number);
		if (!difference.m_closures.empty()) {
			difference.m_closures.front() -= subtrahend;
		}
		else {
			difference.m_closures.push_back(subtrahend);
			difference.SetNodeOperator<OPERATOR_TYPE_SUB>();
		}
		return difference;
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}

	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &multiplier) {
		Expression<OPERATOR_TYPE_1> multiple(number);
		if (!multiple.m_closures.empty()) {
			multiple.m_closures.front() *= multiplier;
		}
		else {
			multiple.m_closures.push_back(multiplier);
			multiple.SetNodeOperator<OPERATOR_TYPE_MUL>();
		}
		return multiple;
	}
	
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &divisor) {
		Expression<OPERATOR_TYPE_1> quotient(number);
		if (!quotient.m_closures.empty()) {
			quotient.m_closures.front() /= divisor;
		}
		else {
			quotient.m_closures.push_back(divisor);
			quotient.SetNodeOperator<OPERATOR_TYPE_DIV>();
		}
		return quotient;
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &addition) {
		Expression<OPERATOR_TYPE_0> sum(number);
		sum.m_opens.push_back(addition);
		sum.SetNodeOperator<OPERATOR_TYPE_ADD>();
		return sum;
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &subtrahend) {
		Expression<OPERATOR_TYPE_0> difference(number);
		difference.m_opens.push_back(subtrahend);
		difference.SetNodeOperator<OPERATOR_TYPE_SUB>();
		return difference;
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}

	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &multiplier) {
		Expression<OPERATOR_TYPE_1> multiple(number);
		multiple.m_opens.push_back(multiplier);
		multiple.SetNodeOperator<OPERATOR_TYPE_MUL>();
		return multiple;
	}

	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &divisor) {
		Expression<OPERATOR_TYPE_1> quotient(number);
		quotient.m_opens.push_back(divisor);
		quotient.SetNodeOperator<OPERATOR_TYPE_DIV>();
		return quotient;
	}
	
	Expression<OPERATOR_TYPE_1> Collect(const expression::Expression<OPERATOR_TYPE_1> &exp, size_t count) {
		Expression<OPERATOR_TYPE_1> collect(exp);
		return collect;
	}

}