#include <cassert>
#include <iostream>
#include <map>
#include "Integer.h"
#include "Complex.h"
#include "Fraction.h"
namespace number {
	Fraction::Fraction() :
		m_numerator(0), m_denominator(UINT64_MAX),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		Reduce();
	}
	Fraction::Fraction(const number::Integer &significant) :
		m_numerator(significant), m_denominator(1),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		Reduce();
	}
	Fraction::Fraction(const number::Integer &numerator, const number::Integer &denominator) :
		m_numerator(numerator), m_denominator(denominator),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		assert(!m_denominator.EqualZero());
		Reduce();
	}
	Fraction::Fraction(const number::Integer &numerator, const Fraction &denominator) :
		m_numerator(numerator*denominator.Denominator()),
		m_denominator(denominator.Numerator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		assert(!m_denominator.EqualZero());
		Reduce();
	}

	Fraction::Fraction(const Fraction &numerator, const number::Integer &denominator) :
		m_numerator(numerator.Numerator()),
		m_denominator(denominator*numerator.Denominator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		assert(!m_denominator.EqualZero());
		Reduce();
	}
	Fraction::Fraction(const Fraction &numerator, const Fraction &denominator) :
		m_numerator(numerator.Numerator()*denominator.Denominator()),
		m_denominator(denominator.Numerator()*numerator.Denominator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		assert(!m_denominator.EqualZero());
		Reduce();
	}
	Fraction Fraction::Point(size_t point) const{
		return Fraction(m_numerator, m_denominator*Natural(1).CalcPower(point));
	}
	const std::string Fraction::GetString(uint8_t radix) const {
		if(m_reduction_integer.EqualZero()){
			if (m_reduction_numerator.EqualZero() || m_reduction_denominator.EqualPositiveOne()) {
				return m_reduction_numerator.GetString(radix);
			}
			else if (m_reduction_denominator.EqualNegativeOne()) {
				return (-m_reduction_numerator).GetString(radix);
			}
			else {
				return m_reduction_numerator.GetString(radix) + "/" + m_reduction_denominator.GetString(radix);
			}
		}
		else {
			return m_reduction_integer.GetString(radix) + "[" + Fraction(Numerator() % Denominator(), Denominator()).GetString(radix) + "]";
		}
	}
	bool Fraction::EqualZero() const {
		return m_reduction_integer.EqualZero() && m_reduction_numerator.EqualZero();
	}
	bool Fraction::EqualPositiveOne() const {
		if (!IsPositive()) {
			return false;
		}
		if (m_reduction_integer.EqualZero() && m_reduction_numerator.GetAbs() == m_reduction_denominator.GetAbs()) {
			return true;
		}
		if (m_reduction_integer.EqualPositiveOne() && m_reduction_numerator.EqualZero()) {
			return true;
		}
		return false;
	}
	bool Fraction::EqualNegativeOne() const {
		if (IsPositive()) {
			return false;
		}
		if (m_reduction_integer.EqualZero() && m_reduction_numerator.GetAbs() == m_reduction_denominator.GetAbs()) {
			return true;
		}
		if (m_reduction_integer.EqualPositiveOne() && m_reduction_numerator.EqualZero()) {
			return true;
		}
		return false;
	}
	void Fraction::SetUnSigned(bool isUnSigned) {
		m_numerator.SetUnSigned(isUnSigned);
		m_denominator.SetUnSigned(true);
		Reduce();
	}
	bool Fraction::IsPositive() const {
		return m_numerator.IsPositive() ==
			m_denominator.IsPositive();
	}
	void Fraction::Opposite() {
		m_numerator.Opposite();
		m_reduction_numerator.Opposite();
		m_reduction_integer.Opposite();
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
	const Integer &Fraction::ReductionDenominator() const {
		return m_reduction_denominator;
	}
	const Integer &Fraction::ReductionInteger() const {
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
		return ReductionDenominator().EqualPositiveOne() || ReductionDenominator().EqualNegativeOne();
	}

	const std::string Fraction::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {

		if (IsInteger()) {
			return m_reduction_integer.GetDecimal(radix, decimalLength, round);
		}

		std::pair<Natural, Natural> quotient(m_numerator.Value().Div(m_denominator.Value()));

		std::string literal = quotient.first.GetDecimal(radix, decimalLength, round) + ".";

		std::map<std::string, size_t> remainders;
		size_t loopBegin = SIZE_MAX, loopEnd = SIZE_MAX;
		bool isRemainder = true;
		for (size_t index = 0; index < decimalLength + 1; index++) {
			const Natural &dividend = quotient.second.CalcPower(1);
			if (SIZE_MAX == loopBegin) {
				const std::string &dividendStr = dividend.GetString();
				if (remainders.find(dividendStr) != remainders.end()) {
					loopBegin = remainders.at(dividendStr);
					loopEnd = literal.length();
				}
				else {
					remainders.emplace(dividendStr, literal.length());
				}
			}
			quotient = dividend.Div(m_denominator.Value());
			literal += quotient.first.GetDecimal(radix, decimalLength, round);
			if (quotient.second.EqualZero()) {
				isRemainder = false;
				break;
			}
		}
		if (isRemainder) {
			std::string loop = "...";
			if (SIZE_MAX != loopBegin) {
				loop = "{" + literal.substr(loopBegin, loopEnd - loopBegin) + "}";
			}
			while ('0' == literal.back()) {
				literal.pop_back();
			}
			if ('.' == literal.back()) {
				literal.pop_back();
			}
			return IsPositive() ? literal + loop : "-" + literal + loop;
		}
		else {
			const std::string &trim = literal.substr(0, literal.length() - 1);
			const char last = literal.back();
			if (!round(last)) {
				return IsPositive() ? trim + "..." : "-" + trim + "...";
			}
			else {
				const std::string &integer = trim.substr(0, trim.length() - decimalLength - 1);
				const std::string &decimal = trim.substr(trim.length() - decimalLength);
				const number::Natural &fixed = number::Natural(integer + decimal) + number::Natural(1);
				return Fraction(Integer(fixed, IsPositive()), number::Natural(1).
					CalcPower(decimalLength)).GetDecimal(radix, decimalLength - 1);
			}
		}
	}

	void Fraction::Reduce() {

		m_numerator.SetUnSigned(IsPositive());
		m_denominator.SetUnSigned(true);

		const number::Integer &common = m_denominator.Value().GreatestCommonDivisor(m_numerator.Value());
		
		m_reduction_numerator = m_numerator / common;
		m_reduction_denominator = m_denominator / common;

		m_reduction_integer = m_reduction_numerator / m_reduction_denominator;
		m_reduction_numerator = m_reduction_numerator % m_reduction_denominator;

	}

	Fraction Fraction::operator-() const {
		Fraction negative(*this);
		negative.Opposite();
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
	bool Fraction::operator>(const Fraction &other) const {
		if (IsPositive() > other.IsPositive()) {
			return true;
		}
		else if (IsPositive() < other.IsPositive()) {
			return false;
		}
		return m_numerator * other.m_denominator >
			other.m_numerator * m_denominator;
	}
	bool Fraction::operator==(const Fraction &other) const {
		return m_numerator * other.m_denominator ==
			other.m_numerator * m_denominator;
	}
	bool Fraction::operator!=(const Fraction &other) const {
		return !(*this == other);
	}
	bool Fraction::operator<=(const Fraction &other) const {
		return *this < other || *this == other;
	}
	bool Fraction::operator>=(const Fraction &other) const {
		return *this > other || *this == other;
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
		assert(!divisor.m_numerator.EqualZero());
		return *this * Fraction(divisor.m_denominator, divisor.m_numerator);
	}
	Fraction Fraction::Power(const number::Integer &exponent) const {
		return Power(m_numerator, exponent) / Power(m_denominator, exponent);
	}
	bool operator==(const Integer &number, const Fraction &rational) {
		return Fraction(number) == rational;
	}
	bool operator!=(const number::Integer &number, const Fraction &rational) {
		return !(number == rational);
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
	Fraction Fraction::CalcApproximation(size_t length) const {
		if (0 < length && length < m_numerator.Value().CalcOrders()) {
			const Natural &exponent = Natural(1).CalcPower(m_numerator.Value().CalcOrders() - length);
			return Fraction(Integer(m_numerator.Value() / exponent, IsPositive()), m_denominator.Value() / exponent);
		}
		else{
			return *this;
		}
	}
	Fraction Fraction::Power(const number::Integer & base, const number::Integer &exponent) {
		number::Integer product = base.Value().Power(exponent.Value());
		product.SetUnSigned(product.IsPositive() || !exponent.Value().IsOdd());
		if (exponent.IsPositive()) {
			return Fraction(product, 1);
		}
		else {
			return Fraction(1, product);
		}
	}
	bool Fraction::CheckReduce(const Integer &numerator, const Integer &denominator) {
		const number::Fraction reduce(numerator.Value(), denominator.Value());
		return reduce.ReductionInteger().EqualZero() &&
			reduce.ReductionNumerator() == numerator.Value();
	}
}