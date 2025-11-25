#ifndef __NUMBER_ROOT_H__
#define __NUMBER_ROOT_H__

#include <optional>

#include "Real.h"
#include "Integer.h"
#include "Fraction.h"

namespace number {
	class Complex;

	class Root : public Real{
	public:
		Root();
		Root(const Integer &power, const Integer &exponent, bool isUnSigned = true);
		Root(const Integer &power, const Fraction &exponent, bool isUnSigned = true);
		Root(const Fraction &power, const Integer &exponent, bool isUnSigned = true);
		Root(const Fraction &power, const Fraction &exponent, bool isUnSigned = true);

		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;

		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		Root operator-() const;
		bool operator==(const Root &other) const;

		const Fraction &Power()const;
		const Fraction &Exponent()const;
		const Fraction &ReductionCoefficient()const;
		const Fraction &ReductionPower()const;
		const Fraction &ReductionExponent()const;

		bool IsFraction() const;
		bool IsImaginary() const;

		Root AddEqual(const number::Root &right) const;
		Root MulEqual(const number::Root &right, bool isLeftMul, bool isRightMul) const;

		friend Root Power(const Fraction &base, const Fraction &exponent);
		static std::optional<Root> CheckReduce(const Fraction &power, const Fraction &exponent);

		static void ExponentDomainVerification(const Fraction& exponent);
	private:

		Fraction m_power;
		Fraction m_exponent;

		Fraction m_reduction_power = Integer(0);
		Fraction m_reduction_exponent = Integer(1);
		Fraction m_reduction_coefficient = Integer(1);

		void Reduce();
		void ReduceExponent();
		void ReducePower();

		bool ValueEqualPositiveOne() const;
		bool ValueEqualNegativeOne() const;

		void DomainVerification() const;

		std::pair<Natural, Natural> CalcuCoefficient(const Natural &maxRoot, const Natural &power) const;
	};
}
#endif