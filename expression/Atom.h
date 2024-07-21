#ifndef __EXPRESSION_ATOM_H__
#define __EXPRESSION_ATOM_H__

#include "Node.hpp"

namespace expression {
	class Atom : public Node {
	public:
		Atom(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);
		Atom(const Atom &prototype);

		const std::string OutPutString(size_t pos = 0) const override;

		virtual const std::string GetString(size_t pos = 0, uint8_t radix = 10) const = 0;

		const Atom &operator=(const Atom &right);
	};
}

#endif