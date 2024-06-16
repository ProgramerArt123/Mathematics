#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <cstdint>
#include <vector>
#include "Real.h"
#include "Natural.h"
namespace number {
	class Integer : public Real {
	public:
		Integer(uint64_t value = 0, bool positive = true);
		Integer(const Natural &value, bool positive = true);
		Integer(const std::string &value, bool positive = true);
		const std::string GetString(uint8_t radix = 10) const override;
		void SetRadix(uint8_t radix = 10) override;
		uint8_t GetRadix() const override;
		bool EqualZero() const override;
		void SetPositive(bool isPositive)override;
		bool IsPositive() const override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		Natural Value() const;
		Integer GetAbs() const;

		operator bool() const;
		Integer operator-() const;
		Integer operator+(const Integer &addition) const;
		Integer operator-(const Integer &subtrahend) const;
		Integer operator*(const Integer &multiplier) const;
		Integer operator/(const Integer &divisor) const;
		Integer operator%(const Integer &divisor) const;
		Integer &operator+=(const Integer &addition);
		Integer &operator-=(const Integer &subtrahend);
		Integer &operator*=(const Integer &multiplier);
		Integer &operator/=(const Integer &divisor);
		bool operator==(const Integer &other)const;

	private:
		Integer PositiveAdd(const Integer &addition) const;
		Integer PositiveSub(const Integer &subtrahend) const;

		bool m_positive = true;

		Natural m_value;
	};
}
#endif