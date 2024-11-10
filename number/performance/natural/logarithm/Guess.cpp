#include "number/performance/natural/Algorithm.h"

#include "Guess.h"

namespace performance {
	namespace natural {
		namespace logarithm {
			Guess::Guess(const number::Natural &power, const number::Natural &base)
				: Interface(power, base) {
				size_t order = MaxOrders();
				std::vector<char> singles(order, '0');
				m_result = Algorithm::PowerInverseHalf(m_power, base,
					singles,
					order - 1,
					m_power.GetChar(LITERAL_DEFAULT_RADIX - 1),
					'0',
					[&base](const number::Natural &factor, const number::Natural &value) {
						return base.Power(value);
					});
			}
			size_t Guess::MaxOrders() const {
				if (m_base.CalcOrders() > 1) {
					return number::Natural((m_power.CalcOrders() - 1) / (m_base.CalcOrders() - 1)).GetString().length();
				}
				else {
					return m_power.CalcOrders() > 2 ? m_power.CalcOrders() - 2 : 1;
				}
			}
		}
	}
}
