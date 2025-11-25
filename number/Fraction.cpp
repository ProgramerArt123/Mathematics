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
		DomainVerification();
		SetPositive(true);
		Reduce();
	}
	
	Fraction::Fraction(const number::Integer &numerator, const number::Integer &denominator, bool isUnSigned) :
		m_numerator(numerator.Value()), m_denominator(denominator.Value()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		DomainVerification();
		SetPositiveUnSigned(isUnSigned, numerator.IsPositive(), denominator.IsPositive());
		Reduce();
	}
	Fraction::Fraction(const number::Integer &numerator, const Fraction &denominator, bool isUnSigned) :
		m_numerator(numerator.Value()*denominator.Denominator()),
		m_denominator(denominator.Numerator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		DomainVerification();
		SetPositiveUnSigned(isUnSigned, numerator.IsPositive(), denominator.IsPositive());
		Reduce();
	}

	Fraction::Fraction(const Fraction &numerator, const number::Integer &denominator, bool isUnSigned) :
		m_numerator(numerator.Numerator()),
		m_denominator(denominator.Value()*numerator.Denominator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		DomainVerification();
		SetPositiveUnSigned(isUnSigned, numerator.IsPositive(), denominator.IsPositive());
		Reduce();
	}
	Fraction::Fraction(const Fraction &numerator, const Fraction &denominator, bool isUnSigned) :
		m_numerator(numerator.Numerator()*denominator.Denominator()),
		m_denominator(denominator.Numerator()*numerator.Denominator()),
		m_reduction_numerator(m_numerator), m_reduction_denominator(m_denominator) {
		DomainVerification();
		SetPositiveUnSigned(isUnSigned, numerator.IsPositive(), denominator.IsPositive());
		Reduce();
	}
	Fraction Fraction::Point(size_t point) const{
		return Fraction(m_numerator, m_denominator*Natural(1).CalcPower(point));
	}
	const std::string Fraction::GetString(uint8_t radix) const {
		const std::string negative = IsPositive() ? "" : "-";

		if(m_reduction_integer.EqualZero()){
			if (m_reduction_numerator.EqualZero() || m_reduction_denominator.EqualPositiveOne()) {
				return negative + m_reduction_numerator.GetString(radix);
			}
			else {
				return negative + m_reduction_numerator.GetString(radix) + "/" + m_reduction_denominator.GetString(radix);
			}
		}
		else {
			if (m_reduction_numerator.EqualZero()) {
				return negative + m_reduction_integer.GetString(radix);
			}
			else {
				return negative + m_reduction_integer.GetString(radix) + "[" + Fraction(m_reduction_numerator, m_reduction_denominator).GetString(radix) + "]";
			}
		}
	}
	bool Fraction::EqualZero() const {
		return m_reduction_integer.EqualZero() && m_reduction_numerator.EqualZero();
	}
	bool Fraction::EqualPositiveOne() const {
		if (!IsPositive()) {
			return false;
		}
		if (m_reduction_integer.EqualZero() && m_reduction_numerator == m_reduction_denominator) {
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
		if (m_reduction_integer.EqualZero() && m_reduction_numerator == m_reduction_denominator) {
			return true;
		}
		if (m_reduction_integer.EqualPositiveOne() && m_reduction_numerator.EqualZero()) {
			return true;
		}
		return false;
	}
	const Natural &Fraction::Numerator() const {
		return m_numerator;
	}
	const Natural &Fraction::ReductionNumerator() const {
		return m_reduction_numerator;
	}
	const Natural &Fraction::Denominator() const {
		return m_denominator;
	}
	const Natural &Fraction::ReductionDenominator() const {
		return m_reduction_denominator;
	}
	const Natural &Fraction::ReductionInteger() const {
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

		std::pair<Natural, Natural> quotient(m_numerator.Div(m_denominator));

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
			quotient = dividend.Div(m_denominator);
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

		const number::Natural &common = m_denominator.GreatestCommonDivisor(m_numerator);
		
		m_reduction_numerator = m_numerator / common;
		m_reduction_denominator = m_denominator / common;

		m_reduction_integer = m_reduction_numerator / m_reduction_denominator;
		m_reduction_numerator = m_reduction_numerator % m_reduction_denominator;

	}

	void Fraction::DomainVerification() const {
		DenominatorDomainVerification(m_denominator);
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
		if (IsPositive() && addition.IsPositive()) {
			return Fraction((m_numerator * addition.m_denominator) +
				(addition.m_numerator * m_denominator),
				m_denominator * addition.m_denominator);
		}
		else if (!addition.IsPositive()) {
			return Fraction(Integer(m_numerator * addition.m_denominator) -
				Integer(addition.m_numerator * m_denominator),
				m_denominator * addition.m_denominator);
		}
		else {
			return Fraction(Integer(addition.m_numerator * m_denominator) -
				Integer(m_numerator * addition.m_denominator),
				m_denominator * addition.m_denominator);
		}
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
		if (0 < length && length < m_numerator.CalcOrders()) {
			const Natural &exponent = Natural(1).CalcPower(m_numerator.CalcOrders() - length);
			return Fraction(Integer(m_numerator / exponent, IsPositive()), m_denominator / exponent);
		}
		else{
			return *this;
		}
	}
	Fraction Fraction::Power(const number::Integer & base, const number::Integer &exponent) {
		number::Integer product = base.Value().Power(exponent.Value());
		product.SetPositive(product.IsPositive() || !exponent.Value().IsOdd());
		if (exponent.IsPositive()) {
			return Fraction(product, 1);
		}
		else {
			return Fraction(1, product);
		}
	}
	std::optional<Fraction> Fraction::CheckReduce(const Integer &numerator, const Integer &denominator) {
		const number::Fraction reduce(numerator.Value(), denominator.Value());
		if (reduce.ReductionInteger().EqualZero() &&
			reduce.ReductionNumerator() == numerator.Value()) {
			return std::nullopt;
		}
		else {
			return reduce;
		}
	}
	void Fraction::DenominatorDomainVerification(const Natural &denominator) {
		if (denominator.EqualZero()) {
			throw std::exception("Domain Undefined : Fraction Denominator Can not 0");
		}
	}
	void Fraction::SetPositiveUnSigned(bool isUnSigned, bool isNumeratorPositive, bool isDenominatorPositive)
	{
		SetPositive((m_numerator.EqualZero()) || 
			(isUnSigned == (isNumeratorPositive == isDenominatorPositive)));
	}
}