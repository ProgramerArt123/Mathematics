#ifndef __NUMBER_FRACTION_H__
#define __NUMBER_FRACTION_H__

#include <cstdint>
#include <functional>
#include "Real.h"
#include "Integer.h"
namespace number {
	class Fraction : public Real {
	public:
		Fraction();
		Fraction(const Integer &significant);
		Fraction(const Integer &numerator, const Integer &denominator);
		Fraction(const Integer &numerator, const Fraction &denominator);
		Fraction(const Fraction &numerator, const Integer &denominator);
		Fraction(const Fraction &numerator, const Fraction &denominator);

		Fraction Point(size_t point) const;
		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		void SetUnSigned(bool isUnSigned) override;
		bool IsPositive() const override;
		void Opposite() override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		const Integer &Numerator() const;
		const Integer &ReductionNumerator() const;
		const Integer &Denominator() const;
		const Integer &ReductionDenominator() const;
		const Integer &ReductionInteger() const;

		Fraction GetAbs() const;
		Fraction GetReciprocal() const;
		bool IsInteger() const;

		Fraction operator-() const;
		bool operator<(const Fraction &other) const;
		bool operator>(const Fraction &other) const;
		bool operator==(const Fraction &other) const;
		bool operator!=(const Fraction &other) const;
		bool operator<=(const Fraction &other) const;
		bool operator>=(const Fraction &other) const;

		Fraction operator+(const Fraction &addition) const;
		Fraction operator-(const Fraction &subtrahend) const;
		Fraction operator*(const Fraction &multiplier) const;
		Fraction operator/(const Fraction &divisor) const;

		Fraction Power(const number::Integer &exponent) const;

		Fraction &operator+=(const Fraction &addition);
		Fraction &operator-=(const Fraction &subtrahend);
		Fraction &operator*=(const Fraction &multiplier);
		Fraction &operator/=(const Fraction &divisor);

		Fraction CalcApproximation(size_t length) const;

		friend bool operator==(const number::Integer &number, const Fraction &rational);
		friend bool operator!=(const number::Integer &number, const Fraction &rational);

		friend Fraction operator+(const Fraction &number, const number::Integer &addition);
		friend Fraction operator-(const Fraction &number, const number::Integer &subtrahend);
		friend Fraction operator*(const Fraction &number, const number::Integer &multiplier);
		friend Fraction operator/(const Fraction &number, const number::Integer &divisor);

		friend Fraction operator+(const number::Integer &number, const Fraction &addition);
		friend Fraction operator-(const number::Integer &number, const Fraction &subtrahend);
		friend Fraction operator*(const number::Integer &number, const Fraction &multiplier);
		friend Fraction operator/(const number::Integer &number, const Fraction &divisor);

		static Fraction Power(const number::Integer &number, const number::Integer &exponent);
		static bool CheckReduce(const Integer &numerator, const Integer &denominator);
	private:

		number::Integer m_numerator = 0;
		number::Integer m_denominator = 1;

		number::Integer m_reduction_numerator = 0;
		number::Integer m_reduction_denominator = 1;
		number::Integer m_reduction_integer = 0;

		void Reduce();

	};
}

#endif