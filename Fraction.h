#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <cstdint>
#include <functional>
#include "Real.h"
#include "Complex.h"

class Integer;

class Fraction : public Real {
public:
	Fraction();
	Fraction(const Integer &significant);
	Fraction(const Integer &numerator, const Integer &denominator);
	Fraction(const Integer &numerator, const Fraction &denominator);
	Fraction(const std::shared_ptr<Real> &numerator, const std::shared_ptr<Real> &denominator);
	Fraction &SetPointPos(size_t point);
	const std::string GetString(uint8_t radix = 10) const override;
	void SetRadix(uint8_t radix = 10) override;
	uint8_t GetRadix() const override;
	bool EqualZero() const override;
	void SetPositive(bool isPositive) override;
	bool IsPositive() const override;
	Natural GetNatural() const override;
	std::shared_ptr<Real> operator+(const Real &addition) const override;
	std::shared_ptr<Real> operator-(const Real &subtrahend) const override;
	std::shared_ptr<Real> operator*(const Real &multiplier) const override;
	std::shared_ptr<Real> operator/(const Real &divisor) const override;
	std::shared_ptr<Number> Power(const Real &exponent) const override;
	std::shared_ptr<Number> Root(const Real &exponent) const override;
	bool operator==(const Real &other) const override;
	bool operator<(const Real &other) const override;
	const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const override;
	Fraction operator-() const;
	bool operator<(const Fraction &other) const;
	bool operator==(const Fraction &other) const;

	Fraction operator+(const Fraction &addition) const;
	Fraction operator-(const Fraction &subtrahend) const;
	Fraction operator*(const Fraction &multiplier) const;
	Fraction operator/(const Fraction &divisor) const;
	
	Complex Power(const Fraction &exponent) const;
	Complex Root(const Fraction &exponent) const;

	Fraction &operator+=(const Fraction &addition);
	Fraction &operator*=(const Fraction &multiplier);

	Complex Power(const Integer &exponent)const;
	Complex Root(const Integer &exponent)const;

	friend bool operator==(const Integer &number, const Fraction &rational);

	friend Fraction operator+(const Fraction &number, const Integer &addition);
	friend Fraction operator-(const Fraction &number, const Integer &subtrahend);
	friend Fraction operator*(const Fraction &number, const Integer &multiplier);
	friend Fraction operator/(const Fraction &number, const Integer &divisor);

	std::shared_ptr<Real> m_numerator;
	std::shared_ptr<Real> m_denominator;
};


#endif