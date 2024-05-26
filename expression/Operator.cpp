#include "Operator.h"
namespace expression {

	const uint8_t OPERATOR_TYPE_0::GetLevel() {
		return 0;
	}

	const uint8_t OPERATOR_TYPE_1::GetLevel() {
		return 1;
	}

	const std::string OPERATOR_TYPE_NONE::OutPutString(size_t pos) const {
		return "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_NONE::GetFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}

	const std::string OPERATOR_TYPE_ADD::OutPutString(size_t pos) const {
		return pos ? "+" : "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_ADD::GetFlag() const {
		return OPERATOR_TYPE_FLAG_ADD;
	}

	const std::string OPERATOR_TYPE_SUB::OutPutString(size_t pos) const {
		return "-";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_SUB::GetFlag() const {
		return OPERATOR_TYPE_FLAG_SUB;
	}
	
	const std::string OPERATOR_TYPE_MUL::OutPutString(size_t pos) const {
		return "*";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_MUL::GetFlag() const {
		return OPERATOR_TYPE_FLAG_MUL;
	}

	const std::string OPERATOR_TYPE_DIV::OutPutString(size_t pos) const {
		return "/";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_DIV::GetFlag() const {
		return OPERATOR_TYPE_FLAG_DIV;
	}
}