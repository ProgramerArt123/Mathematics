#ifndef __EXPRESSION_NUMBER_H__
#define __EXPRESSION_NUMBER_H__

#include "Atom.h"

namespace expression {
	class Number : public Atom {
	public:
		Number(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE): Atom(flag) {
		}
		Number(const Number &prototype);

		const Number &operator=(const Number &right) {
			Atom::operator=(right);
			return *this;
		}

	};
}

#endif