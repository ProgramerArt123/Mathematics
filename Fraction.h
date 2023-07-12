#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <cstdint>
#include <functional>
#include "Real.h"

class Integer;

class Fraction : public Real {
public:
	Fraction();
	Fraction(const Integer &significant);
	Fraction(const Integer &numerator, const Integer &denominator);
	Fraction &SetPointPos(size_t point);
	const std::string GetString(uint8_t base = 10) const override;
	const std::string GetDecimal(uint8_t base, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const;
	bool IsPositive() const;
	Fraction operator-() const;
	bool operator<(const Fraction &other) const;
	bool operator==(const Fraction &other) const;

	Fraction operator+(const Fraction &addition) const;
	Fraction operator-(const Fraction &subtrahend) const;
	Fraction operator*(const Fraction &multiplier) const;
	Fraction operator/(const Fraction &divisor) const;

	Fraction &operator+=(const Fraction &addition);
	Fraction &operator*=(const Fraction &multiplier);

	friend bool operator==(const Integer &number, const Fraction &rational);

	friend Fraction operator+(const Integer &number, const Fraction &addition);
	friend Fraction operator-(const Integer &number, const Fraction &subtrahend);
	friend Fraction operator*(const Integer &number, const Fraction &multiplier);
	friend Fraction operator/(const Integer &number, const Fraction &divisor);

	friend Fraction operator+(const Fraction &number, const Integer &addition);
	friend Fraction operator-(const Fraction &number, const Integer &subtrahend);
	friend Fraction operator*(const Fraction &number, const Integer &multiplier);
	friend Fraction operator/(const Fraction &number, const Integer &divisor);

	std::shared_ptr<Integer> m_numerator;
	std::shared_ptr <Integer> m_denominator;
};


#endif