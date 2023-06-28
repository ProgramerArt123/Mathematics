#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <cstdint>
#include <vector>
#include "Number.h"
#include "BitSet.h"

class Integer : public Number {
public:
	Integer(BitSet value = 0, bool positive = true);
	const std::string GetString(uint8_t base = 10) const override;
	Integer GreatestCommonDivisor(const Integer &other) const;
	operator bool() const;
	Integer operator-() const;
	Integer operator!() const;
	Integer operator+(const Integer &addition) const;
	Integer operator-(const Integer &subtrahend) const;
	Integer operator*(const Integer &multiplier) const;
	Integer operator%(const Integer &divisor) const;
	Integer operator/(const Integer &divisor) const;
	Integer &operator+=(const Integer &addition);
	Integer &operator*=(const Integer &multiplier);
	Integer &operator/=(const Integer &divisor);
	bool operator==(const Integer &other)const;
	BitSet m_value;
	bool m_positive = true;
private:
	Integer PositiveAdd(const Integer &addition) const;
	Integer PositiveSub(const Integer &subtrahend) const;
};

#endif