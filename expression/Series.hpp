#ifndef __EXPRESSION_SERIES_HPP__
#define __EXPRESSION_SERIES_HPP__

#include <vector>
#include <map>
#include <functional>

#include "Output.h"

namespace expression {
	template<typename MonomialValue, typename SeriesValue = MonomialValue>
	class Series : public Output {
		static_assert(std::is_base_of<number::Number, MonomialValue>::value, "Monomial invalid");
	public:
		Series(std::function<MonomialValue(const uint64_t index)> monomial) :
			m_monomial(monomial) {
		}
		Series<MonomialValue> Summation(size_t length = 0) const{
			Series<MonomialValue> sum(*this);
			size_t realLength = m_max_length;
			if (length) {
				realLength = length < sum.m_max_length ? length : sum.m_max_length;
			}
			if (sum.m_polynomial.size() < realLength) {
				for (size_t index = sum.m_polynomial.size() + 1; index <= realLength; index++) {
					sum.m_polynomial.push_back(sum.m_monomial(index));
				}
			}
			else if (sum.m_polynomial.size() > realLength) {
				sum.m_polynomial.resize(realLength);
			}
			return sum;
		}
		SeriesValue GetMonomial() const {
			SeriesValue summation;
			for (size_t index = 0; index < m_polynomial.size(); index++) {
				if (m_updates.find(index) == m_updates.end()) {
					summation = summation + m_polynomial[index];
				}
				else {
					summation = summation + m_updates.at(index);
				}
			}
			return summation;
		}
		const std::string OutPutString(size_t pos = 0) const override {
			return GetMonomial().OutPutString(pos);
		}

		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const {
			return GetMonomial().GetDecimal(radix, decimalLength, round);
		}
		void SetMaxLength(size_t length) {
			m_max_length = length;
		}
		size_t GetMaxLength() const {
			return m_max_length;
		}
		void Foreach(std::function<bool(const MonomialValue &value, const size_t index)> itor) {
			for (size_t i = 0; i < m_polynomial.size(); i ++) {
				if (!itor(m_polynomial[i], i)) {
					break;
				}
			}
		}
		void Update(const MonomialValue &value, const size_t index) {
			m_updates.emplace(index, value);
		}
	private:
		std::vector<MonomialValue> m_polynomial;
		std::map<size_t, MonomialValue> m_updates;
		std::function<MonomialValue(const uint64_t index)> m_monomial;
		size_t m_max_length = SIZE_MAX;
	};
}

#endif