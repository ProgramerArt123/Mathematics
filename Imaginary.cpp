#include "Integer.h"
#include "Complex.h"
#include "Imaginary.h"

Imaginary::Imaginary(const Integer &value) :
	m_value(new Integer(value)) {
	
}

Imaginary::Imaginary(const Fraction &value) :
	m_value(new Fraction(value)) {

}

Imaginary::Imaginary(const std::shared_ptr<Real> &value):
	m_value(value) {

}

const std::string Imaginary::GetString(uint8_t radix) const {
	return m_value->GetString(radix) + "i";
}

void Imaginary::SetRadix(uint8_t radix) {
	m_value->SetRadix(radix);
}
uint8_t Imaginary::GetRadix() const {
	return m_value->GetRadix();
}
bool Imaginary::EqualZero() const {
	return m_value->EqualZero();
}
void Imaginary::SetPositive(bool isPositive) {
	m_value->SetPositive(isPositive);
}
bool Imaginary::IsPositive() const {
	return m_value->IsPositive();
}
Natural Imaginary::GetNatural() const {
	return m_value->GetNatural();
}
const std::string Imaginary::GetDecimal(uint8_t radix, size_t decimalLength,
	std::function<bool(char)> round) const {
	return m_value->GetDecimal(radix, decimalLength, round) + "i";
}
Imaginary Imaginary::operator-() const {
	Imaginary negative(*this);
	negative.SetPositive(!negative.IsPositive());
	return negative;
}
Imaginary Imaginary::operator+(const Imaginary &addition) const {
	const std::shared_ptr<Number> &sum = *m_value + *addition.m_value;
	if (strstr(typeid(*sum).name(), "Integer")) {
		return *std::dynamic_pointer_cast<Integer>(sum);
	}
	else if (strstr(typeid(*sum).name(), "Fraction")) {
		return *std::dynamic_pointer_cast<Fraction>(sum);
	}
	else {
		throw "undefine";
	}
}
Imaginary Imaginary::operator-(const Imaginary &subtrahend) const {
	const std::shared_ptr<Number> &diff = *m_value - *subtrahend.m_value;
	if (strstr(typeid(*diff).name(), "Integer")) {
		return *std::dynamic_pointer_cast<Integer>(diff);
	}
	else if (strstr(typeid(*diff).name(), "Fraction")) {
		return *std::dynamic_pointer_cast<Fraction>(diff);
	}
	else {
		throw "undefine";
	}
}
Fraction Imaginary::operator*(const Imaginary &multiplier) const {
	const std::shared_ptr<Number> &product = *m_value * *multiplier.m_value;
	if (strstr(typeid(*product).name(), "Integer")) {
		return -*std::dynamic_pointer_cast<Integer>(product);
	}
	else if (strstr(typeid(*product).name(), "Fraction")) {
		return -*std::dynamic_pointer_cast<Fraction>(product);
	}
	else {
		throw "undefine";
	}
	return *std::dynamic_pointer_cast<Fraction>(product);
}
Fraction Imaginary::operator/(const Imaginary &divisor) const {
	return Fraction(m_value, divisor.m_value);
}

Complex operator+(const Integer &number, const Imaginary &addition) {
	return Complex(number, addition);
}
Complex operator-(const Integer &number, const Imaginary &subtrahend) {
	return Complex(number, -subtrahend);
}
Imaginary operator*(const Integer &number, const Imaginary &multiplier) {
	Imaginary product(multiplier);
	product.m_value = std::dynamic_pointer_cast<Real>(*product.m_value * number);
	return product;
}
Imaginary operator/(const Integer &number, const Imaginary &divisor) {
	Imaginary quotient(divisor);
	quotient.m_value = std::dynamic_pointer_cast<Real>(*quotient.m_value / number);
	return quotient;
}

Complex operator+(const Imaginary &number, const Integer &addition) {
	return addition + number;
}
Complex operator-(const Imaginary &number, const Integer &subtrahend) {
	return Complex(-subtrahend, number);
}
Imaginary operator*(const Imaginary &number, const Integer &multiplier) {
	return multiplier * number;
}
Imaginary operator/(const Imaginary &number, const Integer &divisor) {
	Imaginary quotient(divisor);
	quotient.m_value = std::dynamic_pointer_cast<Real>(*number.m_value / *quotient.m_value);
	return quotient;
}

Complex operator+(const Fraction &number, const Imaginary &addition) {
	return Complex(number, addition);
}
Complex operator-(const Fraction &number, const Imaginary &subtrahend) {
	return Complex(number, -subtrahend);
}
Imaginary operator*(const Fraction &number, const Imaginary &multiplier) {
	Imaginary product(multiplier);
	product.m_value = std::dynamic_pointer_cast<Real>(*product.m_value * number);
	return product;
}
Imaginary operator/(const Fraction &number, const Imaginary &divisor) {
	Imaginary quotient(divisor);
	quotient.m_value = std::dynamic_pointer_cast<Real>(*quotient.m_value / number);
	return quotient;
}

Complex operator+(const Imaginary &number, const Fraction &addition) {
	return addition + number;
}
Complex operator-(const Imaginary &number, const Fraction &subtrahend) {
	return Complex(-subtrahend, number);
}
Imaginary operator*(const Imaginary &number, const Fraction &multiplier) {
	return multiplier * number;
}
Imaginary operator/(const Imaginary &number, const Fraction &divisor) {
	Imaginary quotient(divisor);
	quotient.m_value = std::dynamic_pointer_cast<Real>(*number.m_value / *quotient.m_value);
	return quotient;
}
Complex Power(const Imaginary &number, const Integer &exponent) {
	return Power(number, Fraction(exponent, 1));
}
Complex Root(const Imaginary &number, const Integer &exponent) {
	return Root(number, Fraction(exponent, 1));
}
Complex Power(const Imaginary &number, const Fraction &exponent) {
	if (strstr(typeid(*exponent.m_denominator).name(), "Integer") && strstr(typeid(*exponent.m_numerator).name(), "Integer")) {
		if (strstr(typeid(*number.m_value).name(), "Integer")) {
			return std::dynamic_pointer_cast<Integer>(number.m_value)->Power(exponent);
		}
		else if (strstr(typeid(*number.m_value).name(), "Fraction")) {
			return std::dynamic_pointer_cast<Fraction>(number.m_value)->Power(exponent);
		}
		else {
			throw "undefine";
		}
	}
	else {
		throw "undefine";
	}
}
Complex Root(const Imaginary &number, const Fraction &exponent) {
	return Power(number, Fraction(exponent.m_denominator, exponent.m_numerator));
}