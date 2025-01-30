#ifndef __EXPRESSION_SERIES_HPP__
#define __EXPRESSION_SERIES_HPP__

#include <vector>
#include <map>
#include <functional>
#include <cassert>

#include "Output.h"
#include "number/Number.h"
#include "Operator.h"

namespace expression {
	template<typename MonomialValue, typename SeriesValue = MonomialValue>
	class Series : public Output {
		static_assert(std::is_base_of<number::Number, MonomialValue>::value, "Monomial invalid");
	public:
		Series(std::function<MonomialValue(const uint64_t index)> monomial) :
			m_monomial(monomial) {
		}
		Series<MonomialValue> Approximation(size_t length = 0) const{
			Series<MonomialValue> approximation(*this);
			size_t realLength = m_max_length;
			if (length) {
				realLength = length < approximation.m_max_length ? length : approximation.m_max_length;
			}
			if (approximation.m_polynomial.size() < realLength) {
				for (size_t index = approximation.m_polynomial.size() + 1; index <= realLength; index++) {
					approximation.m_polynomial.push_back(approximation.m_monomial(index));
				}
			}
			else if (approximation.m_polynomial.size() > realLength) {
				approximation.m_polynomial.resize(realLength);
			}
			return approximation;
		}
		SeriesValue GetMonomial(OPERATOR_TYPE_FLAG op = OPERATOR_TYPE_FLAG_ADD) const {
			SeriesValue monomial;
			for (size_t index = 0; index < m_polynomial.size(); index++) {
				if (m_updates.find(index) == m_updates.end()) {
					monomial = GetMonomial(monomial, m_polynomial[index], op);
				}
				else {
					monomial = GetMonomial(monomial, m_updates.at(index), op);
				}
			}
			return monomial;
		}
		const std::string OutPutString() const override {
			return GetMonomial().OutPutString();
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

		static const SeriesValue GetMonomial(const SeriesValue &monomial, const SeriesValue &append, OPERATOR_TYPE_FLAG op = OPERATOR_TYPE_FLAG_ADD) {
			switch (op)
			{
			case OPERATOR_TYPE_FLAG_ADD:
				return monomial + append;
				break;
			case OPERATOR_TYPE_FLAG_MUL:
				return monomial * append;
				break;
			default:
				assert(0);
				return monomial;
				break;
			}
		}
	};
}

#endif