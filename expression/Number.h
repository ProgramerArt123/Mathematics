#ifndef __EXPRESSION_NUMBER_H__
#define __EXPRESSION_NUMBER_H__

#include <memory>
#include "Node.h"
#include "Operator.h"
#include "number/Number.h"

namespace expression {
	class Number : public Node {
	public:
		OPERATOR_TYPE m_type = OPERATOR_TYPE_ADD;
	};
}

#endif