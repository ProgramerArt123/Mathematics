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
		Node(isPositive, flag), m_name(name){

	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	const Symbol &Symbol::operator=(const Symbol &right) {
		Node::operator=(right);
		m_name = right.m_name;
		m_positive = right.m_positive;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return Node::operator==(other) &&
			m_name == other.m_name &&
			m_positive == other.m_positive;
	}
	const std::string Symbol::OutPutString(size_t pos) const {
		return m_positive ? Name() : "-" + Name();
	}
	bool Symbol::EqualZero() const {
		return false;
	}
	bool Symbol::EqualOne() const {
		return false;
	}
}