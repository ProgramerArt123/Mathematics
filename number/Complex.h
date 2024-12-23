#ifndef __NUMBER_COMPLEX_H__
#define __NUMBER_COMPLEX_H__

#include "Number.h"
#include "Fraction.h"
#include "Imaginary.h"

namespace number {

	class Integer;
	class Real;

	class Complex : public Number {
	public:
		Complex();
		Complex(const Integer &real, const Integer &image);
		Complex(const Fraction &real, const Fraction &image);
		Complex(const Imaginary &real, const Imaginary &image);
		Complex(const Complex &real, const Complex &image);
		Complex(const Fraction &real, const Integer &image);
		Complex(const Integer &real, const Fraction &image);
		Complex(const Integer &real, const Imaginary &image);
		Complex(const Fraction &real, const Imaginary &image);

		const Fraction &Real() const;
		const Imaginary &Image() const;

		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		void SetUnSigned(bool isUnSigned)override;
		bool IsPositive() const override;
		void Opposite() override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		bool IsElement() const;
		bool IsReal() const;
		bool IsRealInteger() const;

		Complex operator-() const;

		bool operator==(const Complex &other) const;

		Complex operator+(const Complex &addition) const;
		Complex operator-(const Complex &subtrahend) const;
		Complex operator*(const Complex &multiplier) const;
		Complex operator/(const Complex &divisor) const;

		Complex &operator+=(const Complex &addition);
		Complex &operator-=(const Complex &subtrahend);
		Complex &operator*=(const Complex &multiplier);
		Complex &operator/=(const Complex &divisor);

		Complex Power(const Integer &exponent);

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

		static Complex Power(const Imaginary &number, const Integer &exponent);

		friend Complex operator+(const Integer &number, const Imaginary &addition);
		friend Complex operator-(const Integer &number, const Imaginary &subtrahend);

		friend Complex operator+(const Imaginary &number, const Integer &addition);
		friend Complex operator-(const Imaginary &number, const Integer &subtrahend);

		friend Complex operator+(const Fraction &number, const Imaginary &addition);
		friend Complex operator-(const Fraction &number, const Imaginary &subtrahend);

		friend Complex operator+(const Imaginary &number, const Fraction &addition);
		friend Complex operator-(const Imaginary &number, const Fraction &subtrahend);

	private:
		Fraction m_real;
		Imaginary m_image;
	};
}

#endif