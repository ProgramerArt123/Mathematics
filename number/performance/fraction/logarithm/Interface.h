#ifndef __PERFORMANCE_FRACTION_LOGARITHM_INTERFACE_H__
#define __PERFORMANCE_FRACTION_LOGARITHM_INTERFACE_H__

#include <utility>
#include "number/Fraction.h"

namespace performance {
	namespace fraction {
		namespace logarithm {
			class Interface{
			public:
				Interface(const number::Fraction &power, const number::Fraction &base)
					: m_power(power), m_base(base) {
				}
				number::Fraction GetResult() const
				{
					return m_result;
				}
			protected:
				const number::Fraction &m_power;
				const number::Fraction &m_base;
				number::Fraction m_result;
				std::pair<number::Fraction, number::Fraction> m_remainders;
			};
		}
	}
}
#endif