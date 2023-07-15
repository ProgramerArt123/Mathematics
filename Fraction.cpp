#include <cassert>
#include "Integer.h"
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
	m_numerator->SetBase(m_denominator->GetBase());
	if (m_numerator->EqualZero()) {
		m_denominator->SetPositive(true);
	}
}
Fraction::Fraction(const Integer &numerator, const Fraction &denominator) :
	m_numerator(new Integer(numerator)), m_denominator(new Fraction(denominator)) {

}
Fraction::Fraction(const std::shared_ptr<Real> &numerator, 
	const std::shared_ptr<Real> &denominator):m_numerator(numerator), m_denominator(denominator) {

}
Fraction &Fraction::SetPointPos(size_t point) {
	std::string denominator = "1";
	denominator.append(point, '0');
	m_denominator = std::shared_ptr<Real>(new Integer(NDecimal(denominator)));
	m_denominator->SetBase(m_numerator->GetBase());
	return *this;
}
const std::string Fraction::GetString(uint8_t base) const {
	return m_numerator->GetString(base) + "/" + m_denominator->GetString(base);
}
void Fraction::SetBase(uint8_t base) {
	m_numerator->SetBase(base);
	m_denominator->SetBase(base);
}
uint8_t Fraction::GetBase() const {
	return m_denominator->GetBase();
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
NDecimal Fraction::GetNDecimal() const {
	return m_numerator->GetNDecimal() / 
		m_denominator->GetNDecimal();
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
const std::string Fraction::GetDecimal(uint8_t base, size_t decimalLength, 
	std::function<bool(char)> round) const {
	const std::string baseStr = "[base=" + std::to_string(base) + "]";
	NDecimal integer(0, m_denominator->GetBase()), integerRemainder(0, m_denominator->GetBase());
	m_numerator->GetNDecimal().Div(m_denominator->GetNDecimal(), integer, integerRemainder);
	const std::string &integerStr = integer.GetString(base);
	if (!integerRemainder) {
		return m_numerator->IsPositive() == m_denominator->IsPositive() ?
			integerStr + baseStr : "-" + integerStr + baseStr;
	}
	std::string integerRemainderStr = integerRemainder.GetString(base);
	integerRemainderStr.append(decimalLength + 1, '0');
	NDecimal decimal(0, m_denominator->GetBase()), decimalRemainder(0, m_denominator->GetBase());
	NDecimal(integerRemainderStr, base).Div(m_denominator->GetNDecimal(), decimal.SetCheckLoop(), decimalRemainder);
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
				return m_numerator->IsPositive() == m_denominator->IsPositive() ?
					integerStr + "." + fill + decimalStr + loop + baseStr : "-" +
					integerStr + "." + fill + decimalStr + loop + baseStr;
			}
			else {
				return m_numerator->IsPositive() == m_denominator->IsPositive() ?
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
		return m_numerator->IsPositive() == m_denominator->IsPositive() ?
			integerStr + "." + fill + decimalStr + loop + baseStr : "-" +
			integerStr + "." + fill + decimalStr + loop + baseStr;
	}
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
	return Fraction(std::dynamic_pointer_cast<Real>(
		*(*m_numerator * *addition.m_denominator) +
		*(*addition.m_numerator * *m_denominator)),
		std::dynamic_pointer_cast<Real>(*m_denominator * *addition.m_denominator));
}
Fraction Fraction::operator-(const Fraction &subtrahend) const {
	return *this + (-subtrahend);
}
Fraction Fraction::operator*(const Fraction &multiplier) const {
	return Fraction(std::dynamic_pointer_cast<Real>(*m_numerator * *multiplier.m_numerator),
		std::dynamic_pointer_cast<Real>(*m_denominator * *multiplier.m_denominator));
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
Complex Fraction::Power(const Fraction &exponent) const {
	if (strstr(typeid(*exponent.m_denominator).name(), "Integer") && strstr(typeid(*exponent.m_numerator).name(), "Integer")) {
		return *std::dynamic_pointer_cast<Complex>(std::dynamic_pointer_cast<Fraction>(m_numerator->Power(*exponent.m_numerator))->Root(*exponent.m_denominator)) /
			*std::dynamic_pointer_cast<Complex>(std::dynamic_pointer_cast<Fraction>(m_denominator->Power(*exponent.m_numerator))->Root(*exponent.m_denominator));
	}
	else {
		throw "undefine";
	}
}
Complex Fraction::Root(const Fraction &exponent) const {
	return Power(Fraction(exponent.m_denominator, exponent.m_numerator));
}
Complex Fraction::Power(const Integer &exponent) const {
	if (strstr(typeid(*m_denominator).name(), "Integer")) {
		if (strstr(typeid(*m_numerator).name(), "Integer")) {
			return Complex(std::dynamic_pointer_cast<Integer>(m_numerator)->Power(exponent), 0) /
				std::dynamic_pointer_cast<Integer>(m_denominator)->Power(exponent);
		}
		else if (strstr(typeid(*m_numerator).name(), "Fraction")) {
			return std::dynamic_pointer_cast<Fraction>(m_numerator)->Power(exponent) /
				std::dynamic_pointer_cast<Integer>(m_denominator)->Power(exponent);
		}
		else {
			throw "undefine";
		}
	}
	else if (strstr(typeid(*m_denominator).name(), "Fraction")) {
		if (strstr(typeid(*m_numerator).name(), "Integer")) {
			return std::dynamic_pointer_cast<Integer>(m_numerator)->Power(exponent) /
				std::dynamic_pointer_cast<Fraction>(m_denominator)->Power(exponent);
		}
		else if (strstr(typeid(*m_numerator).name(), "Fraction")) {
			return std::dynamic_pointer_cast<Fraction>(m_numerator)->Power(exponent) /
				std::dynamic_pointer_cast<Fraction>(m_denominator)->Power(exponent);
		}
		else {
			throw "undefine";
		}
	}
	else {
		throw "undefine";
	}
}
Complex Fraction::Root(const Integer &exponent) const {
	if (strstr(typeid(*m_denominator).name(), "Integer")) {
		if (strstr(typeid(*m_numerator).name(), "Integer")) {
			return std::dynamic_pointer_cast<Integer>(m_numerator)->Root(exponent) /
				std::dynamic_pointer_cast<Integer>(m_denominator)->Root(exponent);
		}
		else if (strstr(typeid(*m_numerator).name(), "Fraction")) {
			return std::dynamic_pointer_cast<Fraction>(m_numerator)->Root(exponent) /
				std::dynamic_pointer_cast<Integer>(m_denominator)->Root(exponent);
		}
		else {
			throw "undefine";
		}
	}
	else if (strstr(typeid(*m_denominator).name(), "Fraction")) {
		if (strstr(typeid(*m_numerator).name(), "Integer")) {
			return std::dynamic_pointer_cast<Integer>(m_numerator)->Root(exponent) /
				std::dynamic_pointer_cast<Fraction>(m_denominator)->Root(exponent);
		}
		else if (strstr(typeid(*m_numerator).name(), "Fraction")) {
			return std::dynamic_pointer_cast<Fraction>(m_numerator)->Root(exponent) /
				std::dynamic_pointer_cast<Fraction>(m_denominator)->Root(exponent);
		}
		else {
			throw "undefine";
		}
	}
	else {
		throw "undefine";
	}
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
