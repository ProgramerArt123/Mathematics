#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <string>
#include <functional>

#include "Output.h"

class Number : public Output{
public:
	
	virtual void SetRadix(uint8_t radix = 10) = 0;
	virtual uint8_t GetRadix() const = 0;
	virtual bool EqualZero() const = 0;
	virtual void SetPositive(bool isPositive) = 0;
	virtual bool IsPositive() const = 0;
	
	friend std::ostream& operator<<(std::ostream& out, const Number &number);
};


#endif