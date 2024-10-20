#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Logarithm.h"

namespace number {
	Logarithm::Logarithm():m_power(1), m_base(0) {
		assert(!(1 == m_base));
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Integer &base) :
		m_power(power), m_base(base){
		assert(!(1 == m_base));
		Reduce();
	}
	Logarithm::Logarithm(const Integer &power, const Fraction &base) :
		m_power(power), m_base(base) {
		assert(!(1 == m_base));
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Integer &base) :
		m_power(power), m_base(base) {
		assert(!(1 == m_base));
		Reduce();
	}
	Logarithm::Logarithm(const Fraction &power, const Fraction &base) :
		m_power(power), m_base(base) {
		assert(!(1 == m_base));
		Reduce();
	}
	const std::string Logarithm::GetString(uint8_t radix) const {
		if (!IsFraction()) {
			return m_power.GetString(radix) + "#" + m_base.GetString(radix);
		}
		else {
			return m_reduction_coefficient.GetString(radix) + "{" + m_power.GetString(radix) + "#" + m_base.GetString(radix) + "}";
		}
	}
	bool Logarithm::EqualZero() const {
		return m_reduction_coefficient.EqualZero() || m_reduction_power.EqualOne();
	}
	bool Logarithm::EqualOne() const {
		return IsPositive() && m_reduction_coefficient.EqualOne() && m_reduction_power == m_base;
	}
	void Logarithm::SetUnSigned(bool isUnSigned) {
		m_power.SetUnSigned(isUnSigned);
		m_base.SetUnSigned(true);
	}
	bool Logarithm::IsPositive() const {
		return m_power.IsPositive() == m_base.IsPositive();
	}
	const std::string Logarithm::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		const Fraction &numerator = GetFraction(m_power.Numerator(), radix, decimalLength);
		const Fraction &denominator = GetFraction(m_power.Denominator(), radix, decimalLength);
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
	void Logarithm::Reduce() {
		
	}

	bool Logarithm::IsFraction() const {
		return EqualZero() || m_base.GetAbs().EqualOne() || m_reduction_power.GetAbs().EqualOne();
	}

	Fraction Logarithm::GetFraction(const Integer &power, uint8_t radix, size_t decimalLength)const {
		if (m_base.IsInteger()) {
			return Integer(power.Value().Logarithm(m_base.Numerator().Value()).first);
		}
		else {
			const Natural &numerator = m_base.Numerator().Value().Logarithm(power.Value()).first;
			const Natural &denominator = m_base.Denominator().Value().Logarithm(power.Value()).first;
			return Fraction(1, numerator - denominator);
		}
	}

	void Logarithm::Opposite() {
		m_power.Opposite();
	}
}