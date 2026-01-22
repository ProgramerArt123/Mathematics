#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "Infinitesimal.h"

namespace inf {

	number::Fraction Infinitesimal::ignore_line = number::Integer(1);

	Infinitesimal::Infinitesimal(const std::string& name, const number::Fraction &degree) :
		Symbol(name) {
		SetDegree(degree);
	}
	const std::string Infinitesimal::GetString(uint8_t radix) const {
		if (!IsZero()) {
			return Symbol::GetString(radix) + "[" + (IsRight() ? "<-" : "->") + ":" + m_degree.GetAbs().GetString(radix) + "]";
		}
		else {
			return "0";
		}
	}
	bool Infinitesimal::ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> &exp) {
		const std::optional<expression::ExpressionNodes::iterator> closureItor = exp.GetFirst<expression::ClosureNumber>();
		if (!closureItor) {
			return false;
		}
		for (auto node = exp.begin(); node != exp.end(); ++node) {
			const expression::SymbolWrapper* symbol = std::get_if<expression::SymbolWrapper>(&*node);
			if (symbol && symbol->Name() == Name()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(*closureItor.value());
				if (closure.IsDiv()) {
					exp.AddSymbol(expression::SymbolWrapper(std::make_shared<Infinitesimal>(*this / closure.Value())));
				}
				else {
					exp.AddSymbol(expression::SymbolWrapper(std::make_shared<Infinitesimal>(*this * closure.Value())));
				}
				exp.RemoveNode(node);
				exp.RemoveNode(closureItor.value());
				expression::Polymorphism::Visit(exp.Front())->SetOperator(expression::OPERATOR_TYPE_FLAG_NONE);
				break;
			}
		}
		return true;
	}
	std::shared_ptr<expression::Symbol> Infinitesimal::GetClone() const {
		return std::make_shared<Infinitesimal>(*this);
	}
	
	Infinitesimal Infinitesimal::operator+(const Infinitesimal &addition) const {
		if (IsZero()) {
			return addition;
		}
		else if (addition.IsZero()) {
			return *this;
		}
		else {
			Infinitesimal sum(Name());

			sum.SetDegree((m_degree.GetReciprocal() + addition.m_degree.GetReciprocal()).GetReciprocal());

			return sum;
		}

	}
	Infinitesimal &Infinitesimal::operator+=(const Infinitesimal &addition) {
		*this = *this + addition;
		return *this;
	}
	Infinitesimal Infinitesimal::operator-(const Infinitesimal &subtrahend) const {
		if (IsZero()) {
			Infinitesimal negative(subtrahend);
			negative.m_degree.Opposite();
			return negative;
		}
		else if (subtrahend.IsZero()) {
			Infinitesimal negative(*this);
			negative.m_degree.Opposite();
			return negative;
		}
		else {
			Infinitesimal difference(Name(), number::Integer(0));

			if (m_degree != subtrahend.m_degree) {
				difference.SetDegree((m_degree.GetReciprocal() - subtrahend.m_degree.GetReciprocal()).GetReciprocal());
			}

			return difference;
		}
	}
	Infinitesimal &Infinitesimal::operator-=(const Infinitesimal &subtrahend) {
		*this = *this - subtrahend;
		return *this;
	}
	number::Fraction Infinitesimal::operator/(const Infinitesimal &divisor) const {
		return m_degree / divisor.m_degree;
	}
	number::Logarithm Infinitesimal::Logarithm(const Infinitesimal &base) const {
		return number::Logarithm(base.m_degree, this->m_degree);
	}
	Infinitesimal Infinitesimal::operator*(const number::Fraction &multiplier) const {
		Infinitesimal product(Name());

		product.SetDegree(m_degree / multiplier);

		return product;
	}
	Infinitesimal Infinitesimal::operator/(const number::Fraction &divisor) const {
		Infinitesimal quotient(Name());

		quotient.SetDegree(m_degree * divisor);

		return quotient;
	}
	bool Infinitesimal::IsPositive() const{
		return m_degree.IsPositive() && !IsZero();
	}
	bool Infinitesimal::IsNegative() const{
		return !m_degree.IsPositive() && !IsZero();
	}
	bool Infinitesimal::IsZero() const{
		return m_degree.EqualZero();
	}
	bool Infinitesimal::IsLeft() const {
		return IsNegative();
	}
	bool Infinitesimal::IsRight() const {
		return IsPositive();
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
	const number::Fraction &Infinitesimal::Degree() const {
		return m_degree;
	}
	void Infinitesimal::SetIgnoreLine(const number::Fraction& ignore) {
		ignore_line = ignore;
	}
}