#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Logarithm.h"

#include "performance/fraction/logarithm/Dissection.h"

namespace number {
	Logarithm::Logarithm():m_power(1), m_base(0),
		m_reduction_power(m_power), m_reduction_base(m_base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Integer &base) :
		m_power(power), m_base(base),
		m_reduction_power(m_power), m_reduction_base(m_base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Fraction &base) :
		m_power(power), m_base(base),
		m_reduction_power(m_power), m_reduction_base(m_base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Integer &base) :
		m_power(power), m_base(base),
		m_reduction_power(m_power), m_reduction_base(m_base) {
		assert(Fraction(0) < m_base && 1 != m_base &&
			Integer(0) < m_power.Numerator() && Integer(0) < m_power.Denominator());
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Fraction &base) :
		m_power(power), m_base(base),
		m_reduction_power(m_power), m_reduction_base(m_base) {
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
		const number::Fraction &fraction =
			performance::fraction::logarithm::Dissection(m_power, m_base, decimalLength).GetResult();
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
		if (!m_power.EqualPositiveOne()) {
			ReduceBase();
			ReducePower();
			ReduceCoefficient();
		}
	}
	void Logarithm::ReduceBase() {
		Natural exponent(2);
		while (true) {
			const Natural &power = Natural(2).Power(exponent);
			if (power >= m_base.Numerator().Value()) {
				break;
			}
			if (power >= m_base.Denominator().Value()) {
				break;
			}
			if (power >= m_power.Numerator().Value()) {
				break;
			}
			if (power >= m_power.Denominator().Value()) {
				break;
			}
			++exponent;
		}
		for (; exponent >= 2; --exponent) {
			const std::pair<Natural, Natural> &baseNumerator = m_base.Numerator().Value().Root(exponent);
			const std::pair<Natural, Natural> &baseDenominator = m_base.Denominator().Value().Root(exponent);
			const std::pair<Natural, Natural> &powerNumerator = m_power.Numerator().Value().Root(exponent);
			const std::pair<Natural, Natural> &powerDenominator = m_power.Denominator().Value().Root(exponent);
			if (baseNumerator.second.EqualZero() && baseDenominator.second.EqualZero() &&
				powerNumerator.second.EqualZero() && powerDenominator.second.EqualZero()) {
				m_reduction_base = Fraction(baseNumerator.first, baseDenominator.first);
				m_reduction_power = Fraction(powerNumerator.first, powerDenominator.first);
				break;
			}
		}
	}
	void Logarithm::ReducePower() {
		Natural exponent(2);
		while (true) {
			const Natural &power = Natural(2).Power(exponent);
			if (power >= m_reduction_power.Numerator().Value()) {
				break;
			}
			if (power >= m_reduction_power.Denominator().Value()) {
				break;
			}
			++exponent;
		}

		for (; exponent >= 2; --exponent) {
			const std::pair<Natural, Natural> &powerNumerator = m_reduction_power.Numerator().Value().Root(exponent);
			const std::pair<Natural, Natural> &powerDenominator = m_reduction_power.Denominator().Value().Root(exponent);
			if (powerNumerator.second.EqualZero() && powerDenominator.second.EqualZero()) {
				m_reduction_coefficient = Integer(exponent);
				m_reduction_power = Fraction(powerNumerator.first, powerDenominator.first);
				break;
			}
		}
	}

	void Logarithm::ReduceCoefficient()
	{
		{
			const auto &coefficient = ReduceCoefficient(m_reduction_power, m_reduction_base);
			if (coefficient.has_value()) {
				m_reduction_coefficient *= coefficient.value();
				m_reduction_power = Integer(2);
				m_reduction_base = Integer(2);
			}
		}
		{
			const auto& coefficient = ReduceCoefficient(m_reduction_base, m_reduction_power);
			if (coefficient.has_value()) {
				m_reduction_coefficient *= coefficient.value().GetReciprocal();
				m_reduction_power = Integer(2);
				m_reduction_base = Integer(2);
			}
		}
	}

	std::optional<Fraction> Logarithm::ReduceCoefficient(const Fraction& power, const Fraction& base) const {
		std::pair<Natural, Natural> numerator(0, 0);
		if (!base.Numerator().Value().EqualPositiveOne()) {
			numerator = power.Numerator().Value().Logarithm(base.Numerator().Value());
		}
		std::pair<Natural, Natural> denominator(0, 0);
		if (!base.Denominator().Value().EqualPositiveOne()) {
			denominator = power.Denominator().Value().Logarithm(base.Denominator().Value());
		}
		if (numerator.second.EqualZero() && denominator.second.EqualZero())
		{
			if (numerator.first == denominator.first ||
				(power.Denominator().Value().EqualPositiveOne() && base.Denominator().EqualPositiveOne()))
			{
				return Integer(numerator.first);
			}
		}
		return std::nullopt;
	}

	bool Logarithm::IsFraction() const {
		return EqualZero() || m_reduction_base.EqualPositiveOne() ||
			m_reduction_power.EqualPositiveOne() || m_reduction_base == m_reduction_power;
	}

	void Logarithm::Opposite() {
		m_power.Opposite();
	}
	
	std::optional<Logarithm> Logarithm::CheckReduce(const Fraction &power, const Fraction &base) {
		const number::Logarithm reduce(power, base);
		if (reduce.ReductionPower() == power &&
			reduce.ReductionCoefficient().EqualPositiveOne()) {
			return std::nullopt;
		}
		else {
			return reduce;
		}
	}
}