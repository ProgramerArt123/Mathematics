#include "Symbol.h"
namespace expression {
	Symbol::Symbol(const expression::Symbol &prototype) {
		*this = prototype;
	}
	Symbol::Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	Symbol::Symbol(const std::string &name, bool isPositive, OPERATOR_TYPE_FLAG flag):
		Atom(flag), m_name(name), m_positive(isPositive){

	}
	bool Symbol::IsPositive() const {
		return m_positive;
	}
	const std::string Symbol::GetString(size_t pos, uint8_t radix) const {
		return m_positive ? Name() : "-" + Name();
	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	const Symbol &Symbol::operator=(const Symbol &right) {
		Atom::operator=(right);
		m_name = right.m_name;
		m_positive = right.m_positive;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return Atom::operator==(other) &&
			m_name == other.m_name &&
			m_positive == other.m_positive;
	}
	bool Symbol::EqualZero() const {
		return false;
	}
	bool Symbol::EqualOne() const {
		return false;
	}
	bool Symbol::EqualNegativeOne() const {
		return false;
	}
	void Symbol::Opposite() {
		m_positive = !m_positive;
	}
}