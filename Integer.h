#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <cstdint>
#include <vector>
#include "Real.h"
#include "Natural.h"
#include "Fraction.h"
#include "Complex.h"
class Integer : public Real {
public:
	Integer(uint64_t value = 0, bool positive = true);
	Integer(const Natural &value, bool positive = true);
	const std::string GetString(uint8_t radix = 10) const override;
	void SetRadix(uint8_t radix = 10) override;
	uint8_t GetRadix() const override;
	bool EqualZero() const override;
	void SetPositive(bool isPositive)override;
	bool IsPositive() const override;
	Natural GetNatural() const ;
	const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const override;
	std::shared_ptr<Real> operator+(const Real &addition) const override;
	std::shared_ptr<Real> operator-(const Real &subtrahend) const override;
	std::shared_ptr<Real> operator*(const Real &multiplier) const override;
	std::shared_ptr<Real> operator/(const Real &divisor) const override;
	std::shared_ptr<Number> Power(const Real &exponent) const override;
	std::shared_ptr<Number> Root(const Real &exponent) const override;
	bool operator==(const Real &other) const override;
	bool operator<(const Real &other) const override;
	operator bool() const;
	Integer operator-() const;
	Integer operator!() const;
	Integer operator+(const Integer &addition) const;
	Integer operator-(const Integer &subtrahend) const;
	Integer operator*(const Integer &multiplier) const;
	Integer operator/(const Integer &divisor) const;
	Integer operator%(const Integer &divisor) const;
	Fraction operator+(const Fraction &addition) const;
	Fraction operator-(const Fraction &subtrahend) const;
	Fraction operator*(const Fraction &multiplier) const;
	Fraction operator/(const Fraction &divisor) const;
	Fraction Power(const Integer &exponent) const;
	Complex Root(const Integer &exponent) const;
	Complex Power(const Fraction &exponent) const;
	Complex Root(const Fraction &exponent) const;
	Integer &operator+=(const Integer &addition);
	Integer &operator*=(const Integer &multiplier);
	Integer &operator/=(const Integer &divisor);
	bool operator==(const Integer &other)const;
	
	Natural m_value;
	bool m_positive = true;
private:
	Integer PositiveAdd(const Integer &addition) const;
	Integer PositiveSub(const Integer &subtrahend) const;
};

#endif