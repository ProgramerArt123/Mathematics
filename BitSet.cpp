#include <cassert>
#include <list>
#include "BitSet.h"

BitSet::BitSet(uint64_t value) {
	if (value) {
		while (value) {
			m_bits.push_back('0' + (value & 0x01));
			value >>= 1;
		}
	}
	else {
		m_bits.push_back('0');
	}
}
BitSet::BitSet(const std::string &value, uint8_t base):
	BitSet(std::list<char>(value.crbegin(), value.crend()), base){

}
BitSet::BitSet() {

}
BitSet::BitSet(const std::list<char> &bits, uint8_t base):
	m_base(base) {
	std::list<char> quotient = bits;
	char remainder = '0';
	do{
		Div2(base, quotient, remainder);
		m_bits.push_back(remainder);
	} while (quotient.size() > 1 || '0' != quotient.front());
	if (m_bits.empty()) {
		m_bits.push_back('0');
	}
}
BitSet::operator bool() const {
	return !(1 == m_bits.size() && '0' == m_bits.front());
}
bool BitSet::operator==(const BitSet &other) const {
	return m_bits == other.m_bits;
}
bool BitSet::operator>(const BitSet &other) const {
	if (m_bits.size() < other.m_bits.size()) {
		return false;
	}
	else if (m_bits.size() > other.m_bits.size()) {
		return true;
	}
	else {
		for (auto bit = m_bits.crbegin(), oBit = other.m_bits.crbegin();
			bit != m_bits.crend() && oBit != other.m_bits.crend();
			bit ++, oBit++) {
			if (*bit == *oBit) {
				continue;
			}
			else {
				return *bit > *oBit;
			}
		}
		return false;
	}
}
bool BitSet::operator<(const BitSet &other) const {
	return other > *this;
}
bool BitSet::operator>=(const BitSet &other) const {
	return *this > other || *this == other;
}
bool BitSet::operator<=(const BitSet &other) const {
	return *this < other || *this == other;
}
BitSet BitSet::operator+(const BitSet &addition) const {
	BitSet result;
	bool isCarray = false;
	for (auto bit = m_bits.cbegin(), aBit = addition.m_bits.cbegin();
		bit != m_bits.cend() || aBit != addition.m_bits.cend();) {
		unsigned char bitValue = 0;
		if (bit != m_bits.cend()) {
			bitValue = *bit - '0';
		}
		unsigned char aBitValue = 0;
		if (aBit != addition.m_bits.cend()) {
			aBitValue = *aBit - '0';
		}
		switch (bitValue + aBitValue + isCarray)
		{
		case 0:
			result.m_bits.push_back('0');
			isCarray = false;
			break;
		case 1:
			result.m_bits.push_back('1');
			isCarray = false;
			break;
		case 2:
			result.m_bits.push_back('0');
			isCarray = true;
			break;
		case 3:
			result.m_bits.push_back('1');
			isCarray = true;
			break;
		default:
			break;
		}
		if (bit != m_bits.cend())
			bit++;
		if (aBit != addition.m_bits.cend())
			aBit++;
	}
	if (isCarray) {
		result.m_bits.push_back('1');
	}
	return result.Format();
}
BitSet &BitSet::operator+=(const BitSet &addition) {
	*this = *this + addition;
	return *this;
}
BitSet BitSet::operator-(const BitSet &subtrahend) const {
	assert(*this >= subtrahend);
	BitSet result;
	bool isCarray = false;
	for (auto bit = m_bits.cbegin(), sBit = subtrahend.m_bits.cbegin();
		bit != m_bits.cend(); bit++) {
		unsigned char bitValue = *bit - '0';
		unsigned char sBitValue = 0;
		if (sBit != subtrahend.m_bits.cend()) {
			sBitValue = *sBit - '0';
		}
		switch (bitValue - sBitValue - isCarray)
		{
		case -2:
			result.m_bits.push_back('0');
			isCarray = true;
			break;
		case -1:
			result.m_bits.push_back('1');
			isCarray = true;
			break;
		case 0:
			result.m_bits.push_back('0');
			isCarray = false;
			break;
		case 1:
			result.m_bits.push_back('1');
			isCarray = false;
			break;
		default:
			break;
		}
		if(sBit != subtrahend.m_bits.cend())
			sBit++;
	}
	assert(!isCarray);
	return result.Format();
}
BitSet &BitSet::operator-=(const BitSet &subtrahend) {
	*this = *this - subtrahend;
	return *this;
}
BitSet BitSet::operator*(const BitSet &multiplier) const {
	BitSet result;
	size_t count = 0;
	for (auto mBit = multiplier.m_bits.cbegin();
		mBit != multiplier.m_bits.cend(); mBit++, count ++) {
		if ('1' == *mBit) {
			BitSet item(*this);
			item.m_bits.insert(item.m_bits.cbegin(), count, '0');
			result += item;
		}
	}
	return result.Format();
}
BitSet BitSet::operator/(const BitSet &divisor) const {
	BitSet quotient, remainder;
	Div(divisor, quotient, remainder);
	return quotient;
}
BitSet &BitSet::operator/=(const BitSet &divisor) {
	*this = *this / divisor;
	return *this;
}
BitSet BitSet::operator%(const BitSet &divisor) const {
	BitSet quotient, remainder;
	Div(divisor, quotient, remainder);
	return remainder;
}
BitSet &BitSet::operator++() {
	*this = *this + BitSet(1);
	return *this;
}
void BitSet::Div(const BitSet &divisor, BitSet &quotient, BitSet &remainder) const {
	if (divisor == BitSet(0)) {
		throw "undefined";
	}

	if (*this < divisor) {
		remainder = *this;
		quotient = BitSet(0);
		return;
	}

	BitSet result;

	size_t times = m_bits.size() - divisor.m_bits.size() + 1;

	auto begin = m_bits.cbegin();
	{
		size_t count = m_bits.size() - divisor.m_bits.size();
		for (size_t index = 0; index < count; index++) {
			begin++;
		}
	}
	BitSet remaining(std::list<char>(begin, m_bits.cend()));

	for (size_t index = 0; index < times; index++) {
		if (begin != m_bits.cbegin())
			begin--;
		if (remaining >= divisor) {
			result.m_bits.insert(result.m_bits.cbegin(), '1');
			remaining -= divisor;
		}
		else {
			result.m_bits.insert(result.m_bits.cbegin(), '0');
		}
		if (index < times - 1) {
			remaining.m_bits.push_front(*begin);
			remaining.Format();
		}
	}

	remainder = remaining;

	quotient = result.Format();
}
const std::string BitSet::GetString(uint8_t base) const {
	assert(2 <= base && base <= (11 + ('Z' - 'A')));
	const BitSet &bitBase = BitSet(base);
	const BitSet &bitZero = BitSet(0);
	std::list<char> result;
	BitSet remaining(*this);
	do {
		BitSet quotient, remainde;
		remaining.Div(bitBase, quotient, remainde);
		uint8_t built = remainde.GetBuilt();
		if (0 <= built && built <= 9) {
			result.push_front('0' + built);
		}
		else {
			result.push_front('A' + (built - 10));
		}
		remaining = quotient;
	} while (remaining > bitZero);
	return std::string(result.cbegin(), result.cend());
}
uint8_t BitSet::GetBase() const {
	return m_base;
}
uint8_t BitSet::GetBuilt()const {
	uint8_t built = 0;
	size_t count = 0;
	for (auto bit = m_bits.cbegin(); bit != m_bits.cend(); bit++, count++) {
		if ('1' == *bit) {
			built += (1 << count);
		}
	}
	return built;
}
BitSet &BitSet::Format() {
	while (!m_bits.empty() && '0' == m_bits.back()) {
		m_bits.pop_back();
	}
	if (m_bits.empty()) {
		m_bits.push_back('0');
	}
	return *this;
}

uint16_t BitSet::ToBuilt(char a, char b, uint8_t base) {
	if (10 > base) {
		assert(('0' <= a && a <= '9') || ('A' <= a && a <= 'A' + base - 11));
		assert(('0' <= b && b <= '9') || ('A' <= b && b <= 'A' + base - 11));
	}
	else {
		assert('0' <= a && a <= '0' + base - 1);
		assert('0' <= b && b <= '0' + base - 1);
	}
	uint16_t result = 0;
	if ('0' <= a && a <= '9') {
		result += (a - '0') * base;
	}
	else {
		result += (a - 'A' + 10) * base;
	}
	if ('0' <= b && b <= '9') {
		result += (b - '0');
	}
	else {
		result += (b - 'A' + 10);
	}
	return result;
}

char BitSet::ToChar(uint16_t value, uint8_t base) {
	if (0 <= value && value <= 9) {
		return '0' + value;
	}
	else {
		return 'A' + value - 10;
	}
}

void BitSet::Div2(uint8_t base, std::list<char> &bits, char &remainder) {
	std::list<char> quotient;
	char pre = '0';
	for (auto bit = bits.crbegin(); bit != bits.crend(); bit++) {
		uint16_t built = ToBuilt(pre, *bit, base);
		uint16_t q = built / 2;
		uint16_t r = built % 2;
		quotient.insert(quotient.cbegin(), ToChar(q, base));
		pre = '0' + r;
	}
	remainder = pre;
	while (quotient.size() > 1 && '0' == quotient.back()) {
		quotient.pop_back();
	}
	bits = quotient;

}

