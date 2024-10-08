#include "Node.hpp"
namespace expression {
	Node::Node(OPERATOR_TYPE_FLAG flag){
		SetOperator(flag);
	}
	Node::Node(const Node &prototype){
		*this = prototype;
	}
	const Node &Node::operator=(const Node &right) {
		if (right.m_operator){
			SetOperator(right.m_operator->GetFlag());
		}
		else {
			SetOperator(OPERATOR_TYPE_FLAG_ADD);
		}
		return *this;
	}
	bool Node::operator==(const Node &other) const {
		return m_operator->GetFlag() == other.m_operator->GetFlag();
	}
	const OPERATOR_TYPE &Node::Operator() const {
		return *m_operator;
	}
	OPERATOR_TYPE_LEVEL Node::Level() const {
		return m_operator->GetLevel();
	}
	OPERATOR_TYPE_FLAG Node::Flag() const {
		return m_operator->GetFlag();
	}
	bool Node::IsAdd() const {
		return OPERATOR_TYPE_FLAG_ADD == Flag();
	}
	bool Node::IsEqual(const Node &other, bool ignoreOperator) const {
		if (typeid(*this) != typeid(other)) {
			return false;
		}
		if (!ignoreOperator) {
			return *this == other;
		}
		else {
			return true;
		}
	}

	void Node::SuperpositionFlag(const OPERATOR_TYPE &other) {
		m_operator = std::move(other.Superposition(*m_operator));
	}

	void Node::SetOperator(OPERATOR_TYPE_FLAG flag) {
		m_operator = OPERATOR_TYPE::OperatorFactory(flag);
	}
}