#include "Integer.h"

namespace expression {
	Integer::Integer(const number::Integer &value):
		m_value(value){
	}
	const std::string Integer::OutPutString(size_t pos) const {
		if (pos) {
			if (OPERATOR_TYPE_ADD == m_type) {
				if (!m_value.IsPositive()) {
					return m_value.OutPutString();
				}
			}
			else if (OPERATOR_TYPE_SUB == m_type) {
				if (!m_value.IsPositive()) {
					return operators[OPERATOR_TYPE_ADD].m_output +
						(-m_value).OutPutString();
				}
			}
		}
		else {
			if (OPERATOR_TYPE_ADD == m_type) {
				return m_value.OutPutString();
			}
			else if (OPERATOR_TYPE_SUB == m_type) {
				if (!m_value.IsPositive()) {
					return (-m_value).OutPutString();
				}
			}
		}
		return operators[m_type].m_output + m_value.OutPutString();
	}
}