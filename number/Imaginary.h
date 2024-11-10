#ifndef __NUMBER_IMAGINARY_H__
#define __NUMBER_IMAGINARY_H__

#include "Number.h"
#include "Fraction.h"
namespace number {
	class Integer;
	class Real;

	class Imaginary : public Number {
	public:
		Imaginary(const Integer &value);
		Imaginary(const Fraction &value);
		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		void SetUnSigned(bool isUnSigned) override;
		bool IsPositive() const override;
		void Opposite() override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		const Fraction &Value() const;

		Imaginary operator-() const;

		bool operator==(const Imaginary &other) const;

		Imaginary operator+(const Imaginary &addition) const;
		Imaginary operator-(const Imaginary &subtrahend) const;
		Fraction operator*(const Imaginary &multiplier) const;
		Fraction operator/(const Imaginary &divisor) const;


		friend Imaginary operator*(const Integer &number, const Imaginary &multiplier);
		friend Imaginary operator/(const Integer &number, const Imaginary &divisor);

		friend Imaginary operator*(const Imaginary &number, const Integer &multiplier);
		friend Imaginary operator/(const Imaginary &number, const Integer &divisor);

		friend Imaginary operator*(const Fraction &number, const Imaginary &multiplier);
		friend Imaginary operator/(const Fraction &number, const Imaginary &divisor);

		friend Imaginary operator*(const Imaginary &number, const Fraction &multiplier);
		friend Imaginary operator/(const Imaginary &number, const Fraction &divisor);

	private:
		Fraction m_value;
	};
}
#endif