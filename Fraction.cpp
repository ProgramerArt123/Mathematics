#include <cassert>
#include "Integer.h"
#include "Fraction.h"

Fraction::Fraction(int64_t value) :
	Fraction(Integer(value >= 0 ? value : -value, value >= 0)) {
}
Fraction::Fraction(const Integer &integer) :
	m_numerator(integer), m_denominator(1) {
}
Fraction::Fraction(const Integer &numerator, const Integer &denominator) :
	m_numerator(numerator), m_denominator(denominator) {
	assert(0 != m_denominator);
	const Integer &common = m_numerator.GreatestCommonDivisor(m_denominator);
	m_numerator /= common;
	m_denominator /= common;
	if (Integer(0) == m_numerator) {
		m_denominator.m_positive = true;
	}
}
const std::string Fraction::GetString(uint8_t base) const {
	return m_numerator.m_positive == m_denominator.m_positive ?
		m_numerator.m_value.GetString(base) + "/" + m_denominator.m_value.GetString(base) : "-" +
		m_numerator.m_value.GetString(base) + "/" + m_denominator.m_value.GetString(base);
}
bool Fraction::IsPositive() const {
	return m_numerator.m_positive == m_denominator.m_positive;
}
Fraction Fraction::operator-() const {
	return Fraction(-m_numerator, m_denominator);
}
bool Fraction::operator<(const Fraction &other) const {
	if (m_numerator.m_positive * m_denominator.m_positive <
		other.m_numerator.m_positive * other.m_denominator.m_positive) {
		return true;
	}
	return m_numerator.m_positive * m_denominator.m_positive ==
		m_numerator * other.m_denominator < other.m_numerator * m_denominator;
}
bool Fraction::operator==(const Fraction &other) const {
	return m_denominator == other.m_denominator &&
		m_numerator == other.m_numerator;
}
Fraction Fraction::operator+(const Fraction &addition) const {
	const Integer &common = m_denominator.GreatestCommonDivisor(addition.m_denominator);
	const Integer &selfNumerator = m_numerator * (addition.m_denominator / common);
	const Integer &otherNumerator = addition.m_numerator * (m_denominator / common);
	const Integer &x = selfNumerator + otherNumerator;
	const Integer &y = m_denominator * (addition.m_denominator / common);
	return Fraction(selfNumerator + otherNumerator,
		m_denominator * (addition.m_denominator / common));
}
Fraction Fraction::operator-(const Fraction &subtrahend) const {
	return *this + (-subtrahend);
}
Fraction Fraction::operator*(const Fraction &multiplier) const {
	Integer selfNumerator = BitSet(0);
	Integer otherNumerator = BitSet(0);
	Integer selfDenominator = BitSet(UINT64_MAX);
	Integer otherDenominator = BitSet(UINT64_MAX);
	{
		const Integer &common = m_numerator.GreatestCommonDivisor(multiplier.m_denominator);
		selfNumerator = m_numerator / common;
		otherDenominator = multiplier.m_denominator / common;
	}
	{
		const Integer &common = m_denominator.GreatestCommonDivisor(multiplier.m_numerator);
		selfDenominator = m_denominator / common;
		otherNumerator = multiplier.m_numerator / common;
	}
	return Fraction(selfNumerator * otherNumerator,
		selfDenominator * otherDenominator);
}
Fraction &Fraction::operator+=(const Fraction &addition) {
	return *this = *this + addition;
}
Fraction &Fraction::operator*=(const Fraction &multiplier) {
	return *this = *this * multiplier;
}
Fraction Fraction::operator/(const Fraction &divisor) const {
	assert(0 != divisor.m_numerator);
	return *this * Fraction(divisor.m_denominator, divisor.m_numerator);
}
bool operator==(int number, const Fraction &rational) {
	return Fraction(number) == rational;
}
Fraction operator-(int number, const Fraction &rational) {
	return Fraction(number) - rational;
}
Fraction operator+(const Integer &number, const Fraction &addition) {
	return Fraction(number, Integer(1)) + addition;
}
Fraction operator-(const Integer &number, const Fraction &subtrahend) {
	return Fraction(number, Integer(1)) - subtrahend;
}
Fraction operator*(const Integer &number, const Fraction &multiplier) {
	return Fraction(number, Integer(1)) * multiplier;
}
Fraction operator/(const Integer &number, const Fraction &divisor) {
	return Fraction(number, Integer(1)) / divisor;
}
Fraction operator+(const Fraction &number, const Integer &addition) {
	return number + Fraction(addition, Integer(1));
}
Fraction operator-(const Fraction &number, const Integer &subtrahend) {
	return number - Fraction(subtrahend, Integer(1));
}
Fraction operator*(const Fraction &number, const Integer &multiplier) {
	return number * Fraction(multiplier, Integer(1));
}
Fraction operator/(const Fraction &number, const Integer &divisor) {
	return number / Fraction(divisor, Integer(1));
}