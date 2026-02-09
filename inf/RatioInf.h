#ifndef __INF_RATIO_INF_H__
#define __INF_RATIO_INF_H__

#include "expression/Symbol.h"

#include "number/Fraction.h"

namespace inf {
	class RatioInf : public expression::Symbol {
	public:
		RatioInf(const std::string &name, const number::Fraction& degree = number::Integer(1));
		
		bool operator==(const RatioInf& other) const;

		bool IsPositive() const;
		bool IsNegative() const;
		bool IsZero() const;

		bool IsUnit() const;

		bool IsLeft() const;
		bool IsRight() const;

		const number::Fraction &Degree() const;

	protected:
		number::Fraction m_degree = number::Integer(1);
	
	};
}

#endif