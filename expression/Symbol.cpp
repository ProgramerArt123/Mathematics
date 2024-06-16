#include "Symbol.h"
namespace expression {
	Symbol::Symbol(const expression::Symbol &prototype) {
		*this = prototype;
	}
	Symbol::Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	Symbol::Symbol(const std::string &name, OPERATOR_TYPE_FLAG flag):
		Node(flag), m_name(name){

	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	const Symbol &Symbol::operator=(const Symbol &right) {
		Node::operator=(right);
		m_name = right.m_name;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return Node::operator==(other) && m_name == other.m_name;
	}
	const std::string Symbol::OutPutString(size_t pos) const {
		return m_name;
	}
	bool Symbol::EqualZero() const {
		return false;
	}
	bool Symbol::EqualOne() const {
		return false;
	}
}