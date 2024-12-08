#include <cassert>
#include "Dissection.h"

#define APPROXIMATION_DEPTH 3
#define APPROXIMATION_LENGTH 5

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
			number::Fraction Dissection::GetApproximation(const number::Integer &power, size_t decimalLength)const {
				const number::Fraction &numerator = GetApproximation(m_base.Numerator(), power);
				number::Fraction denominator(0);
				if (!m_base.IsInteger()) {
					denominator = GetApproximation(m_base.Denominator(), power);
				}
				return number::Fraction(numerator - denominator).GetReciprocal();
			}
			number::Fraction Dissection::GetApproximation(const number::Integer &power, const number::Integer &base, bool point, int approximation) const {
				assert(number::Integer(0) < base && number::Integer(1) != base);
				performance::natural::Algorithm::CorrectExponent correct(1, power.Value(), point ? APPROXIMATION_LENGTH : 0);
				while (correct.Power() < base.Value()) {
					correct.Increase();
				}
				const number::Natural &correctPower = correct.Power();
				const std::pair<number::Natural, number::Natural> &logarithm = correctPower.Logarithm(base.Value());
				if (approximation < APPROXIMATION_DEPTH) {
					number::Fraction remainder;
					if (!point) {
						remainder = number::Fraction(correctPower.CalcPower(APPROXIMATION_LENGTH), correctPower - logarithm.second);
					}
					else {
						remainder = number::Fraction(correct.PointPower(), correctPower - logarithm.second);
					}
					return number::Fraction(logarithm.first + GetApproximation(remainder.ReductionInteger(), base, true, approximation + 1), correct.Exponent());
				}
				else {
					return number::Fraction(logarithm.first, correct.Exponent());
				}
			}
			number::Fraction Dissection::GetApproximation(const number::Integer &power, const number::Integer &base)const {
				if (power >= base) {
					return GetApproximation(power, base, false, 0);
				}
				else {
					return GetApproximation(base, power, false, 0).GetReciprocal();
				}
			}
		}
	}
}
