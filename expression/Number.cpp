#include "number/Number.h"
#include "Number.h"

namespace expression {
	const std::string Number::OutPutString() const {
		return m_value->OutPutString();
	}
}