
#include "Dissection.h"

namespace performance {
	namespace fraction {
		namespace root {
			Dissection::Dissection(const number::Fraction &power, const number::Fraction &exponent, size_t decimalLength)
				: Interface(power, exponent) {
				const std::pair<number::Fraction, number::Fraction> &numerator = GetApproximation(m_power.Numerator(), decimalLength);
				const std::pair<number::Fraction, number::Fraction> &denominator = GetApproximation(m_power.Denominator(), decimalLength);
				m_result = number::Fraction(numerator.first, denominator.first);
				m_remainders = std::make_pair(numerator.second, denominator.second);
			}

			std::pair<number::Fraction, number::Fraction> Dissection::GetApproximation(const number::Integer &base, size_t decimalLength)const {
				number::Natural power = base.Value().Power(m_exponent.Denominator().Value());
				for (number::Natural index(1); index <= m_exponent.Numerator().Value(); ++index) {
					power = power.CalcPower(decimalLength + 1);
				}
				const std::pair<number::Natural, number::Natural> &result = power.Root(m_exponent.Numerator().Value());
				number::Fraction root = number::Fraction(result.first) / number::Fraction(number::Natural(1).CalcPower(decimalLength + 1));
				const number::Fraction remainder(result.second, result.first);
				if (m_exponent.IsPositive()) {
					return std::make_pair(root, remainder);
				}
				else {
					return std::make_pair(root.GetReciprocal(), remainder);
				}
			}
		}
	}
}
