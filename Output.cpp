#include <sstream>

#include "Output.h"

const Output &Output::updatePosition(size_t pos) const {
	m_position = pos;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Output &output) {
	out << output.OutPutString();
	return out;
}

