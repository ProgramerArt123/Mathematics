#ifndef __EXPRESSION_NODE_HPP__
#define __EXPRESSION_NODE_HPP__

#include <list>
#include "Output.h"
#include "Operator.h"

namespace expression {
	class Node : public Output {
	public:
		Node(bool isPositive = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);
		Node(const Node &prototype);

		const Node &operator=(const Node &right);
		bool operator==(const Node &other) const;
		const OPERATOR_TYPE &Operator() const;
		OPERATOR_TYPE_LEVEL Level() const;
		OPERATOR_TYPE_FLAG Flag() const;

		virtual bool IsEqual(const Node &other) const;
		virtual bool EqualZero() const = 0;
		virtual bool EqualOne() const = 0;

		void Opposite();

		void SuperpositionFlag(const OPERATOR_TYPE &other);
	protected:
		void SetOperator(OPERATOR_TYPE_FLAG flag);

		std::unique_ptr<OPERATOR_TYPE> m_operator;

		bool m_positive = true;
	};
}

#endif