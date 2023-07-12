#include "Integer.h"
#include "Imaginary.h"

Imaginary::Imaginary(const Integer &value) :
	m_value(new Integer(value)) {
	
}

const std::string Imaginary::GetString(uint8_t base) const {
	return m_value->GetString(base) + "i";
}