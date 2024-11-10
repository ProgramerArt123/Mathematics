#ifndef __NUMBER_NUMBER_H__
#define __NUMBER_NUMBER_H__

#include <string>
#include <functional>
#include <cstdint>

#include "Output.h"

namespace number {
	class Number : public Output {
	public:
		const std::string OutPutString() const override {
			return GetString();
		}
		virtual const std::string GetString(uint8_t radix = 10) const = 0;
		virtual const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const = 0;
		const std::string GetStringRadix(uint8_t radix = 10) const {
			return GetString(radix) + "[radix=" + std::to_string(radix) + "]";
		}
		const std::string GetDecimalRadix(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const {
			return GetDecimal(radix, decimalLength, round) + "[radix=" + std::to_string(radix) + "]";
		}
		virtual bool EqualZero() const = 0;
		virtual bool EqualPositiveOne() const = 0;
		virtual bool EqualNegativeOne() const = 0;
		virtual void SetUnSigned(bool isUnSigned) = 0;
		virtual bool IsPositive() const = 0;
		virtual void Opposite() = 0;
	};
}

#endif