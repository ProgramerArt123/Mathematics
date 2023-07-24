#include <cassert>
#include "Integer.h"
#include "Complex.h"
#include "Imaginary.h"

Imaginary::Imaginary(const Integer &value) :
	m_value(new Fraction(value)) {
	
}

Imaginary::Imaginary(const Fraction &value) :
	m_value(new Fraction(value)) {

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
	return Imaginary(*m_value + *addition.m_value);
}
Imaginary Imaginary::operator-(const Imaginary &subtrahend) const {
	return Imaginary(*m_value - *subtrahend.m_value);
}
Fraction Imaginary::operator*(const Imaginary &multiplier) const {
	return *m_value * *multiplier.m_value;
}
Fraction Imaginary::operator/(const Imaginary &divisor) const {
	return Fraction(*m_value, *divisor.m_value);
}
Complex Imaginary::Power(const Integer &exponent) {
	const Fraction &fraction = m_value->Power(exponent);
	const Natural &mod = exponent.GetNatural() % Natural(4);
	if (Natural(0) == mod) {
		return Complex(fraction, 0);
	}
	else if (Natural(1) == mod) {
		return Complex(0, fraction);
	}
	else if (Natural(2) == mod) {
		return Complex(-fraction, 0);
	}
	else if (Natural(3) == mod) {
		return Complex(0, -fraction);
	}
	else {
		assert(0);
		return Complex(0, 0);
	}
}
Complex operator+(const Integer &number, const Imaginary &addition) {
	return Complex(number, addition);
}
Complex operator-(const Integer &number, const Imaginary &subtrahend) {
	return Complex(number, -subtrahend);
}
Imaginary operator*(const Integer &number, const Imaginary &multiplier) {
	Imaginary product(multiplier);
	*product.m_value = *product.m_value * number;
	return product;
}
Imaginary operator/(const Integer &number, const Imaginary &divisor) {
	Imaginary quotient(divisor);
	*quotient.m_value = *quotient.m_value / number;
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
	*quotient.m_value = *number.m_value / *quotient.m_value;
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
	*product.m_value = *product.m_value * number;
	return product;
}
Imaginary operator/(const Fraction &number, const Imaginary &divisor) {
	Imaginary quotient(divisor);
	*quotient.m_value = *quotient.m_value / number;
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
	*quotient.m_value = *number.m_value / *quotient.m_value;
	return quotient;
}
