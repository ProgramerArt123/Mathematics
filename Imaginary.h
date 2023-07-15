#ifndef __IMAGINARY_H__
#define __IMAGINARY_H__

#include "Number.h"
#include "Complex.h"
#include "Fraction.h"

class Integer;
class Fraction;
class Real;

class Imaginary : public Number {
public:
	Imaginary(const Integer &value);
	Imaginary(const Fraction &value);
	Imaginary(const std::shared_ptr<Real> &value);
	const std::string GetString(uint8_t base = 10) const override;
	virtual void SetBase(uint8_t base = 10) override;
	virtual uint8_t GetBase() const override;
	virtual bool EqualZero() const override;
	virtual void SetPositive(bool isPositive) override;
	virtual bool IsPositive() const override;
	virtual NDecimal GetNDecimal() const override;
	

	Imaginary operator-() const;

	Imaginary operator+(const Imaginary &addition) const;
	Imaginary operator-(const Imaginary &subtrahend) const;
	Fraction operator*(const Imaginary &multiplier) const;
	Fraction operator/(const Imaginary &divisor) const;


	friend Complex operator+(const Integer &number, const Imaginary &addition);
	friend Complex operator-(const Integer &number, const Imaginary &subtrahend);
	friend Imaginary operator*(const Integer &number, const Imaginary &multiplier);
	friend Imaginary operator/(const Integer &number, const Imaginary &divisor);

	friend Complex operator+(const Imaginary &number, const Integer &addition);
	friend Complex operator-(const Imaginary &number, const Integer &subtrahend);
	friend Imaginary operator*(const Imaginary &number, const Integer &multiplier);
	friend Imaginary operator/(const Imaginary &number, const Integer &divisor);

	friend Complex operator+(const Fraction &number, const Imaginary &addition);
	friend Complex operator-(const Fraction &number, const Imaginary &subtrahend);
	friend Imaginary operator*(const Fraction &number, const Imaginary &multiplier);
	friend Imaginary operator/(const Fraction &number, const Imaginary &divisor);
	
	friend Complex operator+(const Imaginary &number, const Fraction &addition);
	friend Complex operator-(const Imaginary &number, const Fraction &subtrahend);
	friend Imaginary operator*(const Imaginary &number, const Fraction &multiplier);
	friend Imaginary operator/(const Imaginary &number, const Fraction &divisor);

	friend Complex Power(const Imaginary &number, const Integer &exponent);
	friend Complex Root(const Imaginary &number, const Integer &exponent);

	friend Complex Power(const Imaginary &number, const Fraction &exponent);
	friend Complex Root(const Imaginary &number, const Fraction &exponent);

	std::shared_ptr<Real> m_value;
};

#endif