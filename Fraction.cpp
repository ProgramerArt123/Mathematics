#include <cassert>
#include "Integer.h"
#include "Complex.h"
#include "Fraction.h"

Fraction::Fraction():
	m_numerator(new Integer(0)), m_denominator(new Integer(UINT64_MAX)) {

}
Fraction::Fraction(const Integer &significant) :
	m_numerator(new Integer(significant)), m_denominator(new Integer(1)) {
}
Fraction::Fraction(const Integer &numerator, const Integer &denominator) :
	m_numerator(new Integer(numerator)), m_denominator(new Integer(denominator)) {
	assert(0 != m_denominator);
	m_numerator->SetRadix(m_denominator->GetRadix());
	Reduce();
	if (m_numerator->EqualZero()) {
		m_numerator->SetPositive(true);
	}
	else if (m_numerator->IsPositive() ==
		m_denominator->IsPositive()) {
		m_denominator->SetPositive(true);
		m_numerator->SetPositive(true);
	}
	else if(!m_denominator->IsPositive()){
		m_denominator->SetPositive(true);
		m_numerator->SetPositive(false);
	}
}
Fraction::Fraction(const Integer &numerator, const Fraction &denominator) {
	*this = numerator / denominator;
}
Fraction::Fraction(const Fraction &numerator, const Integer &denominator) {
	*this = numerator / denominator;
}
Fraction::Fraction(const Fraction &numerator, const Fraction &denominator) {
	*this = numerator / denominator;
}
Fraction &Fraction::SetPointPos(size_t point) {
	std::string denominator = "1";
	denominator.append(point, '0');
	m_denominator = std::shared_ptr<Integer>(new Integer(Natural(denominator)));
	m_denominator->SetRadix(m_numerator->GetRadix());
	return *this;
}
const std::string Fraction::GetString(uint8_t radix) const {
	if (m_numerator->EqualZero()) {
		return m_numerator->GetString(radix);
	}
	else if (Integer(1) == *m_denominator) {
		return m_numerator->GetString(radix);
	}
	else {
		return m_numerator->GetString(radix) + "/" + m_denominator->GetString(radix);
	}
}
void Fraction::SetRadix(uint8_t radix) {
	m_numerator->SetRadix(radix);
	m_denominator->SetRadix(radix);
}
uint8_t Fraction::GetRadix() const {
	return m_denominator->GetRadix();
}
bool Fraction::EqualZero() const {
	return m_numerator->EqualZero();
}
void Fraction::SetPositive(bool isPositive) {
	m_numerator->SetPositive(isPositive);
	m_denominator->SetPositive(true);
}
bool Fraction::IsPositive() const {
	return m_numerator->IsPositive() == 
		m_denominator->IsPositive();
}
std::shared_ptr<Real> Fraction::operator+(const Real &addition) const {
	if (strstr(typeid(addition).name(), "Integer")) {
		return std::shared_ptr<Real>(new Fraction(
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
std::shared_ptr<Real> Fraction::operator-(const Real &subtrahend) const {
	if (strstr(typeid(subtrahend).name(), "Integer")) {
		return std::shared_ptr<Real>(new Fraction(
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
std::shared_ptr<Real> Fraction::operator*(const Real &multiplier) const {
	if (strstr(typeid(multiplier).name(), "Integer")) {
		return std::shared_ptr<Real>(new Fraction(
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
std::shared_ptr<Real> Fraction::operator/(const Real &divisor) const {
	if (strstr(typeid(divisor).name(), "Integer")) {
		return std::shared_ptr<Real>(new Fraction(
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
std::shared_ptr<Number> Fraction::Power(const Real &exponent) const {
	if (strstr(typeid(exponent).name(), "Integer")) {
		return std::shared_ptr<Number>(new Complex(
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
std::shared_ptr<Number> Fraction::Root(const Real &exponent) const {
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
bool Fraction::operator==(const Real &other) const {
	if (strstr(typeid(other).name(), "Fraction")) {
		return *this == dynamic_cast<const Fraction &>(other);
	}
	else {
		throw "undefine";
	}
}
bool Fraction::operator<(const Real &other) const {
	if (strstr(typeid(other).name(), "Fraction")) {
		return *this < dynamic_cast<const Fraction &>(other);
	}
	else {
		throw "undefine";
	}
}
const std::string Fraction::GetDecimal(uint8_t radix, size_t decimalLength, 
	std::function<bool(char)> round) const {
	Natural quotient(0, m_denominator->GetRadix()), remainder(0, m_denominator->GetRadix());
	std::string numeratorStr = m_numerator->GetString(radix);
	numeratorStr.append(decimalLength + 1, '0');
	Natural(numeratorStr, radix).Div(m_denominator->GetNatural(), quotient.SetCheckLoop(), remainder);
	const std::string &loop = quotient.GetLoop();
	std::string quotientStr = quotient.GetString(radix);
	if (quotientStr.length() < decimalLength + 2) {
		quotientStr.insert(0, decimalLength + 2 - quotientStr.length(), '0');
	}
	std::string decimalStr = quotientStr.substr(0, quotientStr.length() - decimalLength - 1) +
		"." + quotientStr.substr(quotientStr.length() - decimalLength - 1);
	if (remainder.EqualZero()) {
		while ('0' == decimalStr.back()){
			decimalStr.pop_back();
		}
		if ('.' == decimalStr.back()) {
			decimalStr.pop_back();
		}
	}
	if (decimalStr.find('.')!=std::string::npos && 
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
			return ((Fraction(Integer(Natural(quotientStr, radix), IsPositive()))
				+ Natural(1, radix)) / Natural(denominator, radix)).GetDecimal(radix, decimalLength, round);
		}
	}
	else {
		return IsPositive() ? decimalStr + loop : "-" + decimalStr + loop;
	}
}

void Fraction::Reduce() {
	const Integer &common = m_denominator->m_value.GreatestCommonDivisor(m_numerator->m_value);
	*m_numerator /= common;
	*m_denominator /= common;
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
	return *m_numerator * *other.m_denominator <
		*other.m_numerator * *m_denominator;
}
bool Fraction::operator==(const Fraction &other) const {
	return *m_numerator * *other.m_denominator ==
		*other.m_numerator * *m_denominator;
}
Fraction Fraction::operator+(const Fraction &addition) const {
	return Fraction((*m_numerator * *addition.m_denominator) +
		(*addition.m_numerator * *m_denominator),
		*m_denominator * *addition.m_denominator);
}
Fraction Fraction::operator-(const Fraction &subtrahend) const {
	return *this + (-subtrahend);
}
Fraction Fraction::operator*(const Fraction &multiplier) const {
	return Fraction(*m_numerator * *multiplier.m_numerator,
		*m_denominator * *multiplier.m_denominator);
}
Fraction &Fraction::operator+=(const Fraction &addition) {
	return *this = *this + addition;
}
Fraction &Fraction::operator*=(const Fraction &multiplier) {
	return *this = *this * multiplier;
}
Fraction &Fraction::operator/=(const Fraction &divisor) {
	return *this = *this / divisor;
}
Fraction Fraction::operator/(const Fraction &divisor) const {
	assert(0 != divisor.m_numerator);
	return *this * Fraction(*divisor.m_denominator, *divisor.m_numerator);
}
Complex Fraction::Power(const Fraction &exponent) const {
	return m_numerator->Power(*exponent.m_numerator).Root(*exponent.m_denominator) /
		m_denominator->Power(*exponent.m_numerator).Root(*exponent.m_denominator);
}
Complex Fraction::Root(const Fraction &exponent) const {
	return Power(Fraction(*exponent.m_denominator, *exponent.m_numerator));
}
Complex Fraction::Power(const Integer &exponent) const {
	return Complex(m_numerator->Power(exponent), 0) /
		m_denominator->Power(exponent);
}
Complex Fraction::Root(const Integer &exponent) const {
	return m_numerator->Root(exponent) /
		m_denominator->Root(exponent);
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
