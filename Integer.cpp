#include <cassert>
#include "Complex.h"
#include "Imaginary.h"
#include "Fraction.h"
#include "Integer.h"

Integer::Integer(uint64_t value, bool positive):
	Integer(Natural(value, 10), positive) {

}

Integer::Integer(const Natural &value, bool positive) :
	m_value(value), m_positive(positive) {
	if (0 == m_value) {
		m_positive = true;
	}
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
std::shared_ptr<Real> Integer::operator+(const Real &addition) const {
	if (strstr(typeid(addition).name(), "Integer")) {
		return std::shared_ptr<Real>(new Integer(
			*this + dynamic_cast<const Integer &>(addition)
		));
	}
	else if (strstr(typeid(addition).name(), "Fraction")) {
		return std::shared_ptr<Real>(new Fraction(
			*this + dynamic_cast<const Fraction &>(addition)
		));
	}
	else {
		throw "undefine";
	}
}
std::shared_ptr<Real> Integer::operator-(const Real &subtrahend) const {
	if (strstr(typeid(subtrahend).name(), "Integer")) {
		return std::shared_ptr<Real>(new Integer(
			*this - dynamic_cast<const Integer &>(subtrahend)
		));
	}
	else if (strstr(typeid(subtrahend).name(), "Fraction")) {
		return std::shared_ptr<Real>(new Fraction(
			*this - dynamic_cast<const Fraction &>(subtrahend)
		));
	}
	else {
		throw "undefine";
	}
}
std::shared_ptr<Real> Integer::operator*(const Real &multiplier) const {
	if (strstr(typeid(multiplier).name(), "Integer")) {
		return std::shared_ptr<Real>(new Integer(
			*this * dynamic_cast<const Integer &>(multiplier)
		));
	}
	else if (strstr(typeid(multiplier).name(), "Fraction")) {
		return std::shared_ptr<Real>(new Fraction(
			*this * dynamic_cast<const Fraction &>(multiplier)
		));
	}
	else {
		throw "undefine";
	}
}
std::shared_ptr<Real> Integer::operator/(const Real &divisor) const {
	if (strstr(typeid(divisor).name(), "Integer")) {
		return std::shared_ptr<Real>(new Integer(
			*this / dynamic_cast<const Integer &>(divisor)
		));
	}
	else if (strstr(typeid(divisor).name(), "Fraction")) {
		return std::shared_ptr<Real>(new Fraction(
			*this / dynamic_cast<const Fraction &>(divisor)
		));
	}
	else {
		throw "undefine";
	}
}
std::shared_ptr<Number> Integer::Power(const Real &exponent) const {
	if (strstr(typeid(exponent).name(), "Integer")) {
		return std::shared_ptr<Number>(new Fraction(
			Power(dynamic_cast<const Integer &>(exponent))
		));
	}
	else if (strstr(typeid(exponent).name(), "Fraction")) {
		return std::shared_ptr<Number>(new Complex(
			Power(dynamic_cast<const Fraction &>(exponent))
		));
	}
	else {
		throw "undefine";
	}
}
std::shared_ptr<Number> Integer::Root(const Real &exponent) const {
	if (strstr(typeid(exponent).name(), "Integer")) {
		return std::shared_ptr<Number>(new Complex(
			Root(dynamic_cast<const Integer &>(exponent))
		));
	}
	else if (strstr(typeid(exponent).name(), "Fraction")) {
		return std::shared_ptr<Number>(new Complex(
			Root(dynamic_cast<const Fraction &>(exponent))
		));
	}
	else {
		throw "undefine";
	}
}
bool Integer::operator==(const Real &other) const {
	if (strstr(typeid(other).name(), "Integer")) {
		return *this == dynamic_cast<const Integer &>(other);
	}
	else {
		throw "undefine";
	}
}
bool Integer::operator<(const Real &other) const {
	if (strstr(typeid(other).name(), "Integer")) {
		return *this < dynamic_cast<const Integer &>(other);
	}
	else {
		throw "undefine";
	}
}
Integer::operator bool() const {
	return m_value;
}
Integer Integer::operator-() const {
	return Integer(m_value, !m_positive);
}
Integer Integer::operator!() const {
	Integer product(1);
	for (Natural index(1, m_value.GetRadix()); index <= m_value; ++index) {
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
Fraction Integer::operator+(const Fraction &addition) const {
	return Fraction(*this) + addition;
}
Fraction Integer::operator-(const Fraction &subtrahend) const {
	return Fraction(*this) - subtrahend;
}
Fraction Integer::operator*(const Fraction &multiplier) const {
	return Fraction(*this) * multiplier;
}
Fraction Integer::operator/(const Fraction &divisor) const {
	return Fraction(*this) / divisor;
}
Fraction Integer::Power(const Integer &exponent) const {
	Integer product = m_value.Power(exponent.m_value);
	product.m_positive = m_positive || 0 == exponent % Integer(2);
	if (exponent.m_positive) {
		return Fraction(product, 1);
	}
	else {
		return Fraction(1, product);
	}
}
Complex Integer::Root(const Integer &exponent) const {
	if (!m_positive && 0 == exponent % Integer(2)) {
	//	return Complex(0, m_value.Root(exponent.m_value));
	}
	else {
	//	return Complex(m_value.Root(exponent.m_value),0);
	}
	return Complex(0, 0);
}
Complex Integer::Power(const Fraction &exponent) const{
	return Fraction(*this, 1).Power(exponent);
}
Complex Integer::Root(const Fraction &exponent) const {
	return Fraction(*this, 1).Root(exponent);
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
