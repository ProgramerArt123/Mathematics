#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include "Number.h"
#include "Imaginary.h"

class Complex : public Number {
public:
	Complex(const Integer &real, const Integer &image);
	const std::string GetString(uint8_t base = 10) const override;
	std::shared_ptr<Real> m_real;
	Imaginary m_image;
};

#endif