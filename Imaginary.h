#ifndef __IMAGINARY_H__
#define __IMAGINARY_H__

#include "Number.h"

class Integer;
class Real;

class Imaginary : public Number {
public:
	Imaginary(const Integer &value);
	const std::string GetString(uint8_t base = 10) const override;
	std::shared_ptr<Real> m_value;
};

#endif