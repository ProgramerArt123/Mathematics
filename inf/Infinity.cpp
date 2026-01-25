#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "Infinitesimal.h"

#include "Infinity.h"

namespace inf {
	Infinity::Infinity(const std::string& name, const number::Fraction& degree) :
		RatioInf(name) {
		SetDegree(degree);
	}

	const std::string Infinity::GetString(uint8_t radix) const {
		if (IsZero()) {
			return "0";
		}
		else if (Degree().IsPositive()) {
			return Symbol::GetString(radix) + "[" + Degree().GetAbs().GetString(radix) + ":->" + "]";
		}
		else {
			return Symbol::GetString(radix) + "[" + "<-:" + Degree().GetAbs().GetString(radix) + "]";
		}
	}

	bool Infinity::IsEqual(const Symbol& other) const {
		if (!RatioInf::IsEqual(other)) {
			return false;
		}
		if (typeid(other) != typeid(Infinity)) {
			return false;
		}
		const Infinity& otherInfiniy = dynamic_cast<const Infinity&>(other);
		return *this == otherInfiniy;
	}

	bool Infinity::ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		if (Multiple(exp)) {
			return true;
		}
		if (Closure(exp)) {
			return true;
		}
		return false;
	}
	std::shared_ptr<expression::Symbol> Infinity::GetClone() const {
		return std::make_shared<Infinity>(*this);
	}
	bool Infinity::operator==(const Infinity& other) const {
		return m_degree == other.m_degree;
	}

	Infinity Infinity::operator+(const Infinity& addition) const {
		Infinity sum(Name());

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction additionDegree = addition.IsUnSigned() ? addition.Degree() : -addition.Degree();

		sum.SetDegree(signDegree + additionDegree);

		return sum;
	}
	Infinity& Infinity::operator+=(const Infinity& addition) {
		*this = *this + addition;
		return *this;
	}
	Infinity Infinity::operator-(const Infinity& subtrahend) const {
		Infinity difference(Name());

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction subtrahendDegree = subtrahend.IsUnSigned() ? subtrahend.Degree() : -subtrahend.Degree();

		difference.SetDegree(signDegree - subtrahendDegree);

		return difference;
	}
	Infinity& Infinity::operator-=(const Infinity& subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	number::Fraction Infinity::operator/(const Infinity& divisor) const {
		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();
		number::Fraction divisorDegree = divisor.IsUnSigned() ? divisor.Degree() : -divisor.Degree();
		return signDegree / divisorDegree;
	}
	Infinity Infinity::operator*(const number::Fraction& multiplier) const {
		Infinity product(Name());

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();

		product.SetDegree(signDegree * multiplier);

		return product;
	}
	Infinity Infinity::operator/(const number::Fraction& divisor) const {
		Infinity quotient(Name(), number::Integer(0));

		number::Fraction signDegree = IsUnSigned() ? Degree() : -Degree();

		if (!signDegree.EqualZero() && !divisor.EqualZero()) {
			quotient.SetDegree(signDegree / divisor);
		}
		
		return quotient;
	}
	const Infinity& Infinity::SetDegree(const number::Fraction& degree) {
		m_degree = degree;
		return *this;
	}
	bool Infinity::Closure(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		const std::optional<expression::ExpressionNodes::iterator> closureItor = exp.GetFirst<expression::ClosureNumber>();
		if (!closureItor) {
			return false;
		}

		const std::string& name = Name();
		const std::optional<expression::ExpressionNodes::iterator> infItor = exp.GetFirst<expression::SymbolWrapper>(
			[&name](const expression::SymbolWrapper& node) {return name == node.Name(); });
		if (!infItor) {
			return false;
		}

		expression::SymbolWrapper& symbol = std::get<expression::SymbolWrapper>(*infItor.value());
		const expression::ClosureNumber& closure = std::get<expression::ClosureNumber>(*closureItor.value());
		if (symbol.IsDiv()) {
			Infinity& inf = dynamic_cast<Infinity&>(symbol.Inner());
			exp.AddSymbol(expression::SymbolWrapper(std::make_shared<Infinitesimal>("o", inf.Degree())));
			exp.RemoveNode(infItor.value());
			exp.RemoveNode(closureItor.value());
			expression::Polymorphism::Visit(exp.Front())->SetOperator(expression::OPERATOR_TYPE_FLAG_NONE);
			return true;
		}

		return false;
	}
	bool Infinity::Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>();
		if (symbols.empty()) {
			return false;
		}
		number::Fraction coefficient(1);
		for (auto symbol : symbols) {
			const expression::SymbolWrapper& otherWrapper = std::get<expression::SymbolWrapper>(*symbol);
			expression::Symbol& inner = otherWrapper.Inner();
			if (typeid(inner) != typeid(Infinity)) {
				continue;
			}
			Infinity& inf = dynamic_cast<Infinity&>(inner);
			const number::Fraction& degree = inf.Degree();
			if (degree.EqualPositiveOne()) {
				continue;
			}
			if (otherWrapper.IsDiv()) {
				coefficient /= degree;
			}
			else {
				coefficient *= degree;
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