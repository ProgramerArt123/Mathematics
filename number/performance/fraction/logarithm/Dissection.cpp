#include <cassert>
#include "Dissection.h"

#define APPROXIMATION_DEPTH 3
#define APPROXIMATION_LENGTH 10

#include "number/performance/natural/Algorithm.h"

namespace performance {
	namespace fraction {
		namespace logarithm {
			Dissection::Dissection(const number::Fraction &power, const number::Fraction &base, size_t decimalLength)
				: Interface(power, base) {
				const number::Fraction &numerator = GetApproximation(m_power.Numerator(), decimalLength);
				number::Fraction denominator(0);
				if (!m_power.IsInteger()) {
					denominator = GetApproximation(m_power.Denominator(), decimalLength);
				}
				m_result = numerator - denominator;
			}
			number::Fraction Dissection::GetApproximation(const number::Natural &power, size_t decimalLength)const {
				if (power.EqualPositiveOne()) {
					return number::Fraction(0);
				}
				if (m_base.IsInteger()) {
					return GetApproximationInverse‌(power, m_base.ReductionInteger(), 0);
				}
				number::Fraction changeBaseNumerator = Dissection(number::Fraction(power), number::Fraction(2), decimalLength).GetResult();
				number::Fraction changeBaseDenominator = Dissection(m_base, number::Fraction(2), decimalLength).GetResult();
				return changeBaseNumerator / changeBaseDenominator;
			}
			number::Fraction Dissection::GetApproximationValue(const number::Natural &power, const number::Natural &base, int approximation) const {
				assert(number::Natural(0) < base && number::Natural(1) != base);
				assert(power >= base);
				const std::pair<number::Natural, number::Natural> &logarithm = power.Logarithm(base);
				number::Fraction logarithmApproximation = number::Fraction(logarithm.first);
				if (approximation < APPROXIMATION_DEPTH) {
					number::Fraction remainder = number::Fraction(power, power - logarithm.second);
					number::Fraction exponentRemainder = remainder.Power(APPROXIMATION_LENGTH);
					if (!exponentRemainder.ReductionInteger().EqualPositiveOne()) {
						number::Fraction remainderLogarithm = GetApproximationInverse‌(exponentRemainder.ReductionInteger(), base, approximation + 1);
						logarithmApproximation += (remainderLogarithm / APPROXIMATION_LENGTH);
					}
				}
				return logarithmApproximation;
			}

			number::Fraction Dissection::GetApproximationInverse‌(const number::Natural &power, const number::Natural &base, int approximation)const {
				if (power >= base) {
					return GetApproximationValue(power, base, approximation);
				}
				else {
					return GetApproximationValue(base, power, approximation).GetReciprocal();
				}
			}
		}
	}
}
