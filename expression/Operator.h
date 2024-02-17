#ifndef __EXPRESSION_OPERATOR_H__
#define __EXPRESSION_OPERATOR_H__

#include "Node.h"
namespace expression {

	enum OPERATOR_TYPE {
		OPERATOR_TYPE_ADD,
		OPERATOR_TYPE_SUB,
	};

	struct OperatorType {
		OPERATOR_TYPE m_type = OPERATOR_TYPE_ADD;
		const char *m_output = "";
	};

	OperatorType operators[];
}

#endif