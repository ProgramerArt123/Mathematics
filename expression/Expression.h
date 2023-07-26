#ifndef __EXPRESSION_EXPRESSION_H__
#define __EXPRESSION_EXPRESSION_H__
#include <list>
#include <memory>
#include <iostream>
#include "Node.h"

namespace expression {
	class Operator;

	class Expression: public Node {
	public:
		template<typename NUMBER>
		Expression(NUMBER n) {
			m_nodes.push_front(std::shared_ptr<Node>(new NUMBER(n)));
		}
		template<typename NUMBER, typename OPERATOR, typename ...APPEND>
		Expression(NUMBER n, const OPERATOR &o, APPEND ...append):Expression(append...) {
			m_nodes.push_front(std::shared_ptr<Node>(new OPERATOR(o)));
			m_nodes.push_front(std::shared_ptr<Node>(new NUMBER(n)));
		}
		const std::string OutPutString() const override;

		std::list<std::shared_ptr<Node>> m_nodes;
	};

}

#endif