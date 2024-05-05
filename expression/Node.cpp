#include "Node.hpp"
namespace expression {
	Node::Node(){
	}
	Node::Node(const Node &prototype){
		*this = prototype;
	}
	const Node &Node::operator=(const Node &right) {
		SetOperator(right.m_operator);
		return *this;
	}
	void Node::SetOperator(const std::unique_ptr<OPERATOR_TYPE> &flag) {
		if (!flag) {
			m_operator.reset();
			return;
		}
		switch (flag->GetFlag())
		{
		case OPERATOR_TYPE_FLAG_ADD:
			m_operator.reset(new OPERATOR_TYPE_ADD);
			break;
		case OPERATOR_TYPE_FLAG_SUB:
			m_operator.reset(new OPERATOR_TYPE_SUB);
			break;
		case OPERATOR_TYPE_FLAG_MUL:
			m_operator.reset(new OPERATOR_TYPE_MUL);
			break;
		case OPERATOR_TYPE_FLAG_DIV:
			m_operator.reset(new OPERATOR_TYPE_DIV);
			break;
		default:
			break;
		}
	}
}