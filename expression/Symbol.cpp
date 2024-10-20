#include "Symbol.h"
namespace expression {
	Symbol::Symbol(const expression::Symbol &prototype) {
		*this = prototype;
	}
	Symbol::Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	Symbol::Symbol(const std::string &name, bool isUnSigned, OPERATOR_TYPE_FLAG flag):
		Atom(flag), m_name(name), m_unsigned(isUnSigned){

	}
	bool Symbol::IsUnSigned() const {
		return m_unsigned;
	}
	const std::string Symbol::GetString(size_t pos, uint8_t radix) const {
		return m_unsigned ? Name() : "-" + Name();
	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	const Symbol &Symbol::operator=(const Symbol &right) {
		Atom::operator=(right);
		m_name = right.m_name;
		m_unsigned = right.m_unsigned;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return Atom::operator==(other) &&
			m_name == other.m_name &&
			m_unsigned == other.m_unsigned;
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
		m_unsigned = !m_unsigned;
	}
}