#ifndef __NUMBER_NATURAL_H__
#define __NUMBER_NATURAL_H__

#include <cstdint>
#include <list>
#include <ostream>

#include "Real.h"

namespace performance {
	namespace natural {
		namespace root {
			class Guess;
		}
	}
}


namespace number {
	class Natural : public Real {
	public:
		Natural(uint64_t value = 0, uint8_t radix = 10);
		Natural(const std::string &value, uint8_t radix = 10);

		const std::string GetString(uint8_t radix = 10) const override;
		void SetRadix(uint8_t radix = 10) override;
		uint8_t GetRadix() const override;
		bool EqualZero() const override;
		bool EqualOne() const override;
		void SetPositive(bool isPositive) override;
		bool IsPositive() const override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		Natural Factorial() const;
		bool operator==(const Natural &other) const;
		bool operator!=(const Natural &other) const;
		bool operator>(const Natural &other) const;
		bool operator<(const Natural &other) const;
		bool operator>=(const Natural &other) const;
		bool operator<=(const Natural &other) const;

		Natural operator+(const Natural &addition) const;
		Natural &operator+=(const Natural &addition);
		Natural operator-(const Natural &subtrahend) const;
		Natural &operator-=(const Natural &subtrahend);
		Natural operator*(const Natural &multiplier) const;
		Natural &operator*=(const Natural &multiplier);
		Natural operator/(const Natural &divisor) const;
		Natural &operator/=(const Natural &divisor);
		Natural operator%(const Natural &divisor) const;
		Natural Power(const Natural &exponent) const;
		std::pair<Natural, Natural> Root(const Natural &exponent) const;
		std::pair<Natural, Natural> Logarithm(const Natural &base) const;

		Natural &operator++();
		Natural &operator--();

		Natural GreatestCommonDivisor(const Natural &other) const;
		Natural Composition(const Natural &m) const;

		std::pair<Natural, Natural> Div(const Natural &divisor) const;
		Natural GetNatural(uint8_t radix) const;

		std::string GetLoop() const;

		friend class performance::natural::root::Guess;
	private:
		Natural(const std::list<char> &singles, uint8_t radix = 10);
		uint8_t GetBuilt()const;
		Natural &Format();
		static uint16_t ToBuilt(char a, char b, uint8_t radix);
		static void DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder);
		static char GetChar(uint8_t value);
		static uint8_t GetValue(char c);
		std::pair<Natural, Natural> PowerInverseHalf(const Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<Natural(const Natural&, const Natural&)> power) const;
		std::pair<Natural, Natural> PowerInverse(const Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<Natural(const Natural&, const Natural&)> power) const;
		
		std::list<char> m_singles;

		uint8_t m_radix = 10;

		size_t m_loop_begin = -1;
		size_t m_loop_end = -1;
		
	};
}
#endif