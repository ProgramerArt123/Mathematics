#include <sstream>
#include "Node.hpp"

namespace expression {
	Node::Node(OPERATOR_TYPE_FLAG flag) {
		SetOperator(flag);
	}
	Node::Node(const Node& prototype) {
		*this = prototype;
	}
	const std::string Node::OutPutString(size_t pos) const {
		std::stringstream ss;
		ss << m_operator->OutPutString(pos);
		if (!IsDisplaySigned()) {
			ss << GetString();
		}
		else {
			ss << '(' << GetString() << ')';
		}
		return ss.str();
	}
	const Node& Node::operator=(const Node& right) {
		if (right.m_operator) {
			SetOperator(right.m_operator->GetFlag());
		}
		else {
			SetOperator(OPERATOR_TYPE_FLAG_NONE);
		}
		m_unsigned = right.m_unsigned;
		return *this;
	}
	bool Node::operator==(const Node& other) const {
		return m_operator->GetFlag() ==
			other.m_operator->GetFlag() &&
			m_unsigned == other.m_unsigned;
	}
	const OPERATOR_TYPE& Node::Operator() const {
		return *m_operator;
	}
	OPERATOR_TYPE_LEVEL Node::Level() const {
		return m_operator->GetLevel();
	}
	OPERATOR_TYPE_FLAG Node::Flag() const {
		return m_operator->GetFlag();
	}
	bool Node::IsNone() const {
		return OPERATOR_TYPE_FLAG_NONE == Flag();
	}
	bool Node::IsAdd() const {
		return OPERATOR_TYPE_FLAG_ADD == Flag();
	}
	bool Node::IsSub() const {
		return OPERATOR_TYPE_FLAG_SUB == Flag();
	}
	bool Node::IsMul() const {
		return OPERATOR_TYPE_FLAG_MUL == Flag();
	}
	bool Node::IsDiv() const {
		return OPERATOR_TYPE_FLAG_DIV == Flag();
	}
	bool Node::IsPower() const {
		return OPERATOR_TYPE_FLAG_POWER == Flag();
	}
	bool Node::IsRoot() const {
		return OPERATOR_TYPE_FLAG_ROOT == Flag();
	}
	bool Node::IsLogarithm() const {
		return OPERATOR_TYPE_FLAG_LOGARITHM == Flag();
	}
	bool Node::IsEqual(const Node& other, bool ignoreSigned, bool ignoreOperator) const {
		if (typeid(*this) != typeid(other)) {
			return false;
		}

		return (ignoreOperator || m_operator->GetFlag() ==
			other.m_operator->GetFlag()) &&
				(ignoreSigned || m_unsigned == other.m_unsigned);
	}
	size_t Node::Size() const {
		return 1;
	}
	bool Node::IsDisplaySigned() const {
		return !IsUnSigned();
	}
	bool Node::CollectSigned() {
		return false;
	}

	bool Node::CollectAddSubSigned() {
		if (IsDisplaySigned()) {
			Opposite();
			SetOperator(IsAdd() ? OPERATOR_TYPE_FLAG_SUB : OPERATOR_TYPE_FLAG_ADD);
			return true;
		}
		return false;
	}

	bool Node::CollectMulDivSigned() {
		if (IsDisplaySigned()) {
			Opposite();
			return true;
		}
		return false;
	}

	bool Node::CollectPowerRootSigned() {
		if (IsDisplaySigned()) {
			Opposite();
			return true;
		}
		return false;
	}

	void Node::Opposite() {
		m_unsigned = !m_unsigned;
	}

	void Node::Substitution(OPERATOR_TYPE_FLAG flag) {
		SetOperator(flag);
	}

	void Node::SuperpositionFlag(const OPERATOR_TYPE& other) {
		m_operator = std::move(other.Superposition(*m_operator));
	}

	void Node::SetOperator(OPERATOR_TYPE_FLAG flag) {
		m_operator = OPERATOR_TYPE::OperatorFactory(flag);
	}

	bool Node::IsUnSigned() const
	{
		return m_unsigned;
	}

	void Node::SetUnSigned(bool isUnSigned)
	{
		m_unsigned = isUnSigned;
	}


}