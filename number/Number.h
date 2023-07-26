#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <string>
#include <functional>

#include "Output.h"
namespace number {
	class Number : public Output {
	public:
		const std::string OutPutString() const override;

		virtual const std::string GetString(uint8_t radix = 10) const = 0;
		virtual const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const = 0;
		const std::string GetStringRadix(uint8_t radix = 10) const;
		const std::string GetDecimalRadix(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const;

		virtual void SetRadix(uint8_t radix = 10) = 0;
		virtual uint8_t GetRadix() const = 0;
		virtual bool EqualZero() const = 0;
		virtual void SetPositive(bool isPositive) = 0;
		virtual bool IsPositive() const = 0;

	};
}

#endif