#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include "Number.h"

class Fraction;
class Imaginary;
class Integer;
class Real;

class Complex : public Number {
public:
	Complex(const Integer &real, const Integer &image);
	Complex(const Fraction &real, const Fraction &image);
	Complex(const Fraction &real, const Integer &image);
	Complex(const Integer &real, const Fraction &image);
	Complex(const Integer &real, const Imaginary &image);
	Complex(const Fraction &real, const Imaginary &image);
	Complex(const Complex &real, const Complex &image);
	const std::string GetString(uint8_t radix = 10) const override;
	void SetRadix(uint8_t radix = 10) override;
	uint8_t GetRadix() const override;
	bool EqualZero() const override;
	void SetPositive(bool isPositive)override;
	bool IsPositive() const override;
	const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const override;

	Complex operator-() const;

	Complex operator+(const Complex &addition) const;
	Complex operator-(const Complex &subtrahend) const;
	Complex operator*(const Complex &multiplier) const;
	Complex operator/(const Complex &divisor) const;

	Complex &operator+=(const Complex &addition);

	friend Complex operator+(const Integer &number, const Complex &addition);
	friend Complex operator-(const Integer &number, const Complex &subtrahend);
	friend Complex operator*(const Integer &number, const Complex &multiplier);
	friend Complex operator/(const Integer &number, const Complex &divisor);

	friend Complex operator+(const Complex &number, const Integer &addition);
	friend Complex operator-(const Complex &number, const Integer &subtrahend);
	friend Complex operator*(const Complex &number, const Integer &multiplier);
	friend Complex operator/(const Complex &number, const Integer &divisor);

	friend Complex operator+(const Fraction &number, const Complex &addition);
	friend Complex operator-(const Fraction &number, const Complex &subtrahend);
	friend Complex operator*(const Fraction &number, const Complex &multiplier);
	friend Complex operator/(const Fraction &number, const Complex &divisor);

	friend Complex operator+(const Complex &number, const Fraction &addition);
	friend Complex operator-(const Complex &number, const Fraction &subtrahend);
	friend Complex operator*(const Complex &number, const Fraction &multiplier);
	friend Complex operator/(const Complex &number, const Fraction &divisor);

	friend Complex operator+(const Imaginary &number, const Complex &addition);
	friend Complex operator-(const Imaginary &number, const Complex &subtrahend);
	friend Complex operator*(const Imaginary &number, const Complex &multiplier);
	friend Complex operator/(const Imaginary &number, const Complex &divisor);

	friend Complex operator+(const Complex &number, const Imaginary &addition);
	friend Complex operator-(const Complex &number, const Imaginary &subtrahend);
	friend Complex operator*(const Complex &number, const Imaginary &multiplier);
	friend Complex operator/(const Complex &number, const Imaginary &divisor);

	//friend Complex Power(const Complex &number, const Integer &exponent);

	std::shared_ptr<Fraction> m_real;
	std::shared_ptr<Imaginary> m_image;
};

#endif