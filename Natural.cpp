#include <cassert>
#include <list>
#include <map>
#include <vector>
#include <string>
#include "Natural.h"

Natural::Natural(uint64_t value, uint8_t radix):m_radix(radix) {
	if (value) {
		while (value) {
			m_singles.push_back(GetChar(value % radix));
			value /= radix;
		}
	}
	else {
		m_singles.push_back('0');
	}
}
Natural::Natural(const std::string &value, uint8_t radix):
	Natural(std::list<char>(value.crbegin(), value.crend()), radix){

}

Natural::Natural(const std::list<char> &singles, uint8_t radix):
	m_radix(radix) {
	m_singles = singles;
	if (m_singles.empty()) {
		m_singles.push_back('0');
	}
}
const std::string Natural::GetString(uint8_t radix) const {
	assert(2 <= radix && radix <= (11 + ('Z' - 'A')));
	const Natural bitRadix(radix, GetRadix());
	const Natural bitZero(0, GetRadix());
	std::list<char> result;
	Natural remaining(*this);
	do {
		Natural quotient(0, m_radix), remainde(0, m_radix);
		remaining.Div(bitRadix, quotient, remainde);
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
void Natural::SetRadix(uint8_t radix) {
	if (m_radix != radix) {
		const std::string &radixStr = GetString(m_radix = radix);
		m_singles.clear();
		m_singles.assign(radixStr.crbegin(), radixStr.crend());
	}
}
uint8_t Natural::GetRadix() const {
	return m_radix;
}
bool Natural::EqualZero() const {
	return m_singles.size() == 1 && '0' == m_singles.front();
}
void Natural::SetPositive(bool isPositive) {
	throw "undefine";
}
bool Natural::IsPositive() const {
	return true;
}
const std::string Natural::GetDecimal(uint8_t radix, size_t decimalLength,
	std::function<bool(char)> round) const {
	return GetString(radix);
}
Natural::operator bool() const {
	return !(1 == m_singles.size() && '0' == m_singles.front());
}
Natural Natural::Factorial() const {
	Natural product(1, GetRadix());
	for (Natural index(1, GetRadix()); index <= *this; ++index) {
		product *= index;
	}
	return product;
}
bool Natural::operator==(const Natural &other) const {
	const Natural &radixOther = other.GetNatural(m_radix);
	return m_singles == radixOther.m_singles;
}
bool Natural::operator>(const Natural &other) const {
	const Natural &radixOther = other.GetNatural(m_radix);
	if (m_singles.size() < radixOther.m_singles.size()) {
		return false;
	}
	else if (m_singles.size() > radixOther.m_singles.size()) {
		return true;
	}
	else {
		for (auto bit = m_singles.crbegin(), oBit = radixOther.m_singles.crbegin();
			bit != m_singles.crend() && oBit != radixOther.m_singles.crend();
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
bool Natural::operator<(const Natural &other) const {
	return other > *this;
}
bool Natural::operator>=(const Natural &other) const {
	return *this > other || *this == other;
}
bool Natural::operator<=(const Natural &other) const {
	return *this < other || *this == other;
}
Natural Natural::operator+(const Natural &addition) const {
	const Natural &radixAddition = addition.GetNatural(m_radix);
	std::list<char> result;
	bool isCarray = false;
	for (auto bit = m_singles.cbegin(), aBit = radixAddition.m_singles.cbegin();
		bit != m_singles.cend() || aBit != radixAddition.m_singles.cend();) {
		uint8_t bitValue = 0;
		if (bit != m_singles.cend()) {
			bitValue = GetValue(*bit);
		}
		uint8_t aBitValue = 0;
		if (aBit != radixAddition.m_singles.cend()) {
			aBitValue = GetValue(*aBit);
		}
		if (bitValue + aBitValue + isCarray >= m_radix) {
			result.push_back(
				GetChar((bitValue + aBitValue + isCarray)%m_radix));
			isCarray = true;
		}
		else {
			result.push_back(
				GetChar(bitValue + aBitValue + isCarray));
			isCarray = false;
		}
		if (bit != m_singles.cend())
			bit++;
		if (aBit != radixAddition.m_singles.cend())
			aBit++;
	}
	if (isCarray) {
		result.push_back('1');
	}
	return Natural(result, GetRadix()).Format();
}
Natural &Natural::operator+=(const Natural &addition) {
	*this = *this + addition;
	return *this;
}
Natural Natural::operator-(const Natural &subtrahend) const {
	assert(*this >= subtrahend);
	const Natural &radixSubtrahend = subtrahend.GetNatural(m_radix);
	std::list<char> result;
	bool isCarray = false;
	for (auto bit = m_singles.cbegin(), sBit = radixSubtrahend.m_singles.cbegin();
		bit != m_singles.cend(); bit++) {
		uint8_t bitValue = GetValue(*bit);
		uint8_t sBitValue = 0;
		if (sBit != radixSubtrahend.m_singles.cend()) {
			sBitValue = GetValue(*sBit);
		}
		if (bitValue - sBitValue - isCarray < 0) {
			result.push_back(
				GetChar(m_radix + bitValue - sBitValue - isCarray));
			isCarray = true;
		}
		else {
			result.push_back(
				GetChar(bitValue - sBitValue - isCarray));
			isCarray = false;
		}
		if(sBit != radixSubtrahend.m_singles.cend())
			sBit++;
	}
	assert(!isCarray);
	return Natural(result, GetRadix()).Format();
}
Natural &Natural::operator-=(const Natural &subtrahend) {
	*this = *this - subtrahend;
	return *this;
}
Natural Natural::operator*(const Natural &multiplier) const {
	const Natural &radixMultiplier = multiplier.GetNatural(m_radix);
	Natural result(0, GetRadix());
	size_t count = 0;
	for (auto mBit = radixMultiplier.m_singles.cbegin();
		mBit != radixMultiplier.m_singles.cend(); mBit++, count ++) {
		if ('0' != *mBit) {
			Natural item(0, GetRadix());
			for (uint8_t index = 0; index < GetValue(*mBit); index ++) {
				item += *this;
			}
			item.m_singles.insert(item.m_singles.cbegin(), count, '0');
			result += item;
		}
	}
	return result.Format();
}
Natural &Natural::operator*=(const Natural &multiplier) {
	*this = *this * multiplier;
	return *this;
}
Natural Natural::operator/(const Natural &divisor) const {
	Natural quotient(0, m_radix), remainder(0, m_radix);
	Div(divisor, quotient, remainder);
	return quotient;
}
Natural &Natural::operator/=(const Natural &divisor) {
	*this = *this / divisor;
	return *this;
}
Natural Natural::operator%(const Natural &divisor) const {
	Natural quotient(0, m_radix), remainder(0, m_radix);
	Div(divisor, quotient, remainder);
	return remainder;
}
Natural Natural::Power(const Natural &exponent) const {
	const Natural &radixExponent = exponent.GetNatural(m_radix);
	Natural result(1, GetRadix());
	for (Natural count(0, GetRadix()); count < radixExponent; ++count) {
		result = *this * result;
	}
	return result;
}

Natural Natural::Root2(const Natural &exponent, std::vector<char> &singles, size_t index, char top, char bottom, bool &isExhaustive) const {
	char c = GetChar((GetValue(top) + GetValue(bottom)) / 2);
	singles[index] = c;
	const Natural value(std::list<char>(singles.cbegin(), singles.cend()), m_radix);
	const Natural &power = value.Power(exponent);
	if (power == *this) {
		return value;
	}
	else if (power > *this) {
		if (GetValue(c) > GetValue(bottom)) {
			return Root2(exponent, singles, index, GetChar(GetValue(c) - 1), bottom, isExhaustive);
		}
		else {
			if (index) {
				return Root2(exponent, singles, index - 1, GetChar(m_radix - 1), '0', isExhaustive);
			}
			else {
				return Natural(std::list<char>(singles.cbegin(), singles.cend()));
			}
		}
	}
	else {
		if (GetValue(c) < GetValue(top)) {
			if (GetValue(c) < GetValue(top) - 1) {
				return Root2(exponent, singles, index, top, c, isExhaustive);
			}
			else {
				return Root(exponent, singles, index, top, c, isExhaustive);
			}
		}
		else {
			if (index) {
				return Root2(exponent, singles, index - 1, GetChar(m_radix - 1), '0', isExhaustive);
			}
			else {
				return value;
			}
		}
	}
}

Natural Natural::Root(const Natural &exponent, std::vector<char> &singles, size_t index, char top, char bottom, bool &isExhaustive) const {
	char c = top;
	while (GetValue(c) >= GetValue(bottom)) {
		singles[index] = c;
		Natural value(std::list<char>(singles.cbegin(), singles.cend()), m_radix);
		const Natural &power = value.Power(exponent);
		if (power == *this) {
			isExhaustive = true;
			return value;
		}
		else if (power < *this) {
			if (index) {
				return Root2(exponent, singles, index - 1, GetChar(m_radix - 1), '0', isExhaustive);
			}
			else {
				isExhaustive = false;
				return value;
			}
		}
		else {
			c = GetChar(GetValue(c) - 1);
		}
	}
	assert(0);
	return Natural(0, m_radix);
}

Natural Natural::Root(const Natural &exponent, bool &isExhaustive) const {
	size_t len = strtoull(((Natural(m_singles.size(), m_radix) +
		exponent - Natural(1, m_radix)) / exponent).GetString(m_radix).c_str(), NULL, m_radix);
	std::vector<char> singles(len, '0');
	return Root(exponent, singles, len - 1, GetChar(m_radix - 1), '0', isExhaustive);
}
Natural Natural::Root(const Natural &exponent) const {
	bool isExhaustive = false;
	return Root(exponent, isExhaustive);
}
Natural &Natural::operator++() {
	*this = *this + Natural(1, GetRadix());
	return *this;
}
Natural Natural::GreatestCommonDivisor(const Natural &other) const {
	return other ? other.GreatestCommonDivisor(*this%other) : *this;
}
Natural Natural::Composition(const Natural &m) const {
	return Factorial() / (m.Factorial() * (*this - m).Factorial());
}

void Natural::Div(const Natural &divisor, Natural &quotient, Natural &remainder) const {
	if (divisor == Natural(0, GetRadix())) {
		throw "undefined";
	}

	const Natural &radixDivisor = divisor.GetNatural(m_radix);

	if (*this < radixDivisor) {
		remainder = *this;
		quotient = Natural(0, m_radix);
		return;
	}

	quotient.m_singles.clear();
	quotient.m_radix = m_radix;
	remainder.m_singles.clear();
	remainder.m_radix = m_radix;

	size_t times = m_singles.size() - radixDivisor.m_singles.size() + 1;

	auto begin = m_singles.cbegin();
	{
		size_t count = m_singles.size() - radixDivisor.m_singles.size();
		for (size_t index = 0; index < count; index++) {
			begin++;
		}
	}
	
	std::map<std::string, size_t> loop;
	remainder.m_singles = std::list<char>(begin, m_singles.cend());

	for (size_t index = 0; index < times; index++) {
		uint8_t count = 0;
		while (remainder >= radixDivisor) {
			count++;
			remainder -= radixDivisor;
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


uint8_t Natural::GetBuilt()const {
	uint8_t built = 0;
	uint8_t weight = 1;
	for (auto single = m_singles.cbegin(); single != m_singles.cend(); single++, weight*=GetRadix()) {
		built += GetValue(*single) * weight;
	}
	return built;
}
Natural &Natural::Format() {
	while (!m_singles.empty() && '0' == m_singles.back()) {
		m_singles.pop_back();
	}
	if (m_singles.empty()) {
		m_singles.push_back('0');
	}
	return *this;
}

uint16_t Natural::ToBuilt(char a, char b, uint8_t radix) {
	if (10 > radix) {
		assert(('0' <= a && a <= '9') || ('A' <= a && a <= 'A' + radix - 11));
		assert(('0' <= b && b <= '9') || ('A' <= b && b <= 'A' + radix - 11));
	}
	else {
		assert('0' <= a && a <= '0' + radix - 1);
		assert('0' <= b && b <= '0' + radix - 1);
	}
	uint16_t result = 0;
	if ('0' <= a && a <= '9') {
		result += (a - '0') * radix;
	}
	else {
		result += (a - 'A' + 10) * radix;
	}
	if ('0' <= b && b <= '9') {
		result += (b - '0');
	}
	else {
		result += (b - 'A' + 10);
	}
	return result;
}

void Natural::DivN(uint8_t from, uint8_t to, std::list<char> &singles, char &remainder) {
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

Natural Natural::GetNatural(uint8_t radix) const{
	if (m_radix == radix) {
		return *this;
	}
	std::list<char> radixDecimal;
	std::list<char> quotient = m_singles;
	char remainder = '0';
	do {
		DivN(m_radix, radix, quotient, remainder);
		radixDecimal.push_back(remainder);
	} while (quotient.size() > 1 || '0' != quotient.front());
	if (radixDecimal.empty()) {
		radixDecimal.push_back('0');
	}
	return Natural(radixDecimal, radix);
}


Natural &Natural::SetCheckLoop() {
	m_is_check_loop = true;
	return *this;
}

std::string Natural::GetLoop() const {
	if (!m_is_check_loop || -1 == m_loop_begin) {
		return "";
	}
	const std::string singles(m_singles.crbegin(), m_singles.crend());
	return "......{" + singles.substr(m_loop_begin + 1, m_loop_end - m_loop_begin) + "}";
}

char Natural::GetChar(uint8_t value) {
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

uint8_t Natural::GetValue(char c) {
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