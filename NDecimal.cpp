#include <cassert>
#include <list>
#include <map>
#include "NDecimal.h"

static char GetChar(uint8_t value) {
	if (value <= 9) {
		return '0' + value;
	}
	else if (10 <= value && value <= 10 + ('Z' - 'A')) {
		return 'A' + (value - 10);
	}
	else {
		assert(0);
		return '0';
	}
}

static uint8_t GetValue(char c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	else if ('A' <= c && c <= 'Z') {
		return 10 + c - 'A';
	}
	else {
		assert(0);
		return 0;
	}
}

NDecimal::NDecimal(uint64_t value, uint8_t base) {
	if (value) {
		while (value) {
			m_singles.push_back(GetChar(value % base));
			value /= base;
		}
	}
	else {
		m_singles.push_back('0');
	}
}
NDecimal::NDecimal(const std::string &value, uint8_t base):
	NDecimal(std::list<char>(value.crbegin(), value.crend()), base){

}
NDecimal::NDecimal() {

}
NDecimal::NDecimal(const std::list<char> &bits, uint8_t base):
	m_base(base) {
	m_singles = bits;
	if (m_singles.empty()) {
		m_singles.push_back('0');
	}
}
NDecimal::operator bool() const {
	return !(1 == m_singles.size() && '0' == m_singles.front());
}
bool NDecimal::operator==(const NDecimal &other) const {
	return m_singles == other.m_singles;
}
bool NDecimal::operator>(const NDecimal &other) const {
	const NDecimal &baseOther = other.GetNDecimal(m_base);
	if (m_singles.size() < baseOther.m_singles.size()) {
		return false;
	}
	else if (m_singles.size() > baseOther.m_singles.size()) {
		return true;
	}
	else {
		for (auto bit = m_singles.crbegin(), oBit = baseOther.m_singles.crbegin();
			bit != m_singles.crend() && oBit != baseOther.m_singles.crend();
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
bool NDecimal::operator<(const NDecimal &other) const {
	return other > *this;
}
bool NDecimal::operator>=(const NDecimal &other) const {
	return *this > other || *this == other;
}
bool NDecimal::operator<=(const NDecimal &other) const {
	return *this < other || *this == other;
}
NDecimal NDecimal::operator+(const NDecimal &addition) const {
	const NDecimal &baseAddition = addition.GetNDecimal(m_base);
	NDecimal result;
	result.m_base = m_base;
	bool isCarray = false;
	for (auto bit = m_singles.cbegin(), aBit = baseAddition.m_singles.cbegin();
		bit != m_singles.cend() || aBit != baseAddition.m_singles.cend();) {
		uint8_t bitValue = 0;
		if (bit != m_singles.cend()) {
			bitValue = GetValue(*bit);
		}
		uint8_t aBitValue = 0;
		if (aBit != baseAddition.m_singles.cend()) {
			aBitValue = GetValue(*aBit);
		}
		if (bitValue + aBitValue + isCarray >= m_base) {
			result.m_singles.push_back(
				GetChar((bitValue + aBitValue + isCarray)%m_base));
			isCarray = true;
		}
		else {
			result.m_singles.push_back(
				GetChar(bitValue + aBitValue + isCarray));
			isCarray = false;
		}
		if (bit != m_singles.cend())
			bit++;
		if (aBit != baseAddition.m_singles.cend())
			aBit++;
	}
	if (isCarray) {
		result.m_singles.push_back('1');
	}
	return result.Format();
}
NDecimal &NDecimal::operator+=(const NDecimal &addition) {
	*this = *this + addition;
	return *this;
}
NDecimal NDecimal::operator-(const NDecimal &subtrahend) const {
	assert(*this >= subtrahend);
	const NDecimal &baseSubtrahend = subtrahend.GetNDecimal(m_base);
	NDecimal result;
	result.m_base = m_base;
	bool isCarray = false;
	for (auto bit = m_singles.cbegin(), sBit = baseSubtrahend.m_singles.cbegin();
		bit != m_singles.cend(); bit++) {
		uint8_t bitValue = GetValue(*bit);
		uint8_t sBitValue = 0;
		if (sBit != baseSubtrahend.m_singles.cend()) {
			sBitValue = GetValue(*sBit);
		}
		if (bitValue - sBitValue - isCarray < 0) {
			result.m_singles.push_back(
				GetChar(m_base + bitValue - sBitValue - isCarray));
			isCarray = true;
		}
		else {
			result.m_singles.push_back(
				GetChar(bitValue - sBitValue - isCarray));
			isCarray = false;
		}
		if(sBit != baseSubtrahend.m_singles.cend())
			sBit++;
	}
	assert(!isCarray);
	return result.Format();
}
NDecimal &NDecimal::operator-=(const NDecimal &subtrahend) {
	*this = *this - subtrahend;
	return *this;
}
NDecimal NDecimal::operator*(const NDecimal &multiplier) const {
	const NDecimal &baseMultiplier = multiplier.GetNDecimal(m_base);
	NDecimal result;
	result.m_base = m_base;
	size_t count = 0;
	for (auto mBit = baseMultiplier.m_singles.cbegin();
		mBit != baseMultiplier.m_singles.cend(); mBit++, count ++) {
		if ('0' != *mBit) {
			NDecimal item(0);
			for (uint8_t index = 0; index < GetValue(*mBit); index ++) {
				item += *this;
			}
			item.m_singles.insert(item.m_singles.cbegin(), count, '0');
			result += item;
		}
	}
	return result.Format();
}
NDecimal NDecimal::operator/(const NDecimal &divisor) const {
	NDecimal quotient, remainder;
	Div(divisor, quotient, remainder);
	return quotient;
}
NDecimal &NDecimal::operator/=(const NDecimal &divisor) {
	*this = *this / divisor;
	return *this;
}
NDecimal NDecimal::operator%(const NDecimal &divisor) const {
	NDecimal quotient, remainder;
	Div(divisor, quotient, remainder);
	return remainder;
}
NDecimal &NDecimal::operator++() {
	*this = *this + NDecimal(1);
	return *this;
}
void NDecimal::Div(const NDecimal &divisor, NDecimal &quotient, NDecimal &remainder) const {
	if (divisor == NDecimal(0)) {
		throw "undefined";
	}

	const NDecimal &baseDivisor = divisor.GetNDecimal(m_base);

	if (*this < baseDivisor) {
		remainder = *this;
		quotient = NDecimal(0, m_base);
		return;
	}

	quotient.m_singles.clear();
	quotient.m_base = m_base;
	remainder.m_singles.clear();
	remainder.m_base = m_base;

	size_t times = m_singles.size() - baseDivisor.m_singles.size() + 1;

	auto begin = m_singles.cbegin();
	{
		size_t count = m_singles.size() - baseDivisor.m_singles.size();
		for (size_t index = 0; index < count; index++) {
			begin++;
		}
	}
	
	remainder.m_singles = std::list<char>(begin, m_singles.cend());
	
	for (size_t index = 0; index < times; index++) {
		uint8_t count = 0;
		while (remainder >= baseDivisor) {
			count++;
			remainder -= baseDivisor;
		}
		quotient.m_singles.push_front(GetChar(count));
		if (index < times - 1) {
			begin--;
			remainder.m_singles.push_front(*begin);
			remainder.Format();
		}
	}
	quotient.Format();
}
const std::string NDecimal::GetString(uint8_t base) const {
	assert(2 <= base && base <= (11 + ('Z' - 'A')));
	const NDecimal &bitBase = NDecimal(base);
	const NDecimal &bitZero = NDecimal(0);
	std::list<char> result;
	NDecimal remaining(*this);
	do {
		NDecimal quotient, remainde;
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
uint8_t NDecimal::GetBase() const {
	return m_base;
}
uint8_t NDecimal::GetBuilt()const {
	assert(1 == m_singles.size());
	return GetValue(m_singles.front());
}
NDecimal &NDecimal::Format() {
	while (!m_singles.empty() && '0' == m_singles.back()) {
		m_singles.pop_back();
	}
	if (m_singles.empty()) {
		m_singles.push_back('0');
	}
	return *this;
}

uint16_t NDecimal::ToBuilt(char a, char b, uint8_t base) {
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

//char NDecimal::ToChar(uint16_t value, uint8_t base) {
//	if (0 <= value && value <= 9) {
//		return '0' + value;
//	}
//	else {
//		return 'A' + value - 10;
//	}
//}

void NDecimal::DivN(uint8_t from, uint8_t to, std::list<char> &bits, char &remainder) {
	std::list<char> quotient;
	char pre = '0';
	for (auto bit = bits.crbegin(); bit != bits.crend(); bit++) {
		uint16_t built = ToBuilt(pre, *bit, from);
		uint8_t q = built / to;
		uint8_t r = built % to;
		quotient.push_front(GetChar(q));
		pre = '0' + r;
	}
	remainder = pre;
	while (quotient.size() > 1 && '0' == quotient.back()) {
		quotient.pop_back();
	}
	bits = quotient;

}

NDecimal NDecimal::GetNDecimal(uint8_t base) const {
	if (m_base == base) {
		return *this;
	}
	NDecimal baseDecimal;
	baseDecimal.m_base = base;
	std::list<char> quotient = m_singles;
	char remainder = '0';
	do {
		DivN(m_base, base, quotient, remainder);
		baseDecimal.m_singles.push_back(remainder);
	} while (quotient.size() > 1 || '0' != quotient.front());
	if (baseDecimal.m_singles.empty()) {
		baseDecimal.m_singles.push_back('0');
	}
	return baseDecimal;
}
