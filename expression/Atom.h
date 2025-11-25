#ifndef __EXPRESSION_ATOM_H__
#define __EXPRESSION_ATOM_H__

#include "Node.hpp"


namespace expression {
	class Atom : public Node {
	public:
		Atom(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		Atom(const Atom &prototype);

		const Atom &operator=(const Atom &right);
	};
}

#endif