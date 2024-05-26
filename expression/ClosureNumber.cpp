#include <sstream>
#include "number/Number.h"
#include "Series.hpp"
#include "ClosureNumber.hpp"

namespace expression {
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype) {
		*this = prototype;
	}
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype, OPERATOR_TYPE_FLAG flag){
		*this = prototype;
		SetOperator(flag);
	}
	ClosureNumber::ClosureNumber(const number::Integer &value, OPERATOR_TYPE_FLAG flag) :m_value(value, 0), Number(OPERATOR_TYPE_FLAG_ADD) {
	}
	ClosureNumber::ClosureNumber(const number::Fraction &value, OPERATOR_TYPE_FLAG flag) :m_value(value, 0), Number(OPERATOR_TYPE_FLAG_ADD) {
	}
	ClosureNumber::ClosureNumber(const number::Complex &value, OPERATOR_TYPE_FLAG flag):m_value(value), Number(OPERATOR_TYPE_FLAG_ADD) {
	}
	const std::string ClosureNumber::GetString(size_t pos, uint8_t radix) const {
		return m_value.OutPutString(pos);
	}
	const ClosureNumber &ClosureNumber::operator=(const ClosureNumber &right) {
		Number::operator=(right);
		m_value = right.m_value;
		return *this;
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