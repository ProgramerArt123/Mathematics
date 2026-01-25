#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "Infinity.h"

#include "Infinitesimal.h"

namespace inf {

	number::Fraction Infinitesimal::ignore_line = number::Integer(1);

	Infinitesimal::Infinitesimal(const std::string& name, const number::Fraction &degree) :
		RatioInf(name) {
		SetDegree(degree);
	}
	const std::string Infinitesimal::GetString(uint8_t radix) const {
		if (IsZero()) {
			return "0";
		}
		else if (Degree().IsPositive()) {
			return Symbol::GetString(radix) + "[" + "<-:" + Degree().GetAbs().GetString(radix) + "]";
		}
		else {
			return Symbol::GetString(radix) + "[" + Degree().GetAbs().GetString(radix) + ":->" + "]";
		}
	}
	bool Infinitesimal::IsEqual(const Symbol &other) const {
		if (!RatioInf::IsEqual(other)) {
			return false;
		}
		if (typeid(other) != typeid(Infinitesimal)) {
			return false;
		}
		const Infinitesimal& otherInfinitesimal = dynamic_cast<const Infinitesimal&>(other);
		return *this == otherInfinitesimal;
	}
	bool Infinitesimal::ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> &exp) {
		if (Multiple(exp)) {
			return true;
		}
		return false;
	}
	std::shared_ptr<expression::Symbol> Infinitesimal::GetClone() const {
		return std::make_shared<Infinitesimal>(*this);
	}
	bool Infinitesimal::operator==(const Infinitesimal& other) const {
		return m_degree == other.m_degree;
	}

	Infinitesimal Infinitesimal::operator+(const Infinitesimal &addition) const {
		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction additionDegree = addition.IsUnSigned() ? addition.Degree() : -addition.Degree();
		if (signDegree.EqualZero()) {
			return addition;
		}
		else if (additionDegree.EqualZero()) {
			return *this;
		}
		else {
			Infinitesimal sum(Name());
			sum.SetDegree((signDegree.GetReciprocal() + additionDegree.GetReciprocal()).GetReciprocal());
			return sum;
		}

	}
	Infinitesimal &Infinitesimal::operator+=(const Infinitesimal &addition) {
		*this = *this + addition;
		return *this;
	}
	Infinitesimal Infinitesimal::operator-(const Infinitesimal &subtrahend) const {
		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction subtrahendDegree = subtrahend.IsUnSigned() ? subtrahend.Degree() : -subtrahend.Degree();
		if (signDegree.EqualZero()) {
			Infinitesimal negative(subtrahend);
			negative.m_degree.Opposite();
			return negative;
		}
		else if (subtrahendDegree.EqualZero()) {
			Infinitesimal negative(*this);
			negative.m_degree.Opposite();
			return negative;
		}
		else {
			Infinitesimal difference(Name(), number::Integer(0));

			if (signDegree != subtrahendDegree) {
				difference.SetDegree((signDegree.GetReciprocal() - subtrahendDegree.GetReciprocal()).GetReciprocal());
			}
			
			return difference;
		}
	}
	Infinitesimal &Infinitesimal::operator-=(const Infinitesimal &subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	number::Fraction Infinitesimal::operator/(const Infinitesimal &divisor) const {
		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction divisorDegree = divisor.IsUnSigned() ? divisor.Degree() : -divisor.Degree();
		if (signDegree.EqualZero() || divisorDegree.EqualZero()) {
			return number::Integer(0);
		}
		return signDegree.GetReciprocal() / divisorDegree.GetReciprocal();
	}
	Infinitesimal Infinitesimal::operator*(const number::Fraction &multiplier) const {
		Infinitesimal product(Name(), number::Integer(0));

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		
		if (!signDegree.EqualZero() && !multiplier.EqualZero()) {
			product.SetDegree(signDegree * multiplier.GetReciprocal());
		}
		
		return product;
	}
	Infinitesimal Infinitesimal::operator/(const number::Fraction &divisor) const {
		Infinitesimal quotient(Name(), number::Integer(0));

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		
		if (!signDegree.EqualZero() && !divisor.EqualZero()) {
			quotient.SetDegree(signDegree / divisor.GetReciprocal());
		}

		return quotient;
	}
	const Infinitesimal &Infinitesimal::SetDegree(const number::Fraction &degree) {
		m_degree = Transform(degree);
		if (m_degree.GetAbs() >= ignore_line.GetAbs()) {
			SetSubstitution(expression::ClosureNumber(0));
		}
		else {
			SetSubstitution();
		}
		return *this;
	}
	void Infinitesimal::SetIgnoreLine(const number::Fraction& ignore) {
		ignore_line = Transform(ignore);
	}
	bool Infinitesimal::Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>();
		if (symbols.empty()) {
			return false;
		}
		number::Fraction coefficient(1);
		for (auto symbol : symbols) {
			const expression::SymbolWrapper& otherWrapper = std::get<expression::SymbolWrapper>(*symbol);
			expression::Symbol& inner = otherWrapper.Inner();
			if (typeid(inner) != typeid(Infinitesimal)) {
				continue;
			}
			Infinitesimal& inf = dynamic_cast<Infinitesimal&>(inner);
			const number::Fraction& degree = inf.Degree();
			if (degree.EqualPositiveOne()) {
				continue;
			}
			if (otherWrapper.IsDiv()) {
				coefficient /= degree.GetReciprocal();
			}
			else {
				coefficient *= degree.GetReciprocal();
			}

			inf.SetDegree(number::Integer(1));
		}
		if (coefficient.EqualPositiveOne()) {
			return false;
		}
		auto coefficientChild = expression::Expression<expression::OPERATOR_TYPE_ADD_SUB>::Absorb(coefficient);
		coefficientChild.SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
		exp.AppendChild(coefficientChild);
		return true;
	}
}