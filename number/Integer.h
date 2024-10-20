#ifndef __NUMBER_INTEGER_H__
#define __NUMBER_INTEGER_H__

#include <cstdint>
#include <vector>
#include "Real.h"
#include "Natural.h"
namespace number {
	class Integer : public Real {
	public:
		Integer(uint64_t value = 0, bool isUnSigned = true);
		Integer(const Natural &value, bool isUnSigned = true);
		Integer(const std::string &value, bool isUnSigned = true);
		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualOne() const override;
		void SetUnSigned(bool isUnSigned)override;
		bool IsPositive() const override;
		void Opposite() override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		const Natural &Value() const;
		Integer GetAbs() const;

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
		bool operator!=(const Integer &other) const;
		bool operator>(const Integer &other) const;
		bool operator<(const Integer &other) const;
		bool operator>=(const Integer &other) const;
		bool operator<=(const Integer &other) const;
	private:
		Integer PositiveAdd(const Integer &addition) const;
		Integer PositiveSub(const Integer &subtrahend) const;

		bool m_unsigned = true;

		Natural m_value;
	};
}
#endif