#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Root.h"

#include "performance/fraction/root/Dissection.h"

namespace number {
	Root::Root():m_power(0), m_exponent(1),
		m_reduction_power(m_power), m_reduction_exponent(m_exponent) {
		DomainVerification();
		SetPositive(true);
		Reduce();
	}
	Root::Root(const Integer &power, const Integer &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent),
		m_reduction_power(m_power), m_reduction_exponent(m_exponent) {
		DomainVerification();
		SetPositive(isUnSigned);
		Reduce();
	}
	Root::Root(const Integer &power, const Fraction &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent),
		m_reduction_power(m_power), m_reduction_exponent(m_exponent) {
		DomainVerification();
		SetPositive(isUnSigned);
		Reduce();
	}
	Root::Root(const Fraction &power, const Integer &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent),
		m_reduction_power(m_power), m_reduction_exponent(m_exponent) {
		DomainVerification();
		SetPositive(isUnSigned);
		Reduce();
	}
	Root::Root(const Fraction &power, const Fraction &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent),
		m_reduction_power(m_power), m_reduction_exponent(m_exponent) {
		DomainVerification();
		SetPositive(isUnSigned);
		Reduce();
	}

	const std::string Root::GetString(uint8_t radix) const {
		if (!IsFraction()) {
			return m_reduction_power.GetString(radix) + "@" + m_reduction_exponent.GetString(radix);
		}
		else {
			return m_reduction_coefficient.GetString(radix) + "{" + m_reduction_power.GetString(radix) + "@" + m_reduction_exponent.GetString(radix) + "}";
		}
	}
	bool Root::EqualZero() const {
		return m_reduction_coefficient.EqualZero() || m_reduction_power.EqualZero();
	}
	bool Root::EqualPositiveOne() const {
		return (IsPositive() && ValueEqualPositiveOne()) ||
			(!IsPositive() && ValueEqualNegativeOne());
	}
	bool Root::EqualNegativeOne() const {
		return (IsPositive() && ValueEqualNegativeOne()) ||
			(!IsPositive() && ValueEqualPositiveOne());
	}

	const std::string Root::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		const number::Fraction &fraction = 
			performance::fraction::root::Dissection(m_power, m_exponent, decimalLength).GetResult() *
			number::Fraction(number::Integer(1, IsPositive()));
		std::string sign;
		if (!m_power.Numerator().IsOdd()) {
			sign = "(+/-)";
		}
		if (!IsImaginary()) {
			return sign + fraction.GetDecimal(radix, decimalLength, round);
		}
		else {
			return sign + Imaginary(fraction).GetDecimal(radix, decimalLength, round);
		}
	}
	Root Root::operator-() const {
		Root opposite(*this);
		opposite.Opposite();
		return opposite;
	}
	bool Root::operator==(const Root &other) const {
		return IsPositive() == other.IsPositive() &&
			m_reduction_power == other.m_reduction_power &&
			m_reduction_exponent == other.m_reduction_exponent &&
			m_reduction_coefficient == other.m_reduction_coefficient;
	}
	const Fraction &Root::Power()const {
		return m_power;
	}
	const Fraction &Root::Exponent()const {
		return m_exponent;
	}
	const Fraction &Root::ReductionCoefficient()const {
		return m_reduction_coefficient;
	}
	const Fraction &Root::ReductionPower()const {
		return m_reduction_power;
	}
	const Fraction &Root::ReductionExponent()const {
		return m_reduction_exponent;
	}
	void Root::Reduce() {
		if (!m_power.EqualZero()) {
			ReduceExponent();
			ReducePower();
		}
	}
	void Root::ReduceExponent() {
		if (m_exponent.IsInteger()) {
			Natural exponent = m_exponent.Numerator();
			const std::list<Natural> &factors = exponent.GetFactors();
			for (auto factor = factors.crbegin(); factor != factors.crend(); factor++) {
				if (*factor != Natural(1) && *factor != exponent) {
					const std::pair<Natural, Natural> &numeratorResult =
						m_power.Numerator().Root(*factor);
					const std::pair<Natural, Natural> &denominatorResult =
						m_power.Denominator().Root(*factor);
					if (numeratorResult.second.EqualZero() && denominatorResult.second.EqualZero()) {
						m_reduction_power = Fraction(numeratorResult.first, denominatorResult.first);
						m_reduction_exponent = m_exponent / *factor;
						break;
					}
				}
			}
		}
	}
	void Root::ReducePower() {
		const Natural &powerNumerator = m_power.Numerator().Power(m_exponent.Denominator());
		const std::pair<Natural, Natural> &numeratorResult = powerNumerator.Root(m_exponent.Numerator());

		const Natural &powerDenominator = m_power.Denominator().Power(m_exponent.Denominator());
		const std::pair<Natural, Natural> &denominatorResult = powerDenominator.Root(m_exponent.Numerator());

		if (numeratorResult.second.EqualZero() && denominatorResult.second.EqualZero()) {
			m_reduction_coefficient = Fraction(numeratorResult.first, denominatorResult.first);

			const Fraction baseNumerator(Integer(powerNumerator, m_power.Numerator().IsPositive()), powerNumerator);
			const Fraction baseDenominator(Integer(powerDenominator, m_power.Denominator().IsPositive()), powerDenominator);

			m_reduction_power = Fraction(baseNumerator, baseDenominator);
		}
		else {
			const std::pair<Natural, Natural> &numeratorCoefficient = CalcuCoefficient(numeratorResult.first, powerNumerator);
			const std::pair<Natural, Natural> &denominatorCoefficient = CalcuCoefficient(denominatorResult.first, powerDenominator);

			if (!numeratorCoefficient.first.EqualPositiveOne() || !denominatorCoefficient.first.EqualPositiveOne()) {
				m_reduction_coefficient = Fraction(numeratorCoefficient.first, denominatorCoefficient.first);
				m_reduction_power = Fraction(numeratorCoefficient.second, denominatorCoefficient.second);
			}
		}
	}
	std::pair<Natural, Natural> Root::CalcuCoefficient(const Natural &maxRoot, const Natural &power) const {
		Natural coefficient(1);
		Natural base(1);
		for (Natural root(maxRoot); root >= Natural(2); --root) {
			std::pair<Natural, Natural> result(power.Div(root.Power(m_exponent.Numerator())));
			if (result.second.EqualZero()) {
				coefficient = root;
				base = result.first;
				break;
			}
		}
		return std::make_pair(coefficient, base);
	}

	bool Root::IsFraction() const {
		return EqualZero() || m_exponent.GetAbs().EqualPositiveOne() || m_reduction_power.GetAbs().EqualPositiveOne();
	}

	bool Root::IsImaginary() const {
		return !m_power.IsPositive() &&
			m_exponent.Denominator().IsOdd() &&
			!m_exponent.Numerator().IsOdd();
	}

	Root Root::AddEqual(const number::Root &right) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!IsPositive()) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.IsPositive()) {
			rightCoefficient = -right.ReductionCoefficient();
		}
		const number::Fraction &coefficient = leftCoefficient + rightCoefficient;

		const Natural &powerNumerator = coefficient.Numerator().Power(Exponent().Numerator());
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator()).first;

		const Natural &powerDenominator = coefficient.Denominator().Power(Exponent().Numerator());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator()).first;

		return Root(ReductionPower()*(rootNumerator / rootDenominator), Exponent(), coefficient.IsPositive());
	}

	Root Root::MulEqual(const number::Root &right, bool isLeftMul, bool isRightMul) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!IsPositive()) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.IsPositive()) {
			rightCoefficient = -right.ReductionCoefficient();
		}
		number::Fraction leftExponent = Exponent();
		if (!isLeftMul) {
			leftExponent = -Exponent();
		}
		number::Fraction rightExponent = right.Exponent();
		if (!isLeftMul) {
			rightExponent = -right.Exponent();
		}
		number::Fraction exponent = leftExponent.GetReciprocal() + rightExponent.GetReciprocal();

		const number::Fraction &coefficient = leftCoefficient * rightCoefficient;

		if (exponent.EqualZero()) {
			return Root(coefficient, 1);
		}

		const Natural &powerNumerator = coefficient.Numerator().Power(Exponent().Numerator());
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator()).first;

		const Natural &powerDenominator = coefficient.Denominator().Power(Exponent().Numerator());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator()).first;

		return Root(ReductionPower()*(rootNumerator / rootDenominator), exponent.GetReciprocal(), coefficient.IsPositive());
	}
	Root Power(const Fraction &base, const Fraction &exponent) {
		return Root(base, exponent.GetReciprocal());
	}
	std::optional<Root> Root::CheckReduce(const Fraction &power, const Fraction &exponent) {
		const number::Root reduce(power, exponent);
		if (reduce.ReductionPower() == power &&
			reduce.ReductionCoefficient().EqualPositiveOne()) {
			return std::nullopt;
		}
		else {
			return reduce;
		}
	}
	void Root::ExponentDomainVerification(const Fraction & exponent) {
		if (exponent.EqualZero()) {
			throw std::exception("Domain Undefined : Root Exponent Can not 0");
		}
	}
	bool Root::ValueEqualPositiveOne() const {
		return m_reduction_coefficient.EqualPositiveOne() &&
			m_reduction_power.EqualPositiveOne() &&
			m_reduction_exponent.EqualPositiveOne();
	}
	bool Root::ValueEqualNegativeOne() const {
		return m_reduction_coefficient.EqualNegativeOne() &&
			m_reduction_power.EqualPositiveOne() &&
			m_reduction_exponent.EqualPositiveOne();
	}
	void Root::DomainVerification() const {
		ExponentDomainVerification(m_exponent);
	}
}