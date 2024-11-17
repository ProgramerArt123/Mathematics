#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Logarithm.h"

#include "number/performance/natural/Algorithm.h"

#define APPROXIMATION_DEPTH 3
#define APPROXIMATION_LENGTH 5

namespace number {
	Logarithm::Logarithm():m_power(1), m_base(0) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Integer &base) :
		m_power(power), m_base(base){
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Fraction &base) :
		m_power(power), m_base(base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Integer &base) :
		m_power(power), m_base(base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Fraction &base) :
		m_power(power), m_base(base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	const std::string Logarithm::GetString(uint8_t radix) const {
		if (!IsFraction()) {
			return m_reduction_power.GetString(radix) + "#" + m_reduction_base.GetString(radix);
		}
		else {
			return m_reduction_coefficient.GetString(radix) + "{" + m_reduction_power.GetString(radix) + "#" + m_reduction_base.GetString(radix) + "}";
		}
	}
	bool Logarithm::EqualZero() const {
		return m_reduction_coefficient.EqualZero() || m_reduction_power.EqualPositiveOne();
	}
	bool Logarithm::EqualPositiveOne() const {
		return IsPositive() && m_reduction_coefficient.EqualPositiveOne() && m_reduction_power == m_base;
	}
	bool Logarithm::EqualNegativeOne() const {
		return IsPositive() && m_reduction_coefficient.EqualPositiveOne() && m_reduction_power == m_base;
	}
	void Logarithm::SetUnSigned(bool isUnSigned) {
		m_power.SetUnSigned(isUnSigned);
		m_base.SetUnSigned(true);
		Reduce();
	}
	bool Logarithm::IsPositive() const {
		return m_power.IsPositive() == m_base.IsPositive();
	}
	const std::string Logarithm::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		const Fraction &numerator = GetFraction(m_power.Numerator(), radix, decimalLength);
		Fraction denominator(0);
		if (!m_power.IsInteger()) {
			denominator = GetFraction(m_power.Denominator(), radix, decimalLength);
		}
		const Fraction &fraction = numerator - denominator;
		return fraction.GetDecimal(radix, decimalLength, round);
	}
	Logarithm Logarithm::operator-() const {
		Logarithm opposite(*this);
		opposite.Opposite();
		return opposite;
	}
	bool Logarithm::operator==(const Logarithm &other) const {
		return m_reduction_power == other.m_reduction_power &&
			m_reduction_coefficient == other.m_reduction_coefficient &&
			m_base == other.m_base;
	}
	const Fraction &Logarithm::Power()const {
		return m_power;
	}
	const Fraction &Logarithm::Base()const {
		return m_base;
	}
	const Fraction &Logarithm::ReductionCoefficient()const {
		return m_reduction_coefficient;
	}
	const Fraction &Logarithm::ReductionPower()const {
		return m_reduction_power;
	}
	const Fraction &Logarithm::ReductionBase()const {
		return m_reduction_base;
	}
	void Logarithm::Reduce() {
		//if (!m_power.EqualPositiveOne()) {
		//	ReduceExponent();
		//	ReducePower();
		//}
	}
	void Logarithm::ReduceExponent() {
		Natural min = m_base.Numerator().Value();
		if (m_base.Denominator().Value() < min) {
			min = m_base.Denominator().Value();
		}
		if (m_power.Numerator().Value() < min) {
			min = m_power.Numerator().Value();
		}
		if (m_power.Denominator().Value() < min) {
			min = m_power.Denominator().Value();
		}
		for (;min >= 2; --min) {
			const std::pair<Natural, Natural> &baseNumerator = m_base.Numerator().Value().Root(min);
			const std::pair<Natural, Natural> &baseDenominator = m_base.Denominator().Value().Root(min);
			const std::pair<Natural, Natural> &powerNumerator = m_power.Numerator().Value().Root(min);
			const std::pair<Natural, Natural> &powerDenominator = m_power.Denominator().Value().Root(min);
			if (baseNumerator.second.EqualZero() && baseDenominator.second.EqualZero() &&
				powerNumerator.second.EqualZero() && powerDenominator.second.EqualZero()) {
				m_reduction_base = Fraction(baseNumerator.first, baseDenominator.first);
				m_reduction_power = Fraction(powerNumerator.first, powerDenominator.first);
				break;
			}
		}
	}
	void Logarithm::ReducePower() {
		Natural min = m_power.Numerator().Value();
		if (m_power.Denominator().Value() < min) {
			min = m_power.Denominator().Value();
		}
		for (; min >= 2; --min) {
			const std::pair<Natural, Natural> &powerNumerator = m_power.Numerator().Value().Root(min);
			const std::pair<Natural, Natural> &powerDenominator = m_power.Denominator().Value().Root(min);
			if (powerNumerator.second.EqualZero() && powerDenominator.second.EqualZero()) {
				m_reduction_coefficient = Integer(min);
				m_reduction_power = Fraction(powerNumerator.first, powerDenominator.first);
				break;
			}
		}
	}

	bool Logarithm::IsFraction() const {
		return EqualZero() || m_reduction_base.EqualPositiveOne() || m_reduction_power.EqualPositiveOne();
	}

	Fraction Logarithm::GetFraction(const Integer &power, uint8_t radix, size_t decimalLength)const {
		const Fraction &numerator = GetFraction(m_base.Numerator(), power);
		Fraction denominator(0);
		if (!m_base.IsInteger()) {
			denominator = GetFraction(m_base.Denominator(), power);
		}
		return Fraction(numerator - denominator).GetReciprocal();
	}

	void Logarithm::Opposite() {
		m_power.Opposite();
	}

	Fraction Logarithm::GetFraction(const Integer &power, const Integer &base, bool point, int approximation) const {
		assert(Integer(0) < base && Integer(1) != base);
		performance::natural::Algorithm::CorrectExponent correct(1, power.Value(), point ? APPROXIMATION_LENGTH : 0);
		while (correct.Power() < base.Value()) {
			correct.Increase();
		}
		const Natural &correctPower = correct.Power();
		const std::pair<Natural, Natural> &logarithm = correctPower.Logarithm(base.Value());
		if (approximation < APPROXIMATION_DEPTH) {
			Fraction remainder;
			if (!point) {
				remainder = Fraction(correctPower.CalcPower(APPROXIMATION_LENGTH), correctPower - logarithm.second);
			}
			else {
				remainder = Fraction(correct.PointPower(), correctPower - logarithm.second);
			}
			return Fraction(logarithm.first + GetFraction(remainder.ReductionInteger(), base, true, approximation + 1), correct.Exponent());
		}
		else {
			return Fraction(logarithm.first, correct.Exponent());
		}
	}
	Fraction Logarithm::GetFraction(const Integer &power, const Integer &base)const {
		if (power >= base) {
			return GetFraction(power, base, false, 0);
		}
		else {
			return GetFraction(base, power, false, 0).GetReciprocal();
		}
	}
}