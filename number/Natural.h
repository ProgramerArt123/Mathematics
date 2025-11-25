#ifndef __NUMBER_NATURAL_H__
#define __NUMBER_NATURAL_H__

#include <cstdint>
#include <list>
#include <ostream>

#include "Real.h"

#define LITERAL_DEFAULT_RADIX 10
#define CALC_DEFAULT_RADIX 10

namespace performance {
	namespace natural {
		class Algorithm;
		namespace root {
			class Guess;
		}
		namespace logarithm {
			class Guess;
		}
	}
}


namespace number {
	class Natural : public Real {
	public:
		Natural(uint64_t value = 0);
		Natural(const std::string &value, uint8_t radix = LITERAL_DEFAULT_RADIX);

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		void SetPositive(bool isPositive) override;
		bool IsPositive() const override;
		void Opposite() override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		bool IsOdd() const;

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
		const std::list<Natural> &GetFactors();

		Natural &operator++();
		Natural &operator--();

		Natural GreatestCommonDivisor(const Natural &other) const;
		Natural Composition(const Natural &m) const;

		std::pair<Natural, Natural> Div(const Natural &divisor) const;

		size_t CalcOrders() const;
		Natural CalcOrders(size_t length) const;
		Natural CalcPower(size_t exponent) const;
		Natural CalcApproximation(size_t length) const;
		std::pair<Natural, size_t> CalcBase() const;

		static uint8_t GetValue(char c);

		friend class performance::natural::Algorithm;
		friend class performance::natural::root::Guess;
		friend class performance::natural::logarithm::Guess;
	private:
		Natural(const std::list<char> &singles, uint8_t radix = LITERAL_DEFAULT_RADIX);
		uint8_t GetBuilt()const;
		Natural &Format();
		static uint16_t ToBuilt(char a, char b, uint8_t radix);
		static void DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder);
		static char GetChar(uint8_t value);
		static std::list<char> GetRadixSingles(uint8_t from, uint8_t to, const std::list<char> &singles);

		std::list<char> m_singles;

		std::list<Natural> m_factors;
		
	};
}
#endif