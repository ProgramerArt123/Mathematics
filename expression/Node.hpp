#ifndef __EXPRESSION_NODE_HPP__
#define __EXPRESSION_NODE_HPP__

#include <list>
#include "Output.h"
#include "Operator.h"

namespace expression {
	class Node : public Output {
	public:
		Node();
		Node(const Node &prototype);
		const Node &operator=(const Node &right);
		void SetOperator(const std::unique_ptr<OPERATOR_TYPE> &flag);

		std::unique_ptr<OPERATOR_TYPE> m_operator;
	};
}

#endif