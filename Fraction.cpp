#include <cassert>
#include "Integer.h"
#include "Fraction.h"

Fraction::Fraction() {

}
Fraction::Fraction(const Integer &significant) :
	m_numerator(significant), m_denominator(1) {
}
Fraction::Fraction(const Integer &numerator, const Integer &denominator) :
	m_numerator(numerator), m_denominator(denominator) {
	assert(0 != m_denominator);
	m_numerator.m_value = m_numerator.m_value.GetNDecimal(m_denominator.m_value.GetBase());
	const Integer &common = m_numerator.GreatestCommonDivisor(m_denominator);
	m_numerator /= common;
	m_denominator /= common;
	if (Integer(0) == m_numerator) {
		m_denominator.m_positive = true;
	}
}
Fraction &Fraction::SetPointPos(size_t point) {
	std::string denominator = "1";
	denominator.append(point, '0');
	m_denominator = NDecimal(denominator, m_numerator.m_value.GetBase());
	return *this;
}
const std::string Fraction::GetString(uint8_t base) const {
	return m_numerator.m_positive == m_denominator.m_positive ?
		m_numerator.m_value.GetString(base) + "/" + m_denominator.m_value.GetString(base) : "-" +
		m_numerator.m_value.GetString(base) + "/" + m_denominator.m_value.GetString(base);
}
const std::string Fraction::GetDecimal(uint8_t base, size_t decimalLength, 
	std::function<bool(char)> round) const {
	const std::string baseStr = "[base=" + std::to_string(base) + "]";
	NDecimal integer(0, m_denominator.m_value.GetBase()), integerRemainder(0, m_denominator.m_value.GetBase());
	m_numerator.m_value.Div(m_denominator.m_value, integer, integerRemainder);
	const std::string &integerStr = integer.GetString(base);
	if (!integerRemainder) {
		return m_numerator.m_positive == m_denominator.m_positive ?
			integerStr + baseStr : "-" + integerStr + baseStr;
	}
	std::string integerRemainderStr = integerRemainder.GetString(base);
	integerRemainderStr.append(decimalLength + 1, '0');
	NDecimal decimal(0, m_denominator.m_value.GetBase()), decimalRemainder(0, m_denominator.m_value.GetBase());
	NDecimal(integerRemainderStr, base).Div(m_denominator.m_value, decimal.SetCheckLoop(), decimalRemainder);
	const std::string &loop = decimal.GetLoop();
	std::string decimalStr = decimal.GetString(base);
	const std::string fill(decimalLength + 1 - decimalStr.size(), '0');
	if (!decimalRemainder) {
		while ('0' == decimalStr.back()){
			decimalStr.pop_back();
		}
	}
	if (decimalStr.size() > decimalLength) {
		const char last = decimalStr.back();
		decimalStr.pop_back();
		if (!round(decimalStr.back())) {
			if (!loop.empty()) {
				return m_numerator.m_positive == m_denominator.m_positive ?
					integerStr + "." + fill + decimalStr + loop + baseStr : "-" +
					integerStr + "." + fill + decimalStr + loop + baseStr;
			}
			else {
				return m_numerator.m_positive == m_denominator.m_positive ?
					integerStr + "." + fill + decimalStr + "..." + baseStr : "-" +
					integerStr + "." + fill + decimalStr + "..." + baseStr;
			}
		}
		else {
			std::string denominator = "1";
			denominator.append((fill + decimalStr).length(), '0');
			return ((Fraction(Integer(NDecimal(integerStr + fill + decimalStr, base), IsPositive()))
				+ NDecimal(1, base)) / NDecimal(denominator, base)).GetDecimal(base, decimalLength, round);
		}
	}
	else {
		return m_numerator.m_positive == m_denominator.m_positive ?
			integerStr + "." + fill + decimalStr + loop + baseStr : "-" +
			integerStr + "." + fill + decimalStr + loop + baseStr;
	}
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
	Integer selfNumerator = NDecimal(0, m_denominator.m_value.GetBase());
	Integer otherNumerator = NDecimal(0, m_denominator.m_value.GetBase());
	Integer selfDenominator = NDecimal(UINT64_MAX, m_denominator.m_value.GetBase());
	Integer otherDenominator = NDecimal(UINT64_MAX, m_denominator.m_value.GetBase());
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
bool operator==(const Integer &number, const Fraction &rational) {
	return Fraction(number) == rational;
}

Fraction operator+(const Integer &number, const Fraction &addition) {
	return Fraction(number) + addition;
}
Fraction operator-(const Integer &number, const Fraction &subtrahend) {
	return Fraction(number) - subtrahend;
}
Fraction operator*(const Integer &number, const Fraction &multiplier) {
	return Fraction(number) * multiplier;
}
Fraction operator/(const Integer &number, const Fraction &divisor) {
	return Fraction(number) / divisor;
}
Fraction operator+(const Fraction &number, const Integer &addition) {
	return number + Fraction(addition);
}
Fraction operator-(const Fraction &number, const Integer &subtrahend) {
	return number - Fraction(subtrahend);
}
Fraction operator*(const Fraction &number, const Integer &multiplier) {
	return number * Fraction(multiplier);
}
Fraction operator/(const Fraction &number, const Integer &divisor) {
	return number / Fraction(divisor);
}