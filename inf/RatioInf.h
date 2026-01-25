#ifndef __INF_RATIO_INF_H__
#define __INF_RATIO_INF_H__

#include "expression/Symbol.h"

#include "number/Fraction.h"

namespace inf {
	class RatioInf : public expression::Symbol {
	public:
		RatioInf(const std::string &name, const number::Fraction& degree = number::Integer(1));
		
		size_t AddSubSigned(expression::SymbolWrapper& wrapper) override;
		size_t MulDivSigned(expression::SymbolWrapper& wrapper) override;

		void Opposite(expression::SymbolWrapper& wrapper) override;

		bool operator==(const RatioInf&other) const;

		bool IsPositive() const;
		bool IsNegative() const;
		bool IsZero() const;

		bool IsLeft() const;
		bool IsRight() const;

		const number::Fraction &Degree() const;

	protected:

		static number::Fraction Transform(const number::Fraction &degree);

	protected:
		number::Fraction m_degree = number::Integer(1);
	
	};
}

#endif