#include <cassert>
#include "Complex.h"
#include "Imaginary.h"
#include "Fraction.h"
#include "Integer.h"
namespace number {
	Integer::Integer(uint64_t value, bool isUnSigned) :
		Integer(Natural(value), isUnSigned) {

	}

	Integer::Integer(const Natural &value, bool isUnSigned) :
		m_value(value) {
		SetPositive(isUnSigned);
		if (m_value.EqualZero()) {
			SetPositive(true);
		}
	}
	Integer::Integer(const std::string &value, bool isUnSigned) :
		Integer(Natural(value, 10), isUnSigned) {

	}
	const std::string Integer::GetString(uint8_t radix)const {
		return IsPositive() ? m_value.GetString(radix) : "-" + m_value.GetString(radix);
	}
	bool Integer::EqualZero() const {
		return m_value.EqualZero();
	}
	bool Integer::EqualPositiveOne() const {
		return IsPositive() && m_value.EqualPositiveOne();
	}
	bool Integer::EqualNegativeOne() const {
		return !IsPositive() && m_value.EqualPositiveOne();
	}
	const std::string Integer::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		return GetString(radix);
	}
	const Natural &Integer::Value() const {
		return m_value;
	}
	Integer Integer::GetAbs() const {
		return IsPositive() ? *this : -*this;
	}
	Integer Integer::operator-() const {
		return Integer(m_value, !IsPositive());
	}
	Integer Integer::operator+(const Integer &addition) const {
		if (IsPositive()) {
			if (addition.IsPositive()) {
				return PositiveAdd(addition);
			}
			else {
				return PositiveSub(addition);
			}
		}
		else {
			if (addition.IsPositive()) {
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
		product.SetPositive(IsPositive() == multiplier.IsPositive());
		return product;
	}
	Integer Integer::operator/(const Integer &divisor) const {
		Integer quotient = m_value / divisor.m_value;
		quotient.SetPositive(IsPositive() == divisor.IsPositive());
		return quotient;
	}
	Integer Integer::operator%(const Integer &divisor) const {
		Integer remainder = m_value % divisor.m_value;
		remainder.SetPositive(IsPositive() == divisor.IsPositive());
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
		return IsPositive() == other.IsPositive() && m_value == other.m_value;
	}
	bool Integer::operator!=(const Integer &other) const {
		return !(*this == other);
	}
	bool Integer::operator>(const Integer &other) const {
		if (IsPositive() && !other.IsPositive()) {
			return true;
		}
		if (!IsPositive() && other.IsPositive()) {
			return false;
		}
		return IsPositive() == m_value > other.Value();
	}
	bool Integer::operator<(const Integer &other) const {
		if (IsPositive() && !other.IsPositive()) {
			return false;
		}
		if (!IsPositive() && other.IsPositive()) {
			return true;
		}
		return IsPositive() != m_value >= other.Value();
	}
	bool Integer::operator>=(const Integer &other) const {
		return *this > other || *this == other;
	}
	bool Integer::operator<=(const Integer &other) const {
		return *this < other || *this == other;
	}
	Integer NaturalSubExtend(const Natural &natural, const Natural &subtrahend) {
		return Integer(natural) - Integer(subtrahend);
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