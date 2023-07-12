#ifndef __IMAGINARY_H__
#define __IMAGINARY_H__

#include "Number.h"

class Integer;

class Imaginary : public Number {
public:
	Imaginary(const Integer &value);
	const std::string GetString(uint8_t base = 10) const override;
	std::shared_ptr<Number> m_value;
};

#endif