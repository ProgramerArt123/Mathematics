#include "Node.hpp"
namespace expression {
	Node::Node(OPERATOR_TYPE_FLAG flag){
		SetOperator(flag);
	}
	Node::Node(const Node &prototype){
		*this = prototype;
	}
	const Node &Node::operator=(const Node &right) {
		SetOperator(right.m_operator->GetFlag());
		return *this;
	}
	OPERATOR_TYPE_FLAG Node::Flag() const {
		return m_operator->GetFlag();
	}

	void Node::SetOperator(OPERATOR_TYPE_FLAG flag) {
		switch (flag)
		{
		case expression::OPERATOR_TYPE_FLAG_NONE:
			m_operator.reset(new OPERATOR_TYPE_NONE);
			break;
		case expression::OPERATOR_TYPE_FLAG_ADD:
			m_operator.reset(new OPERATOR_TYPE_ADD);
			break;
		case expression::OPERATOR_TYPE_FLAG_SUB:
			m_operator.reset(new OPERATOR_TYPE_SUB);
			break;
		case expression::OPERATOR_TYPE_FLAG_MUL:
			m_operator.reset(new OPERATOR_TYPE_MUL);
			break;
		case expression::OPERATOR_TYPE_FLAG_DIV:
			m_operator.reset(new OPERATOR_TYPE_DIV);
			break;
		default:
			break;
		}
	}
}