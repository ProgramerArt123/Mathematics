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
					m_power.GetChar(DEFAULT_RADIX - 1),
					'0',
					[&base](const number::Natural &factor, const number::Natural &value) {
						return base.Power(value);
					});
			}
			size_t Guess::MaxOrders() const {
				if (m_base.Orders() > 1) {
					return number::Natural((m_power.Orders() - 1) / (m_base.Orders() - 1)).GetString().length();
				}
				else {
					return m_power.Orders() > 2 ? m_power.Orders() - 2 : 1;
				}
			}
		}
	}
}
