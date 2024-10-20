#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Root.h"
namespace number {
	Root::Root():m_power(0), m_exponent(1), m_unsigned(true) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Integer &power, const Integer &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent), m_unsigned(isUnSigned) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Integer &power, const Fraction &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent), m_unsigned(isUnSigned) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Fraction &power, const Integer &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent), m_unsigned(isUnSigned) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Fraction &power, const Fraction &exponent, bool isUnSigned) :
		m_power(power), m_exponent(exponent), m_unsigned(isUnSigned) {
		assert(!(0 == m_exponent));
		Reduce();
	}

	const std::string Root::GetString(uint8_t radix) const {
		if (!IsFraction()) {
			return m_power.GetString(radix) + "@" + m_exponent.GetString(radix);
		}
		else {
			return m_reduction_coefficient.GetString(radix) + "{" + m_power.GetString(radix) + "@" + m_exponent.GetString(radix) + "}";
		}
	}
	bool Root::EqualZero() const {
		return m_power.EqualZero();
	}
	bool Root::EqualOne() const {
		return m_power.EqualOne();
	}
	void Root::SetUnSigned(bool isUnSigned) {
		m_unsigned = isUnSigned;
	}
	bool Root::IsPositive() const {
		return m_unsigned == !(!m_power.IsPositive() &&
			m_exponent.Denominator().Value().IsOdd() &&
			m_exponent.Numerator().Value().IsOdd());
	}
	void Root::Opposite() {
		if (!EqualZero()) {
			m_unsigned = !m_unsigned;
		}
	}
	const std::string Root::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		const Fraction &numerator = GetFraction(m_power.Numerator(), radix, decimalLength) * Fraction(Integer(1, IsPositive()));
		const Fraction &denominator = GetFraction(m_power.Denominator(), radix, decimalLength);
		const Fraction fraction(numerator, denominator);
		std::string sign;
		if (!m_power.Numerator().Value().IsOdd()) {
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
		return m_unsigned == other.m_unsigned &&
			m_reduction_power == other.m_reduction_power &&
			m_reduction_coefficient == other.m_reduction_coefficient &&
			m_exponent == other.m_exponent;
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
	void Root::Reduce() {
		if (!EqualZero()) {
			ReduceExponent();
			ReduceCoefficient();
		}
		else {
			m_reduction_power = Fraction(0);
			m_reduction_coefficient = Fraction(1);
		}
	}
	void Root::ReduceExponent() {
		if (m_exponent.IsInteger()) {
			Natural exponent = m_exponent.Numerator().Value();
			const std::list<Natural> &factors = exponent.GetFactors();
			for (auto factor = factors.crbegin(); factor != factors.crend(); factor++) {
				if (*factor != Natural(1) && *factor != exponent) {
					const std::pair<Natural, Natural> &numeratorResult =
						m_power.Numerator().Value().Root(*factor);
					const std::pair<Natural, Natural> &denominatorResult =
						m_power.Denominator().Value().Root(*factor);
					if (numeratorResult.second.EqualZero() && denominatorResult.second.EqualZero()) {
						m_power = Fraction(numeratorResult.first, denominatorResult.first);
						m_exponent = m_exponent / *factor;
						break;
					}
				}
			}
		}
	}
	void Root::ReduceCoefficient() {
		const Natural &powerNumerator = m_power.Numerator().Value().Power(m_exponent.Denominator().Value());
		const std::pair<Natural, Natural> &numeratorResult = powerNumerator.Root(m_exponent.Numerator().Value());

		const Natural &powerDenominator = m_power.Denominator().Value().Power(m_exponent.Denominator().Value());
		const std::pair<Natural, Natural> &denominatorResult = powerDenominator.Root(m_exponent.Numerator().Value());

		if (numeratorResult.second.EqualZero() && denominatorResult.second.EqualZero()) {
			m_reduction_coefficient = Fraction(numeratorResult.first, denominatorResult.first);

			const Fraction baseNumerator(Integer(powerNumerator, m_power.Numerator().IsPositive()), powerNumerator);
			const Fraction baseDenominator(Integer(powerDenominator, m_power.Denominator().IsPositive()), powerDenominator);

			m_reduction_power = Fraction(baseNumerator, baseDenominator);
		}
		else {
			const std::pair<Natural, Natural> &numeratorCoefficient = CalcuCoefficient(numeratorResult.first, powerNumerator);
			const std::pair<Natural, Natural> &denominatorCoefficient = CalcuCoefficient(denominatorResult.first, powerDenominator);

			if (!numeratorCoefficient.first.EqualOne() || !denominatorCoefficient.first.EqualOne()) {
				m_reduction_coefficient = Fraction(numeratorCoefficient.first, denominatorCoefficient.first);
				m_reduction_power = Fraction(numeratorCoefficient.second, denominatorCoefficient.second);
			}
			else {
				m_reduction_coefficient = Fraction(1);
				m_reduction_power = m_power;
			}
		}
	}
	std::pair<Natural, Natural> Root::CalcuCoefficient(const Natural &maxRoot, const Natural &power) const {
		Natural coefficient(1);
		Natural base(1);
		for (Natural root(maxRoot); root >= Natural(2); --root) {
			std::pair<Natural, Natural> result(power.Div(root.Power(m_exponent.Numerator().Value())));
			if (result.second.EqualZero()) {
				coefficient = root;
				base = result.first;
				break;
			}
		}
		return std::make_pair(coefficient, base);
	}

	bool Root::IsFraction() const {
		return EqualZero() || m_exponent.GetAbs().EqualOne() || m_reduction_power.GetAbs().EqualOne();
	}

	bool Root::IsImaginary() const {
		return !m_power.IsPositive() &&
			m_exponent.Denominator().Value().IsOdd() &&
			!m_exponent.Numerator().Value().IsOdd();
	}

	Fraction Root::GetFraction(const Integer &base, uint8_t radix, size_t decimalLength)const {
		std::string powerStr = base.Value().Power(m_exponent.Denominator().Value()).GetString(radix);
		for (Natural index(1); index <= m_exponent.Numerator().Value(); ++index) {
			powerStr.append(decimalLength + 1, '0');
		}
		const std::pair<Natural, Natural> &result = Natural(powerStr, radix).Root(m_exponent.Numerator().Value());
		if (m_exponent.IsPositive()) {
			std::string rootStr = result.first.GetString(radix);
			if (rootStr.length() < decimalLength + 2) {
				rootStr.insert(0, decimalLength + 2 - rootStr.length(), '0');
			}
			std::string denominator = "1";
			denominator.append(decimalLength + 1, '0');
			const Fraction &fraction = Fraction(Natural(rootStr, radix)) /
				Fraction(Natural(denominator, radix));
			return fraction;
		}
		else {
			std::string numerator = "1";
			numerator.insert(numerator.length(), decimalLength + 1, '0');
			const Fraction &fraction = Fraction(Natural(numerator, radix), result.first);
			return fraction;
		}
	}

	bool Root::EqualPower0(const Root &right) const {
		if (EqualPower1(right) && m_exponent == right.m_exponent) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Root::EqualPower1(const Root &right) const{
		if (m_reduction_power == right.m_reduction_power) {
			return true;
		}
		else {
			return false;
		}
	}
	
	Root Root::AddEqual(const number::Root &right) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!m_unsigned) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.m_unsigned) {
			rightCoefficient = -right.ReductionCoefficient();
		}
		const number::Fraction &coefficient = leftCoefficient + rightCoefficient;

		const Natural &powerNumerator = coefficient.Numerator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator().Value()).first;

		const Natural &powerDenominator = coefficient.Denominator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator().Value()).first;

		return Root(ReductionPower()*(rootNumerator / rootDenominator), Exponent(), coefficient.IsPositive());
	}

	Root Root::MulEqual(const number::Root &right, bool isLeftMul, bool isRightMul) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!m_unsigned) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.m_unsigned) {
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

		const Natural &powerNumerator = coefficient.Numerator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator().Value()).first;

		const Natural &powerDenominator = coefficient.Denominator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator().Value()).first;

		return Root(ReductionPower()*(rootNumerator / rootDenominator), exponent.GetReciprocal(), coefficient.IsPositive());
	}
	Root Power(const Fraction &base, const Fraction &exponent) {
		return Root(base, exponent.GetReciprocal());
	}
	bool Root::CheckReduce(const Fraction &power, const Fraction &exponent) {
		const number::Root reduce(power, exponent);
		return reduce.ReductionPower() == power &&
			reduce.ReductionCoefficient().EqualOne();
	}
}