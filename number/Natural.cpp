#include <cassert>
#include <list>
#include <map>
#include <vector>
#include <string>
#include "Natural.h"
#include "performance/natural/root/Guess.h"
namespace number {
	Natural::Natural(uint64_t value, uint8_t radix) :m_radix(radix) {
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
	Natural::Natural(const std::string &value, uint8_t radix) :
		Natural(std::list<char>(value.crbegin(), value.crend()), radix) {

	}

	Natural::Natural(const std::list<char> &singles, uint8_t radix) :
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
		std::list<char> str;
		Natural remaining(*this);
		do {
			std::pair<Natural, Natural> result(remaining.Div(bitRadix));
			uint8_t built = result.second.GetBuilt();
			if (0 <= built && built <= 9) {
				str.push_front('0' + built);
			}
			else {
				str.push_front('A' + (built - 10));
			}
			remaining = result.first;
		} while (remaining > bitZero);
		return std::string(str.cbegin(), str.cend());
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
		return Natural(0) == *this;
	}
	bool Natural::EqualOne() const {
		return Natural(1) == *this;
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
	bool Natural::operator!=(const Natural &other) const {
		return !(*this == other);
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
				bit++, oBit++) {
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
					GetChar((bitValue + aBitValue + isCarray) % m_radix));
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
			if (sBit != radixSubtrahend.m_singles.cend())
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
			mBit != radixMultiplier.m_singles.cend(); mBit++, count++) {
			if ('0' != *mBit) {
				Natural item(0, GetRadix());
				for (uint8_t index = 0; index < GetValue(*mBit); index++) {
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
		return Div(divisor).first;
	}
	Natural &Natural::operator/=(const Natural &divisor) {
		*this = *this / divisor;
		return *this;
	}
	Natural Natural::operator%(const Natural &divisor) const {
		return Div(divisor).second;
	}
	Natural Natural::Power(const Natural &exponent) const {
		const Natural &radixExponent = exponent.GetNatural(m_radix);
		Natural result(1, GetRadix());
		for (Natural count(0, GetRadix()); count < radixExponent; ++count) {
			result = *this * result;
		}
		return result;
	}

	std::pair<Natural, Natural> Natural::PowerInverseHalf(const Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<Natural(const Natural&, const Natural&)> power) const {
		char c = GetChar((GetValue(top) + GetValue(bottom)) / 2);
		singles[index] = c;
		const Natural value(std::list<char>(singles.cbegin(), singles.cend()), m_radix);
		const Natural guessValue(power(factor, value));
		if (guessValue == *this) {
			return std::make_pair<Natural, Natural>(Natural(value), Natural(0));
		}
		else if (guessValue > *this) {
			if (GetValue(c) > GetValue(bottom)) {
				return PowerInverseHalf(factor, singles, index, GetChar(GetValue(c) - 1), bottom, power);
			}
			else {
				if (index) {
					return PowerInverseHalf(factor, singles, index - 1, GetChar(m_radix - 1), '0', power);
				}
				else {
					return std::make_pair<Natural, Natural>(Natural(std::list<char>(singles.cbegin(), singles.cend())), Natural(0));
				}
			}
		}
		else {
			if (GetValue(c) < GetValue(top)) {
				if (GetValue(c) < GetValue(top) - 1) {
					return PowerInverseHalf(factor, singles, index, top, c, power);
				}
				else {
					return PowerInverse(factor, singles, index, top, c, power);
				}
			}
			else {
				if (index) {
					return PowerInverseHalf(factor, singles, index - 1, GetChar(m_radix - 1), '0', power);
				}
				else {
					return std::make_pair<Natural, Natural>(Natural(value), Natural(0));
				}
			}
		}
	}

	std::pair<Natural, Natural> Natural::PowerInverse(const Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<Natural(const Natural&, const Natural&)> power) const {
		char c = top;
		while (GetValue(c) >= GetValue(bottom)) {
			singles[index] = c;
			Natural value(std::list<char>(singles.cbegin(), singles.cend()), m_radix);
			const Natural guessValue(power(factor, value));
			if (guessValue == *this) {
				return std::make_pair<Natural, Natural>(Natural(value), Natural(0));
			}
			else if (guessValue < *this) {
				if (index) {
					return PowerInverseHalf(factor, singles, index - 1, GetChar(m_radix - 1), '0', power);
				}
				else {
					return std::make_pair<Natural, Natural>(Natural(value), Natural(*this - guessValue));
				}
			}
			else {
				c = GetChar(GetValue(c) - 1);
			}
		}
		assert(0);
		return std::make_pair<Natural, Natural>(Natural(0, m_radix), Natural(0, m_radix));
	}

	std::pair<Natural, Natural> Natural::Root(const Natural &exponent) const {
		performance::natural::root::Guess algorithm(*this, exponent);
		return algorithm.GetResult();
	}

	std::pair<Natural, Natural> Natural::Logarithm(const Natural &base) const {
		size_t len = (size_t)strtoull(((Natural(m_singles.size(), m_radix) +
			base - Natural(1, m_radix)) / base).GetString(m_radix).c_str(), NULL, m_radix);
		std::vector<char> singles(len, '0');
		return PowerInverse(base, singles, len - 1, GetChar(m_radix - 1), '0',
			[&base](const Natural &factor, const Natural &value) {
			return base.Power(value);
		});
	}
	Natural &Natural::operator++() {
		*this = *this + Natural(1, GetRadix());
		return *this;
	}
	Natural &Natural::operator--() {
		*this = *this - Natural(1, GetRadix());
		return *this;
	}
	Natural Natural::GreatestCommonDivisor(const Natural &other) const {
		return !other.EqualZero() ? other.GreatestCommonDivisor(*this%other) : *this;
	}
	Natural Natural::Composition(const Natural &m) const {
		return Factorial() / (m.Factorial() * (*this - m).Factorial());
	}

	std::pair<Natural, Natural> Natural::Div(const Natural &divisor) const {
		if (divisor == Natural(0, GetRadix())) {
			throw "undefined";
		}

		const Natural &radixDivisor = divisor.GetNatural(m_radix);

		if (*this < radixDivisor) {
			return std::make_pair<Natural, Natural>(Natural(0, m_radix), Natural(*this));
		}

		size_t times = m_singles.size() - radixDivisor.m_singles.size() + 1;

		auto begin = m_singles.cbegin();
		{
			size_t count = m_singles.size() - radixDivisor.m_singles.size();
			for (size_t index = 0; index < count; index++) {
				begin++;
			}
		}

		std::pair<Natural, Natural> result(std::make_pair<Natural, Natural>(Natural(0, m_radix), Natural(0, m_radix)));

		std::map<std::string, size_t> loop;
		result.second.m_singles = std::list<char>(begin, m_singles.cend());

		for (size_t index = 0; index < times; index++) {
			uint8_t count = 0;
			while (result.second >= radixDivisor) {
				count++;
				result.second -= radixDivisor;
			}
			result.first.m_singles.push_front(GetChar(count));
			if (index < times - 1) {
				if (-1 == result.first.m_loop_begin && !result.second.EqualZero()) {
					const std::string key(result.second.m_singles.cbegin(), result.second.m_singles.cend());
					if (loop.find(key) != loop.end()) {
						result.first.m_loop_begin = loop.at(key);
						result.first.m_loop_end = result.first.m_singles.size();
					}
					else {
						loop.insert(std::make_pair(std::string(
							result.second.m_singles.cbegin(), result.second.m_singles.cend()), result.first.m_singles.size()));
					}
				}
				begin--;
				result.second.m_singles.push_front(*begin);
				result.second.Format();
			}
		}
		if (-1 == result.first.m_loop_begin) {
			result.first.Format();
		}

		return result;
	}


	uint8_t Natural::GetBuilt()const {
		uint8_t built = 0;
		uint8_t weight = 1;
		for (auto single = m_singles.cbegin(); single != m_singles.cend(); single++, weight *= GetRadix()) {
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

	Natural Natural::GetNatural(uint8_t radix) const {
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

	std::string Natural::GetLoop() const {
		if (-1 == m_loop_begin) {
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
}