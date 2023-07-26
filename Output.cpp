#include "Output.h"

std::ostream& operator<<(std::ostream& out, const Output &output) {
	out << output.OutPutString();
	return out;
}

