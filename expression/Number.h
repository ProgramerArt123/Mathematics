#ifndef __EXPRESSION_NUMBER_H__
#define __EXPRESSION_NUMBER_H__

#include <memory>
#include "Node.h"
#include "number/Number.h"

namespace expression {
	class Number : public Node {
	public:
		const std::string OutPutString() const override;

		std::shared_ptr<number::Number> m_value;
	};
}

#endif