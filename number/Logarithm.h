#ifndef __NUMBER_LOGARITHM_H__
#define __NUMBER_LOGARITHM_H__

#include <optional>
#include <exception>

#include "Real.h"
#include "Integer.h"
#include "Fraction.h"

namespace number {
	class Complex;

	class Logarithm : public Real {
	public:
		Logarithm();
		Logarithm(const Integer &power, const Integer &base, bool isUnSigned = true);
		Logarithm(const Integer &power, const Fraction &base, bool isUnSigned = true);
		Logarithm(const Fraction &power, const Integer &base, bool isUnSigned = true);
		Logarithm(const Fraction &power, const Fraction &base, bool isUnSigned = true);

		const std::string GetString(uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;

		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		Logarithm operator-() const;
		bool operator==(const Logarithm &other) const;

		const Fraction &Power()const;
		const Fraction &Base()const;
		const Fraction &ReductionPower()const;
		const Fraction &ReductionBase()const;
		const Fraction &ReductionCoefficient()const;

		bool IsFraction() const;

		void Opposite();

		static std::optional<Logarithm> CheckReduce(const Fraction &power, const Fraction &base);

		static void PowerDomainVerification(const Fraction& power);

		static void BaseDomainVerification(const Fraction& base);

	private:

		Fraction m_power;
		Fraction m_base;

		Fraction m_reduction_power = Integer(1);
		Fraction m_reduction_base = Integer(2);
		Fraction m_reduction_coefficient = Integer(1);

		void Reduce();
		void ReduceBase();
		void ReducePower();
		void ReduceCoefficient();

		void DomainVerification() const;

		std::optional<Fraction> ReduceCoefficient(const Fraction &power, const Fraction &base) const;
	};
}
#endif