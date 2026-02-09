#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "Infinity.h"

#include "Infinitesimal.h"

namespace inf {

	number::Fraction Infinitesimal::ignore_line = number::Integer(1);

	Infinitesimal::Infinitesimal(const number::Fraction &degree) :
		RatioInf(INFINITESIMAL_NAME) {
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
		if (IsLock()) {
			return false;
		}
		if (Multiple(exp)) {
			return true;
		}
		if (Transform(exp)) {
			return true;
		}
		return false;
	}
	bool Infinitesimal::ExtendPowerRoot(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {
		if (IsLock()) {
			return false;
		}
		if (Multiple(exp)) {
			return true;
		}
		if (Transform(exp)) {
			return true;
		}
		return false;
	}
	std::shared_ptr<expression::Symbol> Infinitesimal::GetClone() const {
		return std::make_shared<Infinitesimal>(*this);
	}
	const Infinitesimal& Infinitesimal::operator=(const Infinitesimal& right) {
		m_degree = right.m_degree;
		return *this;
	}
	bool Infinitesimal::operator==(const Infinitesimal& other) const {
		return m_degree == other.m_degree;
	}

	Infinitesimal Infinitesimal::operator+(const Infinitesimal &addition) const {
		if (Degree().EqualZero()) {
			return addition;
		}
		else if (addition.Degree().EqualZero()) {
			return *this;
		}
		else {
			Infinitesimal sum;
			sum.SetDegree((Degree().GetReciprocal() + addition.Degree().GetReciprocal()).GetReciprocal());
			return sum;
		}

	}
	Infinitesimal &Infinitesimal::operator+=(const Infinitesimal &addition) {
		*this = *this + addition;
		return *this;
	}
	Infinitesimal Infinitesimal::operator-(const Infinitesimal &subtrahend) const {
		if (Degree().EqualZero()) {
			Infinitesimal negative(subtrahend);
			negative.m_degree.Opposite();
			return negative;
		}
		else if (subtrahend.Degree().EqualZero()) {
			Infinitesimal negative(*this);
			negative.m_degree.Opposite();
			return negative;
		}
		else {
			Infinitesimal difference(number::Integer(0));

			if (Degree() != subtrahend.Degree()) {
				difference.SetDegree((Degree().GetReciprocal() - subtrahend.Degree().GetReciprocal()).GetReciprocal());
			}
			
			return difference;
		}
	}
	Infinitesimal &Infinitesimal::operator-=(const Infinitesimal &subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	number::Fraction Infinitesimal::operator/(const Infinitesimal &divisor) const {
		if (Degree().EqualZero() || divisor.Degree().EqualZero()) {
			return number::Integer(0);
		}
		return Degree().GetReciprocal() / divisor.Degree().GetReciprocal();
	}
	Infinitesimal Infinitesimal::operator*(const number::Fraction &multiplier) const {
		Infinitesimal product(number::Integer(0));

		if (!Degree().EqualZero() && !multiplier.EqualZero()) {
			product.SetDegree(Degree() * multiplier.GetReciprocal());
		}
		
		return product;
	}
	Infinitesimal Infinitesimal::operator/(const number::Fraction &divisor) const {
		Infinitesimal quotient(number::Integer(0));

		if (!Degree().EqualZero() && !divisor.EqualZero()) {
			quotient.SetDegree(Degree() / divisor.GetReciprocal());
		}

		return quotient;
	}
	const Infinitesimal &Infinitesimal::SetDegree(const number::Fraction &degree) {
		m_degree = degree;
		if (m_degree.GetAbs() >= ignore_line.GetAbs()) {
			SetSubstitution(expression::ClosureNumber(0));
		}
		else {
			SetSubstitution();
		}
		return *this;
	}
	void Infinitesimal::SetIgnoreLine(const number::Fraction& ignore) {
		ignore_line = ignore;
	}
	bool Infinitesimal::Transform(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		const std::optional<expression::ExpressionNodes::iterator> infItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITESIMAL_NAME == node.Name(); });
		if (!infItor) {
			return false;
		}

		expression::SymbolWrapper& symbol = std::get<expression::SymbolWrapper>(*infItor.value());

		if (symbol.IsDiv()) {
			Infinitesimal& infinitesimal = dynamic_cast<Infinitesimal&>(symbol.Inner());
			expression::SymbolWrapper infinity(std::make_shared<inf::Infinity>(infinitesimal.Degree()));
			infinity.SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
			exp.AppendNode(infinity);
			exp.RemoveNode(infItor.value());
			return true;
		}

		return false;
	}
	bool Infinitesimal::Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& symbol) {return symbol.Name() == INFINITESIMAL_NAME; });
		if (symbols.empty()) {
			return false;
		}
		
		bool allUnit = true;

		number::Fraction coefficient(1);
		
		for (auto symbol : symbols) {
			const expression::SymbolWrapper& wrapper = std::get<expression::SymbolWrapper>(*symbol);
			expression::Symbol& inner = wrapper.Inner();
			
			Infinitesimal& inf = dynamic_cast<Infinitesimal&>(inner);

			if (inf.IsUnit()) {
				continue;
			}

			allUnit = false;

			const number::Fraction& degree = inf.Degree();
			
			if (wrapper.IsDiv()) {
				coefficient /= degree.GetReciprocal();
			}
			else {
				coefficient *= degree.GetReciprocal();
			}

			inf.SetDegree(number::Integer(1));
		}
		if (allUnit) {
			return false;
		}
		auto coefficientChild = expression::Expression<expression::OPERATOR_TYPE_ADD_SUB>::Absorb(coefficient);
		coefficientChild.SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
		exp.AppendChild(coefficientChild);
		return true;
	}
	bool Infinitesimal::Transform(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {

		const std::optional<expression::ExpressionNodes::iterator> infItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITESIMAL_NAME == node.Name(); });
		if (!infItor) {
			return false;
		}

		expression::SymbolWrapper& symbol = std::get<expression::SymbolWrapper>(*infItor.value());

		if (symbol.IsRoot()) {
			Infinitesimal& infinitesimal = dynamic_cast<Infinitesimal&>(symbol.Inner());
			expression::SymbolWrapper infinity(std::make_shared<inf::Infinity>(infinitesimal.Degree()));
			infinity.SetOperator(expression::OPERATOR_TYPE_FLAG_POWER);
			exp.AppendNode(infinity);
			exp.RemoveNode(infItor.value());
			expression::Polymorphism::Visit(exp.Front())->SetOperator(expression::OPERATOR_TYPE_FLAG_NONE);
			return true;
		}

		return false;
	}
	bool Infinitesimal::Multiple(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& symbol) {return symbol.Name() == INFINITESIMAL_NAME; });
		if (symbols.empty()) {
			return false;
		}
		bool allUnit = true;
		number::Fraction exponent(1);
		for (auto symbol : symbols) {
			const expression::SymbolWrapper& wrapper = std::get<expression::SymbolWrapper>(*symbol);
			expression::Symbol& inner = wrapper.Inner();
			if (wrapper.IsNone()) {
				continue;
			}
			Infinitesimal& inf = dynamic_cast<Infinitesimal&>(inner);
			if (inf.IsUnit()) {
				continue;
			}
			allUnit = false;
			const number::Fraction& degree = inf.Degree();
			if (wrapper.IsRoot()) {
				exponent /= degree.GetReciprocal();
			}
			else {
				exponent *= degree.GetReciprocal();
			}

			inf.SetDegree(number::Integer(1));
		}
		if (allUnit) {
			return false;
		}
		auto exponentChild = expression::Expression<expression::OPERATOR_TYPE_ADD_SUB>::Absorb(exponent);
		exponentChild.SetOperator(expression::OPERATOR_TYPE_FLAG_POWER);
		exp.AppendChild(exponentChild);
		return true;
	}
}