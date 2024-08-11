#include <cassert>
#include "Integer.h"
#include "Fraction.h"
#include "Imaginary.h"
#include "Complex.h"
namespace number {
	Complex::Complex() :
		m_real(0), m_image(0) {

	}
	Complex::Complex(const Integer &real, const Integer &image) :
		m_real(real), m_image(image) {

	}
	Complex::Complex(const Imaginary &real, const Imaginary &image) :
		m_real(0), m_image(0) {
		m_image = real + image;
	}
	Complex::Complex(const Fraction &real, const Fraction &image) :
		m_real(real), m_image(image) {

	}
	Complex::Complex(const Fraction &real, const Integer &image) :
		m_real(real), m_image(image) {

	}
	Complex::Complex(const Integer &real, const Fraction &image) :
		m_real(real), m_image(image) {

	}
	Complex::Complex(const Integer &real, const Imaginary &image) :
		m_real(real), m_image(image) {

	}
	Complex::Complex(const Fraction &real, const Imaginary &image) :
		m_real(real), m_image(image) {

	}
	const Fraction &Complex::Real() const {
		return m_real;
	}
	const Imaginary &Complex::Image() const {
		return m_image;
	}
	Complex::Complex(const Complex &real, const Complex &image) :
		m_real(0), m_image(0) {
		*this = real + image * Imaginary(1);
	}
	const std::string Complex::GetString(uint8_t radix) const {
		if (m_real.EqualZero() && m_image.EqualZero()) {
			return "0";
		}
		else if (m_real.EqualZero()) {
			return m_image.GetString(radix);
		}
		else if (m_image.EqualZero()) {
			return m_real.GetString(radix);
		}
		else if (m_image.IsPositive()) {
			return m_real.GetString(radix) + "+" + m_image.GetString(radix);
		}
		else {
			return m_real.GetString(radix) + m_image.GetString(radix);
		}
	}

	void Complex::SetRadix(uint8_t radix) {
		m_real.SetRadix(radix);
		m_image.SetRadix(radix);
	}
	uint8_t Complex::GetRadix() const {
		return m_real.GetRadix();
	}
	bool Complex::EqualZero() const {
		return m_real.EqualZero() && m_image.EqualZero();
	}
	bool Complex::EqualOne() const {
		return m_real.EqualOne() && m_image.EqualZero();
	}
	void Complex::SetPositive(bool isPositive) {
		m_real.SetPositive(isPositive);
		m_image.SetPositive(isPositive);
	}
	bool Complex::IsPositive() const {
		return m_real.IsPositive() && m_image.IsPositive();
	}
	const std::string Complex::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		if (m_real.EqualZero() && m_image.EqualZero()) {
			return "0";
		}
		else if (m_real.EqualZero()) {
			return m_image.GetDecimal(radix, decimalLength, round);
		}
		else if (m_image.EqualZero()) {
			return m_real.GetDecimal(radix, decimalLength, round);
		}
		else if (m_image.IsPositive()) {
			return m_real.GetDecimal(radix, decimalLength, round) +
				"+" + m_image.GetDecimal(radix, decimalLength, round);
		}
		else {
			return m_real.GetDecimal(radix, decimalLength, round) +
				m_image.GetDecimal(radix, decimalLength, round);
		}
	}
	bool Complex::IsElement() const {
		return Real().EqualZero() ||
			Image().EqualZero();
	}
	bool Complex::IsReal() const {
		return Image().EqualZero();
	}
	bool Complex::IsRealInteger() const {
		return IsReal() && Real().IsInteger();
	}
	Complex Complex::operator-() const {
		Complex negative(*this);
		negative.SetPositive(!negative.IsPositive());
		return negative;
	}
	bool Complex::operator==(const Complex &other) const {
		return Real() == other.Real() && Image() == other.Image();
	}
	Complex Complex::operator+(const Complex &addition) const {
		const Fraction &real = m_real + addition.m_real;
		const Imaginary &image = m_image + addition.m_image;
		return Complex(real, image);
	}
	Complex Complex::operator-(const Complex &subtrahend) const {
		return *this + -subtrahend;
	}
	Complex Complex::operator*(const Complex &multiplier) const {
		const Fraction &real = (m_real * multiplier.m_real) -
			(m_image.Value() * multiplier.m_image.Value());
		const Fraction &image = (m_real * multiplier.m_image.Value()) +
			(m_image.Value() * multiplier.m_real);
		return Complex(real, image);
	}
	Complex Complex::operator/(const Complex &divisor) const {
		const Fraction real((m_real * divisor.m_real) +
			(m_image.Value() * divisor.m_image.Value()),
			(divisor.m_real * divisor.m_real) +
			(divisor.m_image.Value() * divisor.m_image.Value()));
		const Fraction image((m_image.Value() * divisor.m_real) -
			(m_real * divisor.m_image.Value()),
			(divisor.m_real * divisor.m_real) +
			(divisor.m_image.Value() * divisor.m_image.Value()));
		return Complex(real, image);
	}
	Complex &Complex::operator+=(const Complex &addition) {
		return *this = *this + addition;
	}
	Complex &Complex::operator-=(const Complex &subtrahend) {
		return *this = *this - subtrahend;
	}
	Complex &Complex::operator*=(const Complex &multiplier) {
		return *this = *this * multiplier;
	}
	Complex &Complex::operator/=(const Complex &divisor) {
		return *this = *this / divisor;
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

	Complex Complex::Power(const Integer &exponent) {
		Complex power(0, 0);
		for (Natural index(0); index <= exponent.Value(); ++index) {
			power += Integer(exponent.Value().Composition(index)) *
				m_real.Power(exponent - index) * Complex::Power(m_image, index);
		}
		return power;
	}

	Complex Complex::Power(const Imaginary &number, const Integer &exponent) {
		const Fraction &fraction = number.Value().Power(exponent);
		const Natural &mod = exponent.Value() % Natural(4);
		if (mod.EqualZero()) {
			return Complex(fraction, 0);
		}
		else if (mod.EqualOne()) {
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

	Complex operator+(const Imaginary &number, const Integer &addition) {
		return addition + number;
	}
	Complex operator-(const Imaginary &number, const Integer &subtrahend) {
		return Complex(-subtrahend, number);
	}

	Complex operator+(const Fraction &number, const Imaginary &addition) {
		return Complex(number, addition);
	}
	Complex operator-(const Fraction &number, const Imaginary &subtrahend) {
		return Complex(number, -subtrahend);
	}

	Complex operator+(const Imaginary &number, const Fraction &addition) {
		return addition + number;
	}
	Complex operator-(const Imaginary &number, const Fraction &subtrahend) {
		return Complex(-subtrahend, number);
	}
}