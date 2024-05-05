#ifndef __EXPRESSION_NUMBER_H__
#define __EXPRESSION_NUMBER_H__

#include "Node.hpp"

namespace expression {
	class Number : public Node {
	public:
		Number();
		Number(const Number &prototype);
		const Number &operator=(const Number &right);

	};
}

#endif