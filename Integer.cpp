#include <cassert>
#include "Integer.h"

Integer::Integer(const BitSet &value, bool positive) :
	m_value(value), m_positive(positive) {
	if (0 == m_value) {
		m_positive = true;
	}
}
const std::string Integer::GetString(uint8_t base)const {
	return m_positive ? m_value.GetString(base) : "-" + m_value.GetString(base);
}
Integer::operator bool() const {
	return m_value;
}
Integer Integer::operator-() const {
	return Integer(m_value, !m_positive);
}
Integer Integer::operator!() const {
	Integer product(BitSet(1));
	for (BitSet index = 1; index <= m_value; ++index) {
		product *= Integer(index);
	}
	return product;
}
Integer Integer::operator+(const Integer &addition) const {
	if (m_positive) {
		if (addition.m_positive) {
			return PositiveAdd(addition);
		}
		else {
			return PositiveSub(addition);
		}
	}
	else {
		if (addition.m_positive) {
			return addition.PositiveSub(*this);
		}
		else {
			return -PositiveAdd(addition);
		}
	}
}
Integer Integer::operator-(const Integer &subtrahend) const {
	return *this + (-subtrahend);
}
Integer Integer::operator*(const Integer &multiplier) const {
	Integer product = m_value * multiplier.m_value;
	product.m_positive = m_positive == multiplier.m_positive;
	return product;
}
Integer Integer::operator/(const Integer &divisor) const {
	Integer quotient = m_value / divisor.m_value;
	quotient.m_positive = m_positive == divisor.m_positive;
	return quotient;
}
Integer Integer::operator%(const Integer &divisor) const {
	Integer remainder = m_value % divisor.m_value;
	remainder.m_positive = m_positive == divisor.m_positive;
	return remainder;
}
Integer &Integer::operator+=(const Integer &addition) {
	*this = *this + addition;
	return *this;
}
Integer &Integer::operator*=(const Integer &multiplier) {
	*this = *this * multiplier;
	return *this;
}
Integer &Integer::operator/=(const Integer &divisor) {
	*this = *this / divisor;
	return *this;
}
bool Integer::operator==(const Integer &other)const {
	return m_positive == other.m_positive && m_value == other.m_value;
}
Integer Integer::GreatestCommonDivisor(const Integer &other) const {
	return other ? other.GreatestCommonDivisor(*this%other) : *this;
}
Integer Integer::PositiveAdd(const Integer &addition) const {
	return Integer(m_value + addition.m_value);
}
Integer Integer::PositiveSub(const Integer &subtrahend) const {
	if (m_value >= subtrahend.m_value) {
		return Integer(m_value - subtrahend.m_value);
	}
	else {
		return Integer(subtrahend.m_value - m_value, false);
	}
}
