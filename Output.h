#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <functional>

class Output {
public:
	virtual const std::string GetString(uint8_t radix = 10) const = 0;
	virtual const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const = 0;
	const std::string GetStringRadix(uint8_t radix = 10) const;
	const std::string GetDecimalRadix(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const;
};

#endif