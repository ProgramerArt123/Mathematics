#include <sstream>
#include "Atom.h"

namespace expression {
	Atom::Atom(OPERATOR_TYPE_FLAG flag): Node(flag) {
	}
	Atom::Atom(const Atom &prototype){
		*this = prototype;
	}
	const std::string Atom::OutPutString() const {
		std::stringstream ss;
		const std::string &op = m_operator->updatePosition(m_position).OutPutString();
		const std::string &value = GetString(m_position);
		ss << op;
		if (op.empty()) {
			ss << value;
		}
		else {
			if (value.front() != '-')
			{
				ss << value;
			}
			else
			{
				ss << '(' << value << ')';
			}
		}
		return ss.str();
	}
	const Atom &Atom::operator=(const Atom &right) {
		Node::operator=(right);
		return *this;
	}
}