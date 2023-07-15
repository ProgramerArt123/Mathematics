#ifndef __N_DECIMAL_H__
#define __N_DECIMAL_H__

#include <cstdint>
#include <list>
#include <ostream>

class NDecimal{
public:
	NDecimal(uint64_t value, uint8_t base);
	NDecimal(const std::string &value, uint8_t base = 10);

	operator bool() const;
	bool operator==(const NDecimal &other) const;
	bool operator>(const NDecimal &other) const;
	bool operator<(const NDecimal &other) const;
	bool operator>=(const NDecimal &other) const;
	bool operator<=(const NDecimal &other) const;

	NDecimal operator+(const NDecimal &addition) const;
	NDecimal &operator+=(const NDecimal &addition);
	NDecimal operator-(const NDecimal &subtrahend) const;
	NDecimal &operator-=(const NDecimal &subtrahend);
	NDecimal operator*(const NDecimal &multiplier) const;
	NDecimal operator/(const NDecimal &divisor) const;
	NDecimal &operator/=(const NDecimal &divisor);
	NDecimal operator%(const NDecimal &divisor) const;
	NDecimal Power(const NDecimal &exponent) const;
	NDecimal Root(const NDecimal &exponent) const;

	NDecimal &operator++();

	void Div(const NDecimal &divisor, NDecimal &quotient, NDecimal &remainder) const;

	const std::string GetString(uint8_t base = 10) const;
	const std::string GetStringBase(uint8_t base = 10) const;

	uint8_t GetBase() const;

	NDecimal GetNDecimal(uint8_t base) const;

	NDecimal &SetCheckLoop();
	std::string GetLoop() const;
private:
	NDecimal(uint8_t base);
	NDecimal(const std::list<char> &singles, uint8_t base = 10);
	uint8_t GetBuilt()const;
	NDecimal &Format();
	static uint16_t ToBuilt(char a, char b, uint8_t base);
	static void DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder);
	static char GetChar(uint8_t value);
	static uint8_t GetValue(char c);
	NDecimal Root(const NDecimal &exponent, std::vector<char> &singles, size_t index, char top, char bottom) const;

	std::list<char> m_singles;

	uint8_t m_base = 10;

	bool m_is_check_loop = false;
	size_t m_loop_begin = -1;
	size_t m_loop_end = -1;
};

#endif