#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <cstdint>
#include "Number.h"
#include "Integer.h"

class Fraction : public Number {
public:
	Fraction(int64_t value = 0);
	Fraction(const Integer &integer);
	Fraction(const Integer &numerator, const Integer &denominator);
	const std::string GetString(uint8_t base = 10) const override;

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

	friend bool operator==(int number, const Fraction &rational);
	friend Fraction operator-(int number, const Fraction &rational);

	friend Fraction operator+(const Integer &number, const Fraction &addition);
	friend Fraction operator-(const Integer &number, const Fraction &subtrahend);
	friend Fraction operator*(const Integer &number, const Fraction &multiplier);
	friend Fraction operator/(const Integer &number, const Fraction &divisor);

	friend Fraction operator+(const Fraction &number, const Integer &addition);
	friend Fraction operator-(const Fraction &number, const Integer &subtrahend);
	friend Fraction operator*(const Fraction &number, const Integer &multiplier);
	friend Fraction operator/(const Fraction &number, const Integer &divisor);

	Integer m_numerator = 0;
	Integer m_denominator = UINT64_MAX;
};


#endif