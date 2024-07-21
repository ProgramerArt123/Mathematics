#include <cassert>
#include <iostream>
#include "Integer.h"
#include "Complex.h"
#include "Fraction.h"
namespace number {
	Fraction::Fraction() :
		m_numerator(0), m_denominator(UINT64_MAX) {
		Reduce();
	}
	Fraction::Fraction(const number::Integer &significant) :
		m_numerator(significant), m_denominator(1) {
		Reduce();
	}
	Fraction::Fraction(const number::Integer &numerator, const number::Integer &denominator) :
		m_numerator(numerator), m_denominator(denominator) {
		assert(0 != m_denominator);
		m_numerator.SetRadix(m_denominator.GetRadix());
		Reduce();
		if (m_numerator.EqualZero()) {
			m_numerator.SetPositive(true);
		}
		else if (m_numerator.IsPositive() ==
			m_denominator.IsPositive()) {
			m_denominator.SetPositive(true);
			m_numerator.SetPositive(true);
		}
		else if (!m_denominator.IsPositive()) {
			m_denominator.SetPositive(true);
			m_numerator.SetPositive(false);
		}
	}
	Fraction::Fraction(const number::Integer &numerator, const Fraction &denominator) {
		*this = numerator / denominator;
	}
	Fraction::Fraction(const Fraction &numerator, const number::Integer &denominator) {
		*this = numerator / denominator;
	}
	Fraction::Fraction(const Fraction &numerator, const Fraction &denominator) {
		*this = numerator / denominator;
	}
	Fraction &Fraction::SetPointPos(size_t point) {
		std::string denominator = "1";
		denominator.append(point, '0');
		m_denominator = number::Integer(Natural(denominator));
		m_denominator.SetRadix(m_numerator.GetRadix());
		return *this;
	}
	const std::string Fraction::GetString(uint8_t radix) const {
		if (m_numerator.EqualZero()) {
			return m_numerator.GetString(radix);
		}
		else if (number::Integer(1) == m_denominator) {
			return m_numerator.GetString(radix);
		}
		else if(m_reduction_integer.EqualZero()){
			return m_reduction_numerator.GetString(radix) + "/" + m_denominator.GetString(radix);
		}
		else {
			return m_reduction_integer.GetString(radix) + "[" + m_reduction_numerator.GetString(radix) + "/" + m_denominator.GetString(radix) + "]";
		}
	}
	void Fraction::SetRadix(uint8_t radix) {
		m_numerator.SetRadix(radix);
		m_denominator.SetRadix(radix);
	}
	uint8_t Fraction::GetRadix() const {
		return m_denominator.GetRadix();
	}
	bool Fraction::EqualZero() const {
		return m_numerator.EqualZero();
	}
	void Fraction::SetPositive(bool isPositive) {
		m_numerator.SetPositive(isPositive);
		m_denominator.SetPositive(true);
	}
	bool Fraction::IsPositive() const {
		return m_numerator.IsPositive() ==
			m_denominator.IsPositive();
	}
	const Integer &Fraction::Numerator() const {
		return m_numerator;
	}
	const Integer &Fraction::ReductionNumerator() const {
		return m_reduction_numerator;
	}
	const Integer &Fraction::Denominator() const {
		return m_denominator;
	}
	const Integer &Fraction::Integer() const {
		return m_reduction_integer;
	}
	Fraction Fraction::GetAbs() const {
		if (IsPositive()) {
			return *this;
		}
		else {
			return -*this;
		}
	}

	Fraction Fraction::GetReciprocal() const {
		return Fraction(m_denominator, m_numerator);
	}

	bool Fraction::IsInteger() const {
		return Denominator().GetAbs() == number::Integer(1);
	}

	void Fraction::Opposite() {
		m_numerator.Opposite();
		m_reduction_integer.Opposite();
		m_reduction_numerator.Opposite();
	}

	const std::string Fraction::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		Natural quotient(0, m_denominator.GetRadix()), remainder(0, m_denominator.GetRadix());
		std::string numeratorStr = m_numerator.Value().GetString(radix);
		numeratorStr.append(decimalLength + 1, '0');
		Natural(numeratorStr, radix).Div(m_denominator.Value(), quotient.SetCheckLoop(), remainder);
		const std::string &loop = quotient.GetLoop();
		std::string quotientStr = quotient.GetString(radix);
		if (quotientStr.length() < decimalLength + 2) {
			quotientStr.insert(0, decimalLength + 2 - quotientStr.length(), '0');
		}
		std::string decimalStr = quotientStr.substr(0, quotientStr.length() - decimalLength - 1) +
			"." + quotientStr.substr(quotientStr.length() - decimalLength - 1);
		if (remainder.EqualZero()) {
			while ('0' == decimalStr.back()) {
				decimalStr.pop_back();
			}
			if ('.' == decimalStr.back()) {
				decimalStr.pop_back();
			}
		}
		if (decimalStr.find('.') != std::string::npos &&
			decimalStr.size() - decimalStr.find('.') > decimalLength) {
			const char last = decimalStr.back();
			decimalStr.pop_back();
			if (!round(last)) {
				if (!loop.empty()) {
					return IsPositive() ? decimalStr + loop : "-" + decimalStr + loop;
				}
				else {
					return IsPositive() ? decimalStr + "..." : "-" + decimalStr + "...";
				}
			}
			else {
				std::string denominator = "1";
				denominator.append(decimalLength + 1, '0');
				return ((Fraction(number::Integer(Natural(quotientStr, radix), IsPositive()))
					+ Natural(1, radix)) / Natural(denominator, radix)).GetDecimal(radix, decimalLength, round);
			}
		}
		else {
			return IsPositive() ? decimalStr + loop : "-" + decimalStr + loop;
		}
	}

	void Fraction::Reduce() {
		const number::Integer &common = m_denominator.Value().GreatestCommonDivisor(m_numerator.Value());
		m_numerator /= common;
		m_denominator /= common;
		m_reduction_integer = m_numerator / m_denominator;
		m_reduction_numerator = m_numerator % m_denominator;
	}

	Fraction Fraction::operator-() const {
		Fraction negative(*this);
		negative.SetPositive(!negative.IsPositive());
		return negative;
	}
	bool Fraction::operator<(const Fraction &other) const {
		if (IsPositive() < other.IsPositive()) {
			return true;
		}
		else if (IsPositive() > other.IsPositive()) {
			return false;
		}
		return m_numerator * other.m_denominator <
			other.m_numerator * m_denominator;
	}
	bool Fraction::operator==(const Fraction &other) const {
		return m_numerator * other.m_denominator ==
			other.m_numerator * m_denominator;
	}
	Fraction Fraction::operator+(const Fraction &addition) const {
		return Fraction((m_numerator * addition.m_denominator) +
			(addition.m_numerator * m_denominator),
			m_denominator * addition.m_denominator);
	}
	Fraction Fraction::operator-(const Fraction &subtrahend) const {
		return *this + (-subtrahend);
	}
	Fraction Fraction::operator*(const Fraction &multiplier) const {
		return Fraction(m_numerator * multiplier.m_numerator,
			m_denominator * multiplier.m_denominator);
	}
	Fraction &Fraction::operator+=(const Fraction &addition) {
		return *this = *this + addition;
	}
	Fraction &Fraction::operator-=(const Fraction &subtrahend) {
		return *this = *this - subtrahend;
	}
	Fraction &Fraction::operator*=(const Fraction &multiplier) {
		return *this = *this * multiplier;
	}
	Fraction &Fraction::operator/=(const Fraction &divisor) {
		return *this = *this / divisor;
	}
	Fraction Fraction::operator/(const Fraction &divisor) const {
		assert(0 != divisor.m_numerator);
		return *this * Fraction(divisor.m_denominator, divisor.m_numerator);
	}
	Fraction Fraction::Power(const number::Integer &exponent) const {
		return Power(m_numerator, exponent) / Power(m_denominator, exponent);
	}
	bool operator==(const Integer &number, const Fraction &rational) {
		return Fraction(number) == rational;
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
	Fraction Fraction::Power(const number::Integer &number, const number::Integer &exponent) {
		number::Integer product = number.Value().Power(exponent.Value());
		product.SetPositive(product.IsPositive() || 0 == exponent.Value() % Natural(2));
		if (exponent.IsPositive()) {
			return Fraction(product, 1);
		}
		else {
			return Fraction(1, product);
		}
	}
}