#include <sstream>
#include "number/Number.h"
#include "OpenNumber.h"

namespace expression {

	OpenNumber::OpenNumber(const expression::OpenNumber &prototype) {
		*this = prototype;
	}
	OpenNumber::OpenNumber(const number::Root &value) : m_value(value){
	}
	const std::string OpenNumber::OutPutString(size_t pos) const {
		std::stringstream ss;
		if (m_operator) {
			ss << m_operator->OutPutString(pos);
		}
		ss << m_value.OutPutString(pos);
		return ss.str();
	}
	const OpenNumber &OpenNumber::operator=(const OpenNumber &right) {
		Number::operator=(right);
		m_value = right.m_value;
		return *this;
	}
	bool OpenNumber::Collect0(const expression::OpenNumber &right, expression::OpenNumber &collect) const {
		number::Root leftValue = m_value;
		if (m_operator && OPERATOR_TYPE_FLAG_SUB == m_operator->GetFlag()) {
			leftValue = -m_value;
		}
		number::Root rightValue = right.m_value;
		if (right.m_operator && OPERATOR_TYPE_FLAG_SUB == right.m_operator->GetFlag()) {
			rightValue = -right.m_value;
		}
		if (leftValue.EqualBase0(rightValue)) {
			collect.m_value = leftValue.AddEqual(rightValue);
			return true;
		}
		else {
			return false;
		}
	}

	bool OpenNumber::Collect1(const expression::OpenNumber &right, expression::OpenNumber &collect) const {
		number::Root leftValue = m_value;
		bool isLeftMul = true;
		if (m_operator && OPERATOR_TYPE_FLAG_DIV == m_operator->GetFlag()) {
			leftValue = number::Root(m_value.Base(), -m_value.Exponent(), m_value.IsPositive());
			isLeftMul = false;
		}
		number::Root rightValue = right.m_value;
		bool isRightMul = true;
		if (right.m_operator && OPERATOR_TYPE_FLAG_DIV == right.m_operator->GetFlag()) {
			rightValue = number::Root(right.m_value.Base(), -right.m_value.Exponent(), right.m_value.IsPositive());
			isRightMul = false;
		}
		if (leftValue.EqualBase1(rightValue)) {
			collect.m_value = leftValue.MulEqual(rightValue, isLeftMul, isRightMul);
			return true;
		}
		else {
			return false;
		}
	}
	const number::Root &OpenNumber::Value()const {
		return m_value;
	}
}