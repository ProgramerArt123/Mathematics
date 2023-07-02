#ifndef __SERIES_HPP__
#define __SERIES_HPP__

#include <vector>
#include <functional>
#include "Number.h"

template<typename MonomialValue>
class Series : public Number {
	static_assert(std::is_base_of_v<Number, MonomialValue>, "Monomial invalid");
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
	const std::string GetString(uint8_t base = 10) const override {
		return GetMonomial().GetString(base);
	}
private:
	std::vector<MonomialValue> m_polynomial;
	std::function<MonomialValue(const uint64_t index)> m_monomial;
};


#endif