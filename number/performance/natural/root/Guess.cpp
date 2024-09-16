#include "Guess.h"

namespace performance {
	namespace natural {
		namespace root {
			Guess::Guess(const number::Natural &number, const number::Natural &exponent)
				: Interface(number, exponent) {
				size_t len = (size_t)strtoull(((number::Natural(m_number.m_singles.size(), m_number.m_radix) +
				exponent - number::Natural(1, m_number.m_radix)) / exponent).GetString(m_number.m_radix).c_str(),
					NULL,
					m_number.m_radix);
				std::vector<char> singles(len, '0');
				m_result = m_number.PowerInverse(exponent,
					singles,
					len - 1,
					m_number.GetChar(m_number.m_radix - 1),
					'0',
					[&exponent](const number::Natural &factor, const number::Natural &value) {
						return value.Power(exponent);
					});
			}
			
		}
	}
}
