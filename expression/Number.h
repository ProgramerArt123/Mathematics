#ifndef __EXPRESSION_NUMBER_H__
#define __EXPRESSION_NUMBER_H__

#include "Node.hpp"

namespace expression {
	class Number : public Node {
	public:
		Number(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		Number(const Number &prototype);

		const std::string OutPutString(size_t pos = 0) const override;
		virtual const std::string GetString(size_t pos = 0, uint8_t radix = 10) const = 0;

		const Number &operator=(const Number &right);

	};
}

#endif