#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <string>
#include <functional>

class Natural;

class Number {
public:
	virtual const std::string GetString(uint8_t radix = 10) const = 0;
	virtual void SetRadix(uint8_t radix = 10) = 0;
	virtual uint8_t GetRadix() const = 0;
	virtual bool EqualZero() const = 0;
	virtual void SetPositive(bool isPositive) = 0;
	virtual bool IsPositive() const = 0;
	virtual Natural GetNatural() const = 0;
	virtual const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const = 0;

	const std::string GetStringRadix(uint8_t radix = 10) const;

	friend std::ostream& operator<<(std::ostream& out, const Number &number);

};


#endif