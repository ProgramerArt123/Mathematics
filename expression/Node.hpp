#ifndef __EXPRESSION_NODE_HPP__
#define __EXPRESSION_NODE_HPP__

#include <list>
#include "Output.h"
#include "Operator.h"

namespace expression {
	class Node : public Output {
	public:
		Node(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);
		Node(const Node &prototype);

		const Node &operator=(const Node &right);
		bool operator==(const Node &other) const;
		const OPERATOR_TYPE &Operator() const;
		OPERATOR_TYPE_LEVEL Level() const;
		OPERATOR_TYPE_FLAG Flag() const;
		bool IsAdd() const;

		virtual bool IsEqual(const Node &other, bool ignoreOperator = false) const;
		virtual bool EqualZero() const = 0;
		virtual bool EqualOne() const = 0;

		virtual void Opposite() = 0;

		void SuperpositionFlag(const OPERATOR_TYPE &other);

		void SetOperator(OPERATOR_TYPE_FLAG flag);
	protected:

		std::unique_ptr<OPERATOR_TYPE> m_operator;

	};
}

#endif