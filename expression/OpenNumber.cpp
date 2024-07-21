#include <sstream>
#include "number/Number.h"
#include "OpenNumber.h"

namespace expression {
	OpenNumber::OpenNumber(const expression::OpenNumber &prototype) {
		*this = prototype;
	}
	OpenNumber::OpenNumber(const expression::OpenNumber &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	OpenNumber::OpenNumber(const number::Root &value, OPERATOR_TYPE_FLAG flag) : m_value(value), Number(flag){
	}
	const std::string OpenNumber::GetString(size_t pos, uint8_t radix) const {
		return m_value.OutPutString(pos);
	}
	bool OpenNumber::EqualZero() const {
		return Value().EqualZero();
	}
	bool OpenNumber::EqualOne() const {
		return Value() == number::Root(1,0);
	}
	const OpenNumber &OpenNumber::operator=(const OpenNumber &right) {
		Number::operator=(right);
		m_value = right.m_value;
		return *this;
	}
	std::optional<expression::OpenNumber> OpenNumber::Collect(const expression::OpenNumber &right) const {
		switch (right.Level())
		{
		case OPERATOR_TYPE_LEVEL_0:
			return Collect0(right);
			break;
		case OPERATOR_TYPE_LEVEL_1:
			return Collect1(right);
			break;
		default:
			break;
		}
		return std::nullopt;
	}
	std::optional<expression::OpenNumber> OpenNumber::Collect0(const expression::OpenNumber &right) const {
		number::Root leftValue = m_value;
		if (m_operator && OPERATOR_TYPE_FLAG_SUB == m_operator->GetFlag()) {
			leftValue = -m_value;
		}
		number::Root rightValue = right.m_value;
		if (right.m_operator && OPERATOR_TYPE_FLAG_SUB == right.m_operator->GetFlag()) {
			rightValue = -right.m_value;
		}
		if (leftValue.EqualBase0(rightValue)) {
			return leftValue.AddEqual(rightValue);
		}
		else {
			return std::nullopt;
		}
	}

	std::optional<expression::OpenNumber> OpenNumber::Collect1(const expression::OpenNumber &right) const {
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
			return leftValue.MulEqual(rightValue, isLeftMul, isRightMul);
		}
		else {
			return std::nullopt;
		}
	}
	const number::Root &OpenNumber::Value()const {
		return m_value;
	}
	void OpenNumber::Opposite() {
		m_value.Opposite();
	}
}