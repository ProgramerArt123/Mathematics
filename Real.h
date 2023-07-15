#ifndef __REAL_H__
#define __REAL_H__

#include "Number.h"

class Real : public Number {
public:
	virtual std::shared_ptr<Real> operator+(const Real &addition) const = 0;
	virtual std::shared_ptr<Real> operator-(const Real &subtrahend) const = 0;
	virtual std::shared_ptr<Real> operator*(const Real &multiplier) const = 0;
	virtual std::shared_ptr<Real> operator/(const Real &divisor) const = 0;
	virtual std::shared_ptr<Number> Power(const Real &exponent) const = 0;
	virtual std::shared_ptr<Number> Root(const Real &exponent) const = 0;
	virtual bool operator==(const Real &other) const = 0;
	virtual bool operator<(const Real &other) const = 0;
};

#endif