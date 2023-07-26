#ifndef __EXPRESSION_ADD_H__
#define __EXPRESSION_ADD_H__

#include "Operator.h"
namespace expression {
	class Add : public Operator {
	public:
		const std::string OutPutString() const override;
	};
}

#endif