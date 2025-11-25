#include <cassert>

#include "number/performance/natural/Algorithm.h"

#include "ChangeBase.h"

#define CHANGE_TO_RADIX 10

namespace performance {
	namespace natural {
		namespace logarithm {
			ChangeBase::ChangeBase(const number::Natural &power, const number::Natural &base)
				: Interface(power, base) {
				assert(!base.EqualZero() && !base.EqualPositiveOne());
				assert(!power.EqualZero());
				const std::string& powerChange = power.GetString(CHANGE_TO_RADIX);
				size_t powerExponent = powerChange.size() - 1;
				const std::string& baseChange = base.GetString(CHANGE_TO_RADIX);
				size_t baseExponent = baseChange.size() > 1 ? baseChange.size() - 1 : 1;
				size_t exponent = powerExponent / baseExponent;
				Algorithm::CorrectExponent correct(exponent, base);
				m_result = Correct(correct);
			}
			std::pair<number::Natural, number::Natural> ChangeBase::Correct(Algorithm::CorrectExponent &exponent) {
				if (exponent.Power() > m_power) {
					if (exponent.IsIncrease()) {
						return std::make_pair(exponent.Exponent() - 1, m_power - m_base.Power(exponent.Exponent() - 1));
					}
					else {
						return Correct(exponent.Decrease());
					}
				}
				else if (exponent.Power() < m_power) {
					return Correct(exponent.Increase());
				}
				else {
					return std::make_pair(exponent.Exponent(), 0);
				}
			}
		}
	}
}
