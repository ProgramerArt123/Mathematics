#include <sstream>

#include <iostream>

#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype) {
		*this = prototype;
	}
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	ClosureNumber::ClosureNumber(const number::Integer &value, OPERATOR_TYPE_FLAG flag) :
		Number(flag), m_value(value) {
	}
	bool ClosureNumber::IsPositive() const {
		return m_value.IsPositive();
	}
	const std::string ClosureNumber::GetString(size_t pos, uint8_t radix) const {
		return m_value.updatePosition(pos).OutPutString();
	}
	bool ClosureNumber::IsEqual(const Node &other, bool ignoreOperator) const {
		if (!Node::IsEqual(other, ignoreOperator)) {
			return false;
		}
		const ClosureNumber &otherClosure = dynamic_cast<const ClosureNumber&>(other);
		return *this == otherClosure;
	}
	bool ClosureNumber::EqualZero() const {
		return Value().EqualZero();
	}
	bool ClosureNumber::EqualOne() const {
		return Value().EqualOne();
	}
	bool ClosureNumber::EqualNegativeOne() const {
		return (-Value()).EqualOne();
	}
	void ClosureNumber::Opposite() {
		m_value.Opposite();
	}
	const number::Integer &ClosureNumber::Value() const {
		return m_value;
	}
	const ClosureNumber &ClosureNumber::operator=(const ClosureNumber &right) {
		expression::Number::operator=(right);
		m_value = right.m_value;
		return *this;
	}
	bool ClosureNumber::operator==(const ClosureNumber &other) const {
		return Node::operator==(other) && Value() == other.Value();
	}
	ClosureNumber ClosureNumber::operator+(const ClosureNumber &addition) const {
		return m_value + addition.m_value;
	}
	ClosureNumber ClosureNumber::operator-(const ClosureNumber &subtrahend) const {
		return m_value - subtrahend.m_value;
	}
	ClosureNumber ClosureNumber::operator*(const ClosureNumber &multiplier) const {
		return m_value * multiplier.m_value;
	}
	ClosureNumber ClosureNumber::operator/(const ClosureNumber &divisor) const {
		return m_value / divisor.m_value;
	}
	ClosureNumber &ClosureNumber::operator+=(const ClosureNumber &addition) {
		m_value += addition.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator-=(const ClosureNumber &subtrahend) {
		m_value -= subtrahend.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator*=(const ClosureNumber &multiplier) {
		m_value *= multiplier.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator/=(const ClosureNumber &divisor) {
		m_value /= divisor.m_value;
		return *this;
	}
}