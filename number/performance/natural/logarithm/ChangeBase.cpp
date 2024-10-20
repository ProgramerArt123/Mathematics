#include "number/performance/natural/Algorithm.h"

#include "ChangeBase.h"

#define CHANGE_TO_RADIX 2

namespace performance {
	namespace natural {
		namespace logarithm {
			ChangeBase::ChangeBase(const number::Natural &power, const number::Natural &base)
				: Interface(power, base) {
				const std::string &powerChange = power.GetString(CHANGE_TO_RADIX);
				size_t powerExponent = powerChange.size() - 1;
				const std::string &baseChange = base.GetString(CHANGE_TO_RADIX);
				size_t baseExponent = baseChange.size() - 1;
				size_t exponent = powerExponent / baseExponent;
				const number::Natural &checkPower = m_base.Power(exponent);
				m_result = Correct(exponent, checkPower);
			}
			std::pair<number::Natural, number::Natural> ChangeBase::Correct(size_t exponent, const number::Natural &power, bool up) {
				if (power > m_power) {
					if (up) {
						return std::make_pair(exponent - 1, 0);
					}
					else {
						return Correct(exponent - 1, power / m_base);
					}
				}
				else if (power < m_power) {
					return Correct(exponent + 1, power * m_base, true);
				}
				else {
					return std::make_pair(exponent, 0);
				}
			}
		}
	}
}
