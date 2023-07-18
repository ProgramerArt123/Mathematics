#ifndef __SERIES_HPP__
#define __SERIES_HPP__

#include <vector>
#include <functional>

#include "Output.h"

template<typename MonomialValue>
class Series : public Output{
	static_assert(std::is_base_of<Number, MonomialValue>::value, "Monomial invalid");
public:
	Series(std::function<MonomialValue(const uint64_t index)> monomial) :
		m_monomial(monomial) {

	}
	Series<MonomialValue> &Summation(size_t length) {
		if (m_polynomial.size() < length) {
			for (size_t index = m_polynomial.size() + 1; index <= length; index++) {
				m_polynomial.push_back(m_monomial(index));
			}
		}
		else if (m_polynomial.size() > length) {
			m_polynomial.resize(length);
		}
		return *this;
	}
	MonomialValue GetMonomial() const{
		MonomialValue summation;
		for (const auto &monomial : m_polynomial) {
			summation += monomial;
		}
		return summation;
	}
	const std::string GetString(uint8_t radix = 10) const override {
		return GetMonomial().GetString(radix);
	}
	const std::string GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round = [](char last) {return false; }) const override {
		return GetMonomial().GetDecimal(radix, decimalLength, round);
	}
private:
	std::vector<MonomialValue> m_polynomial;
	std::function<MonomialValue(const uint64_t index)> m_monomial;
};


#endif