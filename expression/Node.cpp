#include "Node.hpp"
namespace expression {
	Node::Node(bool isPositive, OPERATOR_TYPE_FLAG flag):
		m_positive(isPositive){
		SetOperator(flag);
	}
	Node::Node(const Node &prototype){
		*this = prototype;
	}
	const Node &Node::operator=(const Node &right) {
		m_positive = right.m_positive;
		if (right.m_operator){
			SetOperator(right.m_operator->GetFlag());
		}
		else {
			SetOperator(OPERATOR_TYPE_FLAG_ADD);
		}
		return *this;
	}
	bool Node::operator==(const Node &other) const {
		return m_positive == other.m_positive &&
			m_operator->GetFlag() == other.m_operator->GetFlag();
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
	bool Node::IsEqual(const Node &other) const {
		if (typeid(*this) != typeid(other)) {
			return false;
		}
		return *this == other;
	}
	void Node::Opposite() {
		m_positive = !m_positive;
	}

	void Node::SuperpositionFlag(const OPERATOR_TYPE &other) {
		m_operator = std::move(other.Superposition(*m_operator));
	}

	void Node::SetOperator(OPERATOR_TYPE_FLAG flag) {
		m_operator = OPERATOR_TYPE::OperatorFactory(flag);
	}
}