#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <cstdint>
#include <vector>
#include "Number.h"
#include "NDecimal.h"
#include "Fraction.h"
class Integer : public Number {
public:
	Integer(uint64_t value = 0, bool positive = true);
	Integer(const NDecimal &value, bool positive = true);
	const std::string GetString(uint8_t base = 10) const override;
	Integer GreatestCommonDivisor(const Integer &other) const;
	operator bool() const;
	Integer operator-() const;
	Integer operator!() const;
	Integer operator+(const Integer &addition) const;
	Integer operator-(const Integer &subtrahend) const;
	Integer operator*(const Integer &multiplier) const;
	Integer operator/(const Integer &divisor) const;
	Integer operator%(const Integer &divisor) const;
	Fraction Power(const Integer &exponent) const;
	Integer Root(const Integer &exponent) const;
	Integer &operator+=(const Integer &addition);
	Integer &operator*=(const Integer &multiplier);
	Integer &operator/=(const Integer &divisor);
	bool operator==(const Integer &other)const;
	NDecimal m_value;
	bool m_positive = true;
private:
	Integer PositiveAdd(const Integer &addition) const;
	Integer PositiveSub(const Integer &subtrahend) const;
};

#endif