#include <cassert>

#include <iostream>
#include "Integer.h"
#include "Imaginary.h"
#include "Root.h"
namespace number {
	Root::Root():m_base(0), m_exponent(1), m_positive(true) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Integer &base, const Integer &exponent, bool positive) :
		m_base(base), m_exponent(exponent), m_positive(positive) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Integer &base, const Fraction &exponent, bool positive) :
		m_base(base), m_exponent(exponent), m_positive(positive) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Fraction &base, const Integer &exponent, bool positive) :
		m_base(base), m_exponent(exponent), m_positive(positive) {
		assert(!(0 == m_exponent));
		Reduce();
	}
	Root::Root(const Fraction &base, const Fraction &exponent, bool positive) :
		m_base(base), m_exponent(exponent), m_positive(positive) {
		assert(!(0 == m_exponent));
		Reduce();
	}

	const std::string Root::GetString(uint8_t radix) const {
		if (!IsFraction()) {
			return m_base.GetString(radix) + "@" + m_exponent.GetString(radix);
		}
		else {
			return m_reduction_coefficient.GetString(radix) + "{" + m_base.GetString(radix) + "@" + m_exponent.GetString(radix) + "}";
		}
	}
	void Root::SetRadix(uint8_t radix) {
		m_base.SetRadix(radix);
		m_exponent.SetRadix(radix);
	}
	uint8_t Root::GetRadix() const {
		return m_base.GetRadix();
	}
	bool Root::EqualZero() const {
		return m_base.EqualZero();
	}
	bool Root::EqualOne() const {
		return m_base.EqualOne();
	}
	void Root::SetPositive(bool isPositive) {
		m_positive = isPositive;
	}
	bool Root::IsPositive() const {
		return m_positive == !(!m_base.IsPositive() &&
			(m_exponent.Denominator().Value() % Natural(2, m_exponent.Denominator().GetRadix())).EqualOne() &&
			(m_exponent.Numerator().Value() % Natural(2, m_exponent.Denominator().GetRadix())).EqualOne());
	}

	const std::string Root::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		const Fraction &numerator = GetFraction(m_base.Numerator(), radix, decimalLength) * Fraction(Integer(1, IsPositive()));
		const Fraction &denominator = GetFraction(m_base.Denominator(), radix, decimalLength);
		const Fraction fraction(numerator, denominator);
		std::string sign;
		if ((m_base.Numerator().Value() % Natural(2)).EqualZero()) {
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
		opposite.m_positive = !opposite.m_positive;
		return opposite;
	}
	bool Root::operator==(const Root &other) const {
		return m_positive == other.m_positive &&
			m_reduction_base == other.m_reduction_base &&
			m_reduction_coefficient == other.m_reduction_coefficient &&
			m_exponent == other.m_exponent;
	}
	const Fraction &Root::Base()const {
		return m_base;
	}
	const Fraction &Root::Exponent()const {
		return m_exponent;
	}
	const Fraction &Root::ReductionCoefficient()const {
		return m_reduction_coefficient;
	}
	const Fraction &Root::ReductionBase()const {
		return m_reduction_base;
	}
	void Root::Reduce() {
		if (!EqualZero()) {
			const Natural &powerNumerator = m_base.Numerator().Value().Power(m_exponent.Denominator().Value());
			Natural rootNumeratorRemainder;
			const Natural &rootNumerator = powerNumerator.Root(m_exponent.Numerator().Value(), rootNumeratorRemainder);

			const Natural &powerDenominator = m_base.Denominator().Value().Power(m_exponent.Denominator().Value());
			Natural rootDenominatorRemainder;
			const Natural &rootDenominator = powerDenominator.Root(m_exponent.Numerator().Value(), rootDenominatorRemainder);

			if (rootNumeratorRemainder.EqualZero() && rootDenominatorRemainder.EqualZero()){
				m_reduction_coefficient = Fraction(rootNumerator, rootDenominator);

				const Fraction baseNumerator(Integer(powerNumerator, m_base.Numerator().IsPositive()), powerNumerator - rootNumeratorRemainder);
				const Fraction baseDenominator(Integer(powerDenominator, m_base.Denominator().IsPositive()), powerDenominator - rootDenominatorRemainder);
				m_reduction_base = Fraction(baseNumerator, baseDenominator);
			}
			else {
				Natural numeratorCoefficient(1);
				Natural numeratorBase(1);
				for (Natural root(rootNumerator); root >= Natural(2); -- root) {
					const Natural &power = root.Power(m_exponent.Numerator().Value());
					Natural quotient = 1;
					Natural remainder = 0;
					powerNumerator.Div(power, quotient, remainder);
					if (remainder.EqualZero()) {
						numeratorCoefficient = root;
						numeratorBase = quotient;
						break;
					}
				}

				Natural denominatorCoefficient(1);
				Natural denominatorBase(1);
				for (Natural root(rootDenominator); root >= Natural(2); -- root) {
					const Natural &power = root.Power(m_exponent.Numerator().Value());
					Natural quotient = 1;
					Natural remainder = 0;
					powerDenominator.Div(power, quotient, remainder);
					if (remainder.EqualZero()) {
						denominatorCoefficient = root;
						denominatorBase = quotient;
						break;
					}
				}
				
				if (!numeratorCoefficient.EqualOne() || !denominatorCoefficient.EqualOne()) {
					m_reduction_coefficient = Fraction(numeratorCoefficient, denominatorCoefficient);
					m_reduction_base = Fraction(numeratorBase, denominatorBase);
				}
				else {
					m_reduction_coefficient = Fraction(1);
					m_reduction_base = m_base;
				}
			}
		}
		else {
			m_reduction_base = Fraction(0);
			m_reduction_coefficient = Fraction(1);
		}
	}

	bool Root::IsFraction() const {
		return EqualZero() || m_exponent.GetAbs().EqualOne() || m_reduction_base.GetAbs().EqualOne();
	}

	bool Root::IsImaginary() const {
		return !m_base.IsPositive() &&
			(m_exponent.Denominator().Value() % Natural(2, m_exponent.Denominator().GetRadix())).EqualOne() &&
			(m_exponent.Numerator().Value() % Natural(2, m_exponent.Denominator().GetRadix())).EqualZero();
	}

	Fraction Root::GetFraction(const Integer &base, uint8_t radix, size_t decimalLength)const {
		std::string powerStr = base.Value().Power(m_exponent.Denominator().Value()).GetString(radix);
		for (Natural index(1, radix); index <= m_exponent.Numerator().Value(); ++index) {
			powerStr.append(decimalLength + 1, '0');
		}
		const Natural &root = Natural(powerStr, radix).Root(m_exponent.Numerator().Value());
		if (m_exponent.IsPositive()) {
			std::string rootStr = root.GetString(radix);
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
			const Fraction &fraction = Fraction(Natural(numerator, radix), root);
			return fraction;
		}
	}

	bool Root::EqualBase0(const Root &right) const {
		if (EqualBase1(right) && m_exponent == right.m_exponent) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Root::EqualBase1(const Root &right) const{
		if (m_reduction_base == right.m_reduction_base) {
			return true;
		}
		else {
			return false;
		}
	}
	
	Root Root::AddEqual(const number::Root &right) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!m_positive) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.m_positive) {
			rightCoefficient = -right.ReductionCoefficient();
		}
		const number::Fraction &coefficient = leftCoefficient + rightCoefficient;

		const Natural &powerNumerator = coefficient.Numerator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator().Value());

		const Natural &powerDenominator = coefficient.Denominator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator().Value());

		return Root(ReductionBase()*(rootNumerator / rootDenominator), Exponent(), coefficient.IsPositive());
	}

	Root Root::MulEqual(const number::Root &right, bool isLeftMul, bool isRightMul) const {
		number::Fraction leftCoefficient = ReductionCoefficient();
		if (!m_positive) {
			leftCoefficient = -ReductionCoefficient();
		}
		number::Fraction rightCoefficient = right.ReductionCoefficient();
		if (!right.m_positive) {
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
		const Natural &rootNumerator = powerNumerator.Root(Exponent().Denominator().Value());

		const Natural &powerDenominator = coefficient.Denominator().Value().Power(Exponent().Numerator().Value());
		const Natural &rootDenominator = powerDenominator.Root(Exponent().Denominator().Value());

		return Root(ReductionBase()*(rootNumerator / rootDenominator), exponent.GetReciprocal(), coefficient.IsPositive());
	}
	void Root::Opposite() {
		if (!EqualZero()) {
			m_positive = !m_positive;
		}
	}
	Root Power(const Fraction &base, const Fraction &exponent) {
		return Root(base, exponent.GetReciprocal());
	}
}