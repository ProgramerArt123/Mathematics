#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"
#include "expression/SymbolManager.h"

#include "Infinitesimal.h"

#include "Infinity.h"

namespace inf {
	Infinity::Infinity(const number::Fraction& degree) :
		RatioInf(INFINITY_NAME) {
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
		if (IsLock()) {
			return false;
		}
		if (Multiple(exp)) {
			return true;
		}
		if (Infinitesimal(exp)) {
			return true;
		}
		if (Transform(exp)) {
			return true;
		}
		return false;
	}
	bool Infinity::ExtendPowerRoot(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {
		if (IsLock()) {
			return false;
		}
		if (Multiple(exp)) {
			return true;
		}
		if (Infinitesimal(exp)) {
			return true;
		}
		if (Transform(exp)) {
			return true;
		}
		return false;
	}
	std::shared_ptr<expression::Symbol> Infinity::GetClone() const {
		return std::make_shared<Infinity>(*this);
	}
	const Infinity& Infinity::operator=(const Infinity& right) {
		m_degree == right.m_degree;
		return *this;
	}
	bool Infinity::operator==(const Infinity& other) const {
		return m_degree == other.m_degree;
	}

	Infinity Infinity::operator+(const Infinity& addition) const {
		Infinity sum;

		sum.SetDegree(Degree() + addition.Degree());

		return sum;
	}
	Infinity& Infinity::operator+=(const Infinity& addition) {
		*this = *this + addition;
		return *this;
	}
	Infinity Infinity::operator-(const Infinity& subtrahend) const {
		Infinity difference;

		difference.SetDegree(Degree() - subtrahend.Degree());

		return difference;
	}
	Infinity& Infinity::operator-=(const Infinity& subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	number::Fraction Infinity::operator/(const Infinity& divisor) const {
		return Degree() / divisor.Degree();
	}
	Infinity Infinity::operator*(const number::Fraction& multiplier) const {
		Infinity product;

		product.SetDegree(Degree() * multiplier);

		return product;
	}
	Infinity Infinity::operator/(const number::Fraction& divisor) const {
		Infinity quotient(number::Integer(0));

		if (!Degree().EqualZero() && !divisor.EqualZero()) {
			quotient.SetDegree(Degree() / divisor);
		}
		
		return quotient;
	}
	number::Fraction operator*(const Infinitesimal& multiplier, const Infinity& multiplicand) {
		if (multiplier.IsZero()) {
			return number::Integer(0);
		}
		return multiplier.Degree().GetReciprocal() * multiplicand.Degree();
	}
	number::Fraction operator*(const Infinity& multiplier, const Infinitesimal& multiplicand) {
		if (multiplicand.IsZero()) {
			return number::Integer(0);
		}
		return multiplier.Degree() * multiplicand.Degree().GetReciprocal();
	}
	const Infinity& Infinity::SetDegree(const number::Fraction& degree) {
		m_degree = degree;
		return *this;
	}
	bool Infinity::Transform(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {

		const std::optional<expression::ExpressionNodes::iterator> infItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITY_NAME == node.Name(); });
		if (!infItor) {
			return false;
		}

		expression::SymbolWrapper& symbol = std::get<expression::SymbolWrapper>(*infItor.value());

		if (symbol.IsDiv()) {
			Infinity& infinity = dynamic_cast<Infinity&>(symbol.Inner());
			expression::SymbolWrapper infinitesimal(std::make_shared<inf::Infinitesimal>(infinity.Degree()));
			infinitesimal.SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
			exp.AppendNode(infinitesimal);
			exp.RemoveNode(infItor.value());
			return true;
		}

		return false;
	}
	bool Infinity::Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& symbol) {return symbol.Name() == INFINITY_NAME; });
		if (symbols.empty()) {
			return false;
		}
		bool allUnit = true;

		number::Fraction coefficient(1);

		for (auto symbol : symbols) {
			const expression::SymbolWrapper& wrapper = std::get<expression::SymbolWrapper>(*symbol);
			expression::Symbol& inner = wrapper.Inner();

			Infinity& inf = dynamic_cast<Infinity&>(inner);

			if (inf.IsUnit()) {
				continue;
			}

			allUnit = false;

			const number::Fraction& degree = inf.Degree();
			
			if (wrapper.IsDiv()) {
				coefficient /= degree;
			}
			else {
				coefficient *= degree;
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
	bool Infinity::Infinitesimal(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) {

		const std::optional<expression::ExpressionNodes::iterator> infinityItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITY_NAME == node.Name(); });
		if (!infinityItor) {
			return false;
		}

		const std::optional<expression::ExpressionNodes::iterator> infinitesimalItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITESIMAL_NAME == node.Name(); });
		if (!infinitesimalItor) {
			return false;
		}

		expression::SymbolWrapper& symbolInfinity = std::get<expression::SymbolWrapper>(*infinityItor.value());

		expression::SymbolWrapper& symbolInfinitesimal = std::get<expression::SymbolWrapper>(*infinitesimalItor.value());

		if (!symbolInfinity.IsDiv() && !symbolInfinitesimal.IsDiv()) {
			Infinity& infinity = dynamic_cast<Infinity&>(symbolInfinity.Inner());
			inf::Infinitesimal& infinitesimal = dynamic_cast<inf::Infinitesimal&>(symbolInfinitesimal.Inner());
			number::Fraction product = infinity * infinitesimal;

			auto multiplierChild = expression::Expression<expression::OPERATOR_TYPE_ADD_SUB>::Absorb(product);
			multiplierChild.SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
			exp.AppendChild(multiplierChild);
			
			exp.RemoveNode(infinitesimalItor.value());
			exp.RemoveNode(infinityItor.value());

			return true;
		}

		return false;
	}
	bool Infinity::Transform(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {

		const std::optional<expression::ExpressionNodes::iterator> infItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITY_NAME == node.Name(); });
		if (!infItor) {
			return false;
		}

		expression::SymbolWrapper& symbol = std::get<expression::SymbolWrapper>(*infItor.value());

		if (symbol.IsRoot()) {
			Infinity& infinity = dynamic_cast<Infinity&>(symbol.Inner());
			expression::SymbolWrapper infinitesimal(std::make_shared<inf::Infinitesimal>(infinity.Degree()));
			infinitesimal.SetOperator(expression::OPERATOR_TYPE_FLAG_POWER);
			exp.AppendNode(infinitesimal);
			exp.RemoveNode(infItor.value());
			expression::Polymorphism::Visit(exp.Front())->SetOperator(expression::OPERATOR_TYPE_FLAG_NONE);
			return true;
		}

		return false;
	}
	bool Infinity::Multiple(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {
		const std::vector<expression::ExpressionNodes::iterator> symbols = exp.GetAll<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& symbol) {return symbol.Name() == INFINITY_NAME; });
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
			Infinity& inf = dynamic_cast<Infinity&>(inner);
			if (inf.IsUnit()) {
				continue;
			}
			allUnit = false;
			const number::Fraction& degree = inf.Degree();
			if (wrapper.IsRoot()) {
				exponent /= degree;
			}
			else {
				exponent *= degree;
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
	bool Infinity::Infinitesimal(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) {

		const std::optional<expression::ExpressionNodes::iterator> infinityItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITY_NAME == node.Name(); });
		if (!infinityItor) {
			return false;
		}

		const std::optional<expression::ExpressionNodes::iterator> infinitesimalItor = exp.GetFirst<expression::SymbolWrapper>(
			[](const expression::SymbolWrapper& node) {return INFINITESIMAL_NAME == node.Name(); });
		if (!infinitesimalItor) {
			return false;
		}

		expression::SymbolWrapper& symbolInfinity = std::get<expression::SymbolWrapper>(*infinityItor.value());

		expression::SymbolWrapper& symbolInfinitesimal = std::get<expression::SymbolWrapper>(*infinitesimalItor.value());

		if (!symbolInfinity.IsRoot() && !symbolInfinitesimal.IsRoot()) {
			Infinity& infinity = dynamic_cast<Infinity&>(symbolInfinity.Inner());
			inf::Infinitesimal& infinitesimal = dynamic_cast<inf::Infinitesimal&>(symbolInfinitesimal.Inner());
			number::Fraction product = infinity * infinitesimal;

			auto exponentChild = expression::Expression<expression::OPERATOR_TYPE_ADD_SUB>::Absorb(product);
			exponentChild.SetOperator(expression::OPERATOR_TYPE_FLAG_POWER);
			exp.AppendChild(exponentChild);

			exp.RemoveNode(infinitesimalItor.value());
			exp.RemoveNode(infinityItor.value());

			expression::Polymorphism::Visit(exp.Front())->SetOperator(expression::OPERATOR_TYPE_FLAG_NONE);
			return true;
		}

		return false;
	}
}