#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <cstdint>
#include <vector>
#include <ostream>

class BitSet {
public:
	BitSet(uint64_t value);
	BitSet(const std::string &value, uint8_t base = 10);
	operator bool() const;
	bool operator==(const BitSet &other) const;
	bool operator>(const BitSet &other) const;
	bool operator<(const BitSet &other) const;
	bool operator>=(const BitSet &other) const;
	bool operator<=(const BitSet &other) const;

	BitSet operator+(const BitSet &addition) const;
	BitSet &operator+=(const BitSet &addition);
	BitSet operator-(const BitSet &subtrahend) const;
	BitSet &operator-=(const BitSet &subtrahend);
	BitSet operator*(const BitSet &multiplier) const;
	BitSet operator/(const BitSet &divisor) const;
	BitSet &operator/=(const BitSet &divisor);
	BitSet operator%(const BitSet &divisor) const;

	BitSet &operator++();

	const std::string GetString(uint8_t base = 10) const;

	friend std::ostream& operator<<(std::ostream& out, const BitSet &bits);
private:
	BitSet();
	BitSet(const std::vector<char> &bits, uint8_t base = 2);
	uint8_t GetBuilt()const;
	BitSet &Format();
	static uint16_t ToBuilt(char a, char b, uint8_t base);
	static char ToChar(uint16_t value, uint8_t base);
	static void Div2(uint8_t base, std::vector<char> &bits, char &remainder);
	std::vector<char> m_bits;
};

#endif