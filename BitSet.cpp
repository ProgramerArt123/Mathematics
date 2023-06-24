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
BitSet::BitSet() {

}
BitSet::BitSet(const std::vector<char> &bits) {
	for (auto bit = bits.crbegin(); bit != bits.crend(); bit++) {
		assert('0' <= *bit && *bit <= '1');
		if ('1' == *bit) {
			m_bits.insert(m_bits.cbegin(), '1');
		}
		else {
			if (!m_bits.empty()) {
				m_bits.insert(m_bits.cbegin(), '0');
			}
		}
	}
	if (m_bits.empty()) {
		m_bits.push_back('0');
	}
}
BitSet::operator bool() const {
	return !m_bits.empty();
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
		for (size_t index = 0; index < m_bits.size(); index++) {
			size_t j = m_bits.size() - 1 - index;
			if (m_bits[j] == other.m_bits[j]) {
				continue;
			}
			else {
				return m_bits[j] > other.m_bits[j];
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

	size_t count = m_bits.size() >= addition.m_bits.size() ?
		m_bits.size() : addition.m_bits.size();
	bool isCarray = false;
	for (size_t index = 0; index < count; index++) {
		unsigned char bit = 0;
		if (index < m_bits.size()) {
			bit = m_bits[index] - '0';
		}
		unsigned char aBit = 0;
		if (index < addition.m_bits.size()) {
			aBit = addition.m_bits[index] - '0';
		}
		switch (bit + aBit + isCarray)
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

	size_t count = m_bits.size();
	bool isCarray = false;
	for (size_t index = 0; index < count; index++) {
		unsigned char bit = m_bits[index] - '0';
		unsigned char sBit = 0;
		if (index < subtrahend.m_bits.size()) {
			sBit = subtrahend.m_bits[index] - '0';
		}
		switch (bit - sBit - isCarray)
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

	for (size_t index = 0; index < multiplier.m_bits.size(); index++) {
		if ('1' == multiplier.m_bits[index]) {
			BitSet item(*this);
			for (size_t count = 0; count < index; count++) {
				item.m_bits.insert(item.m_bits.cbegin(), '0');
			}
			result += item;
		}
	}

	return result.Format();
}
BitSet BitSet::operator/(const BitSet &divisor) const {
	if (*this < divisor) {
		return BitSet(0);
	}

	BitSet result;

	size_t times = m_bits.size() - divisor.m_bits.size() + 1;

	BitSet remaining(std::vector<char>(m_bits.cend() -
		divisor.m_bits.size(), m_bits.cend()));
	for (size_t index = 0; index < times; index++) {
		if (remaining >= divisor) {
			result.m_bits.insert(result.m_bits.cbegin(), '1');
			remaining -= divisor;
		}
		else {
			result.m_bits.insert(result.m_bits.cbegin(), '0');
		}
		if (index < times - 1) {
			remaining.m_bits.insert(remaining.m_bits.cbegin(),
				m_bits[m_bits.size() - 1 - (divisor.m_bits.size() + index)]);
			remaining.Format();
		}
	}

	return result.Format();
}
BitSet &BitSet::operator/=(const BitSet &divisor) {
	*this = *this / divisor;
	return *this;
}
BitSet BitSet::operator%(const BitSet &divisor) const {
	return *this - *this / divisor * divisor;
}
BitSet &BitSet::operator++() {
	*this = *this + BitSet(1);
	return *this;
}
const std::string BitSet::GetString(uint8_t base) const {
	assert(2 <= base && base <= (11 + ('Z' - 'A')));
	const BitSet &bitBase = BitSet(base);
	const BitSet &bitZero = BitSet(0);
	std::list<char> result;
	BitSet remaining(*this);
	do {
		const BitSet &mod = remaining % bitBase;
		uint8_t built = mod.GetBuilt();
		if (0 <= built && built <= 9) {
			result.push_front('0' + built);
		}
		else {
			result.push_front('A' + (built - 10));
		}
		remaining /= bitBase;
	} while (remaining > bitZero);
	return std::string(result.cbegin(), result.cend());
}
uint8_t BitSet::GetBuilt()const {
	uint8_t built = 0;
	for (size_t index = 0; index < m_bits.size(); index++) {
		if ('1' == m_bits[index]) {
			built += (1 << index);
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

std::ostream& operator<<(std::ostream& out, const BitSet &bits) {
	out << bits.GetString().c_str();
	return out;
}