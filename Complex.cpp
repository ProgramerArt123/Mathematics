#include "Integer.h"
#include "Fraction.h"
#include "Imaginary.h"
#include "Complex.h"

Complex::Complex(const Integer &real, const Integer &image) :
	m_real(new Integer(real)),m_image(new Imaginary(image)) {

}

Complex::Complex(const Fraction &real, const Fraction &image) :
	m_real(new Fraction(real)), m_image(new Imaginary(image)) {

}
Complex::Complex(const Fraction &real, const Integer &image) :
	m_real(new Fraction(real)), m_image(new Imaginary(image)) {

}
Complex::Complex(const Integer &real, const Fraction &image) :
	m_real(new Integer(real)), m_image(new Imaginary(image)) {

}
Complex::Complex(const Integer &real, const Imaginary &image):
	m_real(new Integer(real)), m_image(new Imaginary(image)) {

}
Complex::Complex(const Fraction &real, const Imaginary &image) :
	m_real(new Fraction(real)), m_image(new Imaginary(image)) {

}
Complex::Complex(const std::shared_ptr<Real> &real, const Imaginary &image) :
	m_real(real), m_image(new Imaginary(image)) {

}

Complex::Complex(const std::shared_ptr<Real> &real, const std::shared_ptr<Real> &image) :
	m_real(real), m_image(new Imaginary(image)) {

}
const std::string Complex::GetString(uint8_t base) const {
	const std::string &realStr = m_real->GetString(base);
	const std::string &imageStr = m_image->GetString(base);
	if ("0" == realStr && "0i"==imageStr) {
		return "0";
	}
	else if ("0" == realStr) {
		return imageStr;
	}
	else if ("0i" == imageStr) {
		return realStr;
	}
	else {
		if ('-' != imageStr.front()) {
			return realStr + "+" + imageStr;
		}
		else {
			return realStr + imageStr;
		}
	}
}

void Complex::SetBase(uint8_t base) {
	m_real->SetBase(base);
	m_image->SetBase(base);
}
uint8_t Complex::GetBase() const {
	return m_real->GetBase();
}
bool Complex::EqualZero() const {
	return m_real->EqualZero() && m_image->EqualZero();
}
void Complex::SetPositive(bool isPositive) {
	m_real->SetPositive(isPositive);
	m_image->SetPositive(isPositive);
}
bool Complex::IsPositive() const {
	return m_real->IsPositive() && m_image->IsPositive();
}
NDecimal Complex::GetNDecimal() const {
	throw "undefine";
}

Complex Complex::operator-() const {
	Complex negative(*this);
	negative.SetPositive(!negative.IsPositive());
	return negative;
}
Complex Complex::operator+(const Complex &addition) const {
	const std::shared_ptr<Number> real = *m_real + *addition.m_real;
	const Imaginary &image = *m_image + *addition.m_image;
	return Complex(std::dynamic_pointer_cast<Real>(real), image);
}
Complex Complex::operator-(const Complex &subtrahend) const {
	return *this + -subtrahend;
}
Complex Complex::operator*(const Complex &multiplier) const {
	const std::shared_ptr<Number> real = *(*m_real * *multiplier.m_real) -
		*(*m_image->m_value * *multiplier.m_image->m_value);
	const std::shared_ptr<Number> image = *(*m_real * *multiplier.m_image->m_value) +
		*(*m_image->m_value * *multiplier.m_real);
	return Complex(std::dynamic_pointer_cast<Real>(real), 
		std::dynamic_pointer_cast<Real>(image));
}
Complex Complex::operator/(const Complex &divisor) const {
	const std::shared_ptr<Number> real = *(*(*m_real * *divisor.m_real) +
		*(*m_image->m_value * *divisor.m_image->m_value)) /
		*(*(*divisor.m_real * *divisor.m_real) + *(*divisor.m_image->m_value * *divisor.m_image->m_value));
	const std::shared_ptr<Number> image = *(*(*m_image->m_value * *divisor.m_real) +
		*(*m_real * *divisor.m_image->m_value)) /
		*(*(*divisor.m_real * *divisor.m_real) + *(*divisor.m_image->m_value * *divisor.m_image->m_value));
	return Complex(std::dynamic_pointer_cast<Real>(real),
		std::dynamic_pointer_cast<Real>(image));
}
Complex &Complex::operator+=(const Complex &addition) {
	return *this = *this + addition;
}
Complex operator+(const Integer &number, const Complex &addition) {
	return Complex(number, 0) + addition;
}
Complex operator-(const Integer &number, const Complex &subtrahend) {
	return Complex(number, 0) - subtrahend;
}
Complex operator*(const Integer &number, const Complex &multiplier) {
	return Complex(number, 0) * multiplier;
}
Complex operator/(const Integer &number, const Complex &divisor) {
	return Complex(number, 0) / divisor;
}

Complex operator+(const Complex &number, const Integer &addition) {
	return number + Complex(addition, 0);
}
Complex operator-(const Complex &number, const Integer &subtrahend) {
	return number - Complex(subtrahend, 0);
}
Complex operator*(const Complex &number, const Integer &multiplier) {
	return number * Complex(multiplier, 0);
}
Complex operator/(const Complex &number, const Integer &divisor) {
	return number / Complex(divisor, 0);
}

Complex operator+(const Fraction &number, const Complex &addition) {
	return Complex(number, 0) + addition;
}
Complex operator-(const Fraction &number, const Complex &subtrahend) {
	return Complex(number, 0) - subtrahend;
}
Complex operator*(const Fraction &number, const Complex &multiplier) {
	return Complex(number, 0) * multiplier;
}
Complex operator/(const Fraction &number, const Complex &divisor) {
	return Complex(number, 0) / divisor;
}
Complex operator+(const Complex &number, const Fraction &addition) {
	return number + Complex(addition, 0);
}
Complex operator-(const Complex &number, const Fraction &subtrahend) {
	return number - Complex(subtrahend, 0);
}
Complex operator*(const Complex &number, const Fraction &multiplier) {
	return number * Complex(multiplier, 0);
}
Complex operator/(const Complex &number, const Fraction &divisor) {
	return number / Complex(divisor, 0);
}
Complex operator+(const Imaginary &number, const Complex &addition) {
	return Complex(Integer(0), number) + addition;
}
Complex operator-(const Imaginary &number, const Complex &subtrahend) {
	return Complex(Integer(0), number) - subtrahend;
}
Complex operator*(const Imaginary &number, const Complex &multiplier) {
	return Complex(Integer(0), number) * multiplier;
}
Complex operator/(const Imaginary &number, const Complex &divisor) {
	return Complex(Integer(0), number) / divisor;
}

Complex operator+(const Complex &number, const Imaginary &addition) {
	return number + Complex(Integer(0), addition);
}
Complex operator-(const Complex &number, const Imaginary &subtrahend) {
	return number - Complex(Integer(0), subtrahend);
}
Complex operator*(const Complex &number, const Imaginary &multiplier) {
	return number * Complex(Integer(0), multiplier);
}
Complex operator/(const Complex &number, const Imaginary &divisor) {
	return number / Complex(Integer(0), divisor);
}
Complex Power(const Complex &number, const Integer &exponent) {
	Complex power(Integer(0), Integer(0));
	for (Integer index(0); index <= exponent; index+=1) {
		power += exponent.Composition(exponent, index) * 
			*std::dynamic_pointer_cast<Complex>(number.m_real->Power(exponent - index)) *
			Power(*number.m_image, exponent);
	}
	return power;
}