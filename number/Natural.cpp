#include <cassert>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <string>
#include "Natural.h"
#include "performance/natural/root/Guess.h"
#include "performance/natural/logarithm/Guess.h"
#include "performance/natural/logarithm/ChangeBase.h"

namespace number {
	Natural::Natural(uint64_t value) {
		if (value) {
			while (value) {
				m_singles.push_back(GetChar(value % CALC_DEFAULT_RADIX));
				value /= CALC_DEFAULT_RADIX;
			}
		}
		else {
			m_singles.push_back('0');
		}
	}
	Natural::Natural(const std::string &value, uint8_t radix) :
		Natural(std::list<char>(value.crbegin(), value.crend()), radix) {

	}
	Natural::Natural(const std::list<char> &singles, uint8_t radix) {
		const std::list<char> &radixSingles = Natural::GetRadixSingles(radix, CALC_DEFAULT_RADIX, singles);
		m_singles.assign(radixSingles.begin(), radixSingles.end());
		if (m_singles.empty()) {
			m_singles.push_back('0');
		}
	}
	const std::string Natural::GetString(uint8_t radix) const {
		assert(2 <= radix && radix <= (11 + ('Z' - 'A')));
		if (CALC_DEFAULT_RADIX != radix) {
			const std::list<char> &radixSingles = Natural::GetRadixSingles(CALC_DEFAULT_RADIX, radix, m_singles);
			return std::string(radixSingles.crbegin(), radixSingles.crend());
		}
		else {
			return std::string(m_singles.crbegin(), m_singles.crend());
		}
	}
	bool Natural::EqualZero() const {
		return Natural(0) == *this;
	}
	bool Natural::EqualPositiveOne() const {
		return Natural(1) == *this;
	}
	bool Natural::EqualNegativeOne() const {
		return false;
	}
	void Natural::SetUnSigned(bool isUnSigned) {
		throw "undefined";
	}
	bool Natural::IsPositive() const {
		return true;
	}
	void Natural::Opposite() {
		throw "undefined";
	}
	const std::string Natural::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		return GetString(radix);
	}
	bool Natural::IsOdd() const {
		return 1 == GetValue(m_singles.front()) % 2;
	}
	Natural Natural::Factorial() const {
		Natural product(1);
		for (Natural index(1); index <= *this; ++index) {
			product *= index;
		}
		return product;
	}
	bool Natural::operator==(const Natural &other) const {
		return m_singles == other.m_singles;
	}
	bool Natural::operator!=(const Natural &other) const {
		return !(*this == other);
	}
	bool Natural::operator>(const Natural &other) const {
		if (CalcOrders() < other.CalcOrders()) {
			return false;
		}
		else if (CalcOrders() > other.CalcOrders()) {
			return true;
		}
		else {
			for (auto bit = m_singles.crbegin(), oBit = other.m_singles.crbegin();
				bit != m_singles.crend() && oBit != other.m_singles.crend();
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
		std::list<char> result;
		bool isCarray = false;
		for (auto bit = m_singles.cbegin(), aBit = addition.m_singles.cbegin();
			bit != m_singles.cend() || aBit != addition.m_singles.cend();) {
			uint8_t bitValue = 0;
			if (bit != m_singles.cend()) {
				bitValue = GetValue(*bit);
			}
			uint8_t aBitValue = 0;
			if (aBit != addition.m_singles.cend()) {
				aBitValue = GetValue(*aBit);
			}
			if (bitValue + aBitValue + isCarray >= CALC_DEFAULT_RADIX) {
				result.push_back(
					GetChar((bitValue + aBitValue + isCarray) % CALC_DEFAULT_RADIX));
				isCarray = true;
			}
			else {
				result.push_back(
					GetChar(bitValue + aBitValue + isCarray));
				isCarray = false;
			}
			if (bit != m_singles.cend())
				bit++;
			if (aBit != addition.m_singles.cend())
				aBit++;
		}
		if (isCarray) {
			result.push_back('1');
		}
		return Natural(result, CALC_DEFAULT_RADIX).Format();
	}
	Natural &Natural::operator+=(const Natural &addition) {
		*this = *this + addition;
		return *this;
	}
	Natural Natural::operator-(const Natural &subtrahend) const {
		assert(*this >= subtrahend);
		std::list<char> result;
		bool isCarray = false;
		for (auto bit = m_singles.cbegin(), sBit = subtrahend.m_singles.cbegin();
			bit != m_singles.cend(); bit++) {
			uint8_t bitValue = GetValue(*bit);
			uint8_t sBitValue = 0;
			if (sBit != subtrahend.m_singles.cend()) {
				sBitValue = GetValue(*sBit);
			}
			if (bitValue - sBitValue - isCarray < 0) {
				result.push_back(
					GetChar(CALC_DEFAULT_RADIX + bitValue - sBitValue - isCarray));
				isCarray = true;
			}
			else {
				result.push_back(
					GetChar(bitValue - sBitValue - isCarray));
				isCarray = false;
			}
			if (sBit != subtrahend.m_singles.cend())
				sBit++;
		}
		assert(!isCarray);
		return Natural(result, CALC_DEFAULT_RADIX).Format();
	}
	Natural &Natural::operator-=(const Natural &subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	Natural Natural::operator*(const Natural &multiplier) const {
		Natural result(0);
		size_t count = 0;
		for (auto mBit = multiplier.m_singles.cbegin();
			mBit != multiplier.m_singles.cend(); mBit++, count++) {
			if ('0' != *mBit) {
				Natural item(0);
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
		Natural result(1);
		for (Natural count(0); count < exponent; ++count) {
			result = *this * result;
		}
		return result;
	}

	std::pair<Natural, Natural> Natural::Root(const Natural &exponent) const {
		return performance::natural::root::Guess(*this, exponent).GetResult();
	}

	std::pair<Natural, Natural> Natural::Logarithm(const Natural &base) const {
		//return performance::natural::logarithm::Guess(*this, base).GetResult();
		return performance::natural::logarithm::ChangeBase(*this, base).GetResult();
	}

	const std::list<Natural> &Natural::GetFactors() {
		if (m_factors.empty()) {
			std::set<Natural, std::function<bool(const Natural&, const Natural&)>> factors(
				[](const Natural &front, const Natural &back) {return front < back; });
			for (Natural divisor(1); divisor <= *this/2; ++divisor) {
				if (factors.find(divisor) == factors.end()) {
					const std::pair<Natural, Natural> &quotient = Div(divisor);
					if (quotient.second.EqualZero()) {
						factors.insert(divisor);
						factors.insert(quotient.first);
					}
				}
			}
			for (const auto &factor : factors) {
				m_factors.push_back(factor);
			}
		}
		return m_factors;
	}

	Natural &Natural::operator++() {
		*this = *this + Natural(1);
		return *this;
	}
	Natural &Natural::operator--() {
		*this = *this - Natural(1);
		return *this;
	}
	Natural Natural::GreatestCommonDivisor(const Natural &other) const {
		return !other.EqualZero() ? other.GreatestCommonDivisor(*this%other) : *this;
	}
	Natural Natural::Composition(const Natural &m) const {
		return Factorial() / (m.Factorial() * (*this - m).Factorial());
	}

	std::pair<Natural, Natural> Natural::Div(const Natural &divisor) const {
		if (divisor == Natural(0)) {
			throw "undefined";
		}

		if (*this < divisor) {
			return std::make_pair<Natural, Natural>(Natural(0), Natural(*this));
		}

		Natural quotient(0);
		Natural dividend(0);
		
		for (auto single = m_singles.crbegin(); single != m_singles.crend(); single++) {
			dividend = dividend.CalcPower(1) + GetValue(*single);
			uint8_t count = 0;
			while (dividend >= divisor) {
				count++;
				dividend -= divisor;
			}
			quotient = quotient.CalcPower(1) + count;
		}

		return std::make_pair(quotient.Format(), dividend.Format());
	}


	uint8_t Natural::GetBuilt()const {
		uint8_t built = 0;
		uint8_t weight = 1;
		for (auto single = m_singles.cbegin(); single != m_singles.cend(); single++, weight *= CALC_DEFAULT_RADIX) {
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

	std::list<char> Natural::GetRadixSingles(uint8_t from, uint8_t to, const std::list<char> &singles) {
		if (from == to) {
			return singles;
		}
		std::list<char> radixDecimal;
		std::list<char> quotient = singles;
		char remainder = '0';
		do {
			DivN(from, to, quotient, remainder);
			radixDecimal.push_back(remainder);
		} while (quotient.size() > 1 || '0' != quotient.front());
		if (radixDecimal.empty()) {
			radixDecimal.push_back('0');
		}
		return radixDecimal;
	}

	size_t Natural::CalcOrders() const {
		return m_singles.size();
	}
	Natural Natural::CalcOrders(size_t length) const {
		Natural orders(*this);
		while (orders.CalcOrders() < length) {
			orders.m_singles.push_back('0');
		}
		return orders;
	}
	Natural Natural::CalcPower(size_t exponent) const {
		Natural power(*this);
		for (size_t e = 0; e < exponent; ++e) {
			power.m_singles.push_front('0');
		}
		return power;
	}
	Natural Natural::CalcApproximation(size_t length) const {
		Natural approximation(*this);
		size_t index = 0;
		for (auto single = approximation.m_singles.rbegin();
			single != approximation.m_singles.rend(); ++single) {
			if (index++ >= length) {
				*single = '0';
			}
		}
		return approximation;
	}
	std::pair<Natural, size_t> Natural::CalcBase() const {
		size_t exponent = 0;
		Natural base(*this);
		while ('0' == base.m_singles.front()) {
			base.m_singles.pop_front();
		}
		return std::make_pair(base, exponent);
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