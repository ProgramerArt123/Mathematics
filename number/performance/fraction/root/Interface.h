#ifndef __PERFORMANCE_FRACTION_ROOT_INTERFACE_H__
#define __PERFORMANCE_FRACTION_ROOT_INTERFACE_H__

#include <utility>
#include "number/Fraction.h"

namespace performance {
	namespace fraction {
		namespace root {
			class Interface{
			public:
				Interface(const number::Fraction &power, const number::Fraction &exponent)
					: m_power(power), m_exponent(exponent) {
				}
				number::Fraction GetResult() const
				{
					return m_result;
				}
			protected:
				const number::Fraction &m_power;
				const number::Fraction &m_exponent;
				number::Fraction m_result;
				std::pair<number::Fraction, number::Fraction> m_remainders;
			};
		}
	}
}
#endif