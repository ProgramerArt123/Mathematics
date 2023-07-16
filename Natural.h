#ifndef __NATURAL_H__
#define __NATURAL_H__

#include <cstdint>
#include <list>
#include <ostream>

#include "Number.h"

class Natural : public Number{
public:
	Natural(uint64_t value, uint8_t radix);
	Natural(const std::string &value, uint8_t radix = 10);

	const std::string GetString(uint8_t radix = 10) const override;
	void SetRadix(uint8_t radix = 10) override;
	uint8_t GetRadix() const override;
	bool EqualZero() const override;
	void SetPositive(bool isPositive) override;
	bool IsPositive() const override;
	Natural GetNatural() const override;
	const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const override;

	operator bool() const;
	bool operator==(const Natural &other) const;
	bool operator>(const Natural &other) const;
	bool operator<(const Natural &other) const;
	bool operator>=(const Natural &other) const;
	bool operator<=(const Natural &other) const;

	Natural operator+(const Natural &addition) const;
	Natural &operator+=(const Natural &addition);
	Natural operator-(const Natural &subtrahend) const;
	Natural &operator-=(const Natural &subtrahend);
	Natural operator*(const Natural &multiplier) const;
	Natural operator/(const Natural &divisor) const;
	Natural &operator/=(const Natural &divisor);
	Natural operator%(const Natural &divisor) const;
	Natural Power(const Natural &exponent) const;
	Natural Root(const Natural &exponent) const;

	Natural &operator++();

	void Div(const Natural &divisor, Natural &quotient, Natural &remainder) const;
	Natural GetNatural(uint8_t radix) const;
	
	Natural &SetCheckLoop();
	std::string GetLoop() const;
private:
	Natural(uint8_t radix);
	Natural(const std::list<char> &singles, uint8_t radix = 10);
	uint8_t GetBuilt()const;
	Natural &Format();
	static uint16_t ToBuilt(char a, char b, uint8_t radix);
	static void DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder);
	static char GetChar(uint8_t value);
	static uint8_t GetValue(char c);
	Natural Root(const Natural &exponent, std::vector<char> &singles, size_t index, char top, char bottom) const;

	std::list<char> m_singles;

	uint8_t m_radix = 10;

	bool m_is_check_loop = false;
	size_t m_loop_begin = -1;
	size_t m_loop_end = -1;
};

#endif