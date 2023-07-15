#include <cassert>
#include <list>
#include <map>
#include <vector>
#include <string>
#include "NDecimal.h"

NDecimal::NDecimal(uint64_t value, uint8_t base):m_base(base) {
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
NDecimal::NDecimal(uint8_t base):m_base(base) {

}
NDecimal::NDecimal(const std::list<char> &singles, uint8_t base):
	m_base(base) {
	m_singles = singles;
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
	NDecimal result(m_base);
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
	NDecimal result(m_base);
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
	NDecimal result(m_base);
	size_t count = 0;
	for (auto mBit = baseMultiplier.m_singles.cbegin();
		mBit != baseMultiplier.m_singles.cend(); mBit++, count ++) {
		if ('0' != *mBit) {
			NDecimal item(0, GetBase());
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
	NDecimal quotient(m_base), remainder(m_base);
	Div(divisor, quotient, remainder);
	return quotient;
}
NDecimal &NDecimal::operator/=(const NDecimal &divisor) {
	*this = *this / divisor;
	return *this;
}
NDecimal NDecimal::operator%(const NDecimal &divisor) const {
	NDecimal quotient(m_base), remainder(m_base);
	Div(divisor, quotient, remainder);
	return remainder;
}
NDecimal NDecimal::Power(const NDecimal &exponent) const {
	const NDecimal &baseExponent = exponent.GetNDecimal(m_base);
	NDecimal result(1, m_base);
	for (NDecimal count(0, m_base); count < baseExponent; ++count) {
		result = *this * result;
	}
	return result;
}

NDecimal NDecimal::Root(const NDecimal &exponent, std::vector<char> &singles, size_t index, char top, char bottom) const {
	char c = GetChar((GetValue(top) + GetValue(bottom) + 1)/2);
	singles[index] = c;
	NDecimal value(std::list<char>(singles.cbegin(), singles.cend()), m_base);
	const NDecimal &power = value.Power(exponent);
	if (power == *this) {
		return value;
	}
	else if (power > *this) {
		if (c > bottom + 1) {
			return Root(exponent, singles, index, c, bottom);
		}
		else {
			singles[index] = bottom;
			if (index) {
				return Root(exponent, singles, index - 1, GetChar(m_base - 1), '0');
			}
			else {
				return NDecimal(std::list<char>(singles.cbegin(), singles.cend()));
			}
		}
	}
	else {
		if (c + 1 < top) {
			return Root(exponent, singles, index, top, c);
		}
		else {
			if (index) {
				return Root(exponent, singles, index - 1, GetChar(m_base - 1), '0');
			}
			else {
				return value;
			}
		}
	}
}

NDecimal NDecimal::Root(const NDecimal &exponent) const {
	size_t len = strtoull(((NDecimal(m_singles.size(), m_base) +
		exponent - NDecimal(1, m_base)) / exponent).GetString(m_base).c_str(), NULL, m_base);
	std::vector<char> singles(len, '0');
	return Root(exponent, singles, len - 1, GetChar(m_base - 1), '0');
}
NDecimal &NDecimal::operator++() {
	*this = *this + NDecimal(1, GetBase());
	return *this;
}
void NDecimal::Div(const NDecimal &divisor, NDecimal &quotient, NDecimal &remainder) const {
	if (divisor == NDecimal(0, GetBase())) {
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
	
	std::map<std::string, size_t> loop;
	remainder.m_singles = std::list<char>(begin, m_singles.cend());

	for (size_t index = 0; index < times; index++) {
		uint8_t count = 0;
		while (remainder >= baseDivisor) {
			count++;
			remainder -= baseDivisor;
		}
		quotient.m_singles.push_front(GetChar(count));
		if (index < times - 1) {
			if (quotient.m_is_check_loop && -1 == quotient.m_loop_begin && remainder) {
				const std::string key(remainder.m_singles.cbegin(), remainder.m_singles.cend());
				if (loop.find(key) != loop.end()) {
					quotient.m_loop_begin = loop.at(key);
					quotient.m_loop_end = quotient.m_singles.size();
				}
				else {
					loop.insert(std::make_pair(std::string(
						remainder.m_singles.cbegin(), remainder.m_singles.cend()), quotient.m_singles.size()));
				}
			}
			begin--;
			remainder.m_singles.push_front(*begin);
			remainder.Format();
		}
	}
	if (!quotient.m_is_check_loop) {
		quotient.Format();
	}
}
const std::string NDecimal::GetString(uint8_t base) const {
	assert(2 <= base && base <= (11 + ('Z' - 'A')));
	const NDecimal bitBase(base, GetBase());
	const NDecimal bitZero(0, GetBase());
	std::list<char> result;
	NDecimal remaining(*this);
	do {
		NDecimal quotient(m_base), remainde(m_base);
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
const std::string NDecimal::GetStringBase(uint8_t base) const {
	return GetString(base) + "[base=" + std::to_string(base) + "]";
}
uint8_t NDecimal::GetBase() const {
	return m_base;
}
uint8_t NDecimal::GetBuilt()const {
	uint8_t built = 0;
	uint8_t weight = 1;
	for (auto single = m_singles.cbegin(); single != m_singles.cend(); single++, weight*=GetBase()) {
		built += GetValue(*single) * weight;
	}
	return built;
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

void NDecimal::DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder) {
	std::list<char> quotient;
	char pre = '0';
	for (auto bit = singles.crbegin(); bit != singles.crend(); bit++) {
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
	singles = quotient;

}

NDecimal NDecimal::GetNDecimal(uint8_t base) const {
	if (m_base == base) {
		return *this;
	}
	NDecimal baseDecimal(base);
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


NDecimal &NDecimal::SetCheckLoop() {
	m_is_check_loop = true;
	return *this;
}

std::string NDecimal::GetLoop() const {
	if (!m_is_check_loop || -1 == m_loop_begin) {
		return "";
	}
	const std::string singles(m_singles.crbegin(), m_singles.crend());
	return "......{" + singles.substr(m_loop_begin + 1, m_loop_end - m_loop_begin) + "}";
}

char NDecimal::GetChar(uint8_t value) {
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

uint8_t NDecimal::GetValue(char c) {
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