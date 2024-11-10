#include "number/performance/natural/Algorithm.h"

#include "Guess.h"

namespace performance {
	namespace natural {
		namespace root {
			Guess::Guess(const number::Natural &power, const number::Natural &exponent)
				: Interface(power, exponent) {
				size_t order = MaxOrders();
				std::vector<char> singles(order, '0');
				m_result = Algorithm::PowerInverseHalf(m_power, exponent,
					singles,
					order - 1,
					m_power.GetChar(LITERAL_DEFAULT_RADIX - 1),
					'0',
					[&exponent](const number::Natural &factor, const number::Natural &value) {
						return value.Power(exponent);
					});
			}
			size_t Guess::MaxOrders() const {
				return (size_t)strtoull(((number::Natural(m_power.CalcOrders()) +
					m_exponent - number::Natural(1)) / m_exponent).GetString().c_str(),
					NULL, LITERAL_DEFAULT_RADIX);
			}
		}
	}
}
