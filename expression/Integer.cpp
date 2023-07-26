#include "Integer.h"

namespace expression {
	Integer::Integer(const number::Integer &value){
		m_value = std::shared_ptr<number::Number>(new number::Integer(value));
	}
}