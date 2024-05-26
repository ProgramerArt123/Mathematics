#include <sstream>
#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	Number::Number(OPERATOR_TYPE_FLAG flag): Node(flag) {
	}
	Number::Number(const Number &prototype){
		*this = prototype;
	}
	const std::string Number::OutPutString(size_t pos) const {
		std::stringstream ss;
		const std::string &op = m_operator->OutPutString(pos);
		const std::string &value = GetString(pos);
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
	const Number &Number::operator=(const Number &right) {
		Node::operator=(right);
		return *this;
	}
}