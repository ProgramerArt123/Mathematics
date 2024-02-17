#include <cassert>
#include "Complex.h"
#include "Imaginary.h"
#include "Fraction.h"
#include "Integer.h"
namespace number {
	Integer::Integer(uint64_t value, bool positive) :
		Integer(Natural(value, 10), positive) {

	}

	Integer::Integer(const Natural &value, bool positive) :
		m_value(value), m_positive(positive) {
		if (0 == m_value) {
			m_positive = true;
		}
	}
	Integer::Integer(const std::string &value, bool positive) :
		Integer(Natural(value, 10), positive) {

	}
	const std::string Integer::GetString(uint8_t radix)const {
		return m_positive ? m_value.GetString(radix) : "-" + m_value.GetString(radix);
	}
	void Integer::SetRadix(uint8_t radix) {
		m_value = m_value.GetNatural(radix);
	}
	uint8_t Integer::GetRadix() const {
		return m_value.GetRadix();
	}
	bool Integer::EqualZero() const {
		return Integer(0) == *this;
	}
	void Integer::SetPositive(bool isPositive) {
		m_positive = isPositive;
	}
	bool Integer::IsPositive() const {
		return m_positive;
	}
	Natural Integer::GetNatural() const {
		return m_value;
	}
	const std::string Integer::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		return GetString(radix);
	}

	Integer::operator bool() const {
		return m_value;
	}
	Integer Integer::operator-() const {
		return Integer(m_value, !m_positive);
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
	Integer &Integer::operator-=(const Integer &subtrahend) {
		*this = *this - subtrahend;
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
}