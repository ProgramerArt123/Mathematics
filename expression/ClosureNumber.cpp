#include <sstream>
#include "number/Number.h"
#include "Series.hpp"
#include "ClosureNumber.hpp"

namespace expression {
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype){
		*this = prototype;
	}
	ClosureNumber::ClosureNumber(const number::Integer &value) :m_value(value, 0) {
	}
	ClosureNumber::ClosureNumber(const number::Fraction &value) :m_value(value, 0) {
	}
	ClosureNumber::ClosureNumber(const number::Complex &value):m_value(value){
	}
	const std::string ClosureNumber::OutPutString(size_t pos) const {
		std::stringstream ss;
		if (m_operator) {
			ss << m_operator->OutPutString(pos);
		}
		ss << m_value.OutPutString(pos);
		return ss.str();
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