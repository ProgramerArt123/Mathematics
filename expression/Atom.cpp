#include "Atom.h"

namespace expression {
	Atom::Atom(OPERATOR_TYPE_FLAG flag): Node(flag) {
	}
	Atom::Atom(const Atom &prototype){
		*this = prototype;
	}
	const Atom &Atom::operator=(const Atom &right) {
		Node::operator=(right);
		return *this;
	}
}