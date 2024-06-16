#include "Operator.h"
namespace expression {

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE::OperatorFactory(OPERATOR_TYPE_FLAG flag) {
		switch (flag)
		{
		case expression::OPERATOR_TYPE_FLAG_ADD:
			return std::make_unique<OPERATOR_TYPE_ADD>();
			break;
		case expression::OPERATOR_TYPE_FLAG_SUB:
			return std::make_unique<OPERATOR_TYPE_SUB>();
			break;
		case expression::OPERATOR_TYPE_FLAG_MUL:
			return std::make_unique<OPERATOR_TYPE_MUL>();
			break;
		case expression::OPERATOR_TYPE_FLAG_DIV:
			return std::make_unique<OPERATOR_TYPE_DIV>();
			break;
		case expression::OPERATOR_TYPE_FLAG_POWER:
			return std::make_unique<OPERATOR_TYPE_POWER>();
			break;
		case expression::OPERATOR_TYPE_FLAG_ROOT:
			return std::make_unique<OPERATOR_TYPE_ROOT>();
			break;
		default:
			return nullptr;
			break;
		}
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_0::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_0;
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_1::GetLevel() const{
		return OPERATOR_TYPE_LEVEL_1;
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_2::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_2;
	}
	
	const std::string OPERATOR_TYPE_ADD::OutPutString(size_t pos) const {
		return pos ? "+" : "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_ADD::GetFlag() const {
		return OPERATOR_TYPE_FLAG_ADD;
	}

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_ADD::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_SUB != other.GetFlag()){
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_ADD);
		}
		else{
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_SUB);
		}
	}

	const std::string OPERATOR_TYPE_SUB::OutPutString(size_t pos) const {
		return "-";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_SUB::GetFlag() const {
		return OPERATOR_TYPE_FLAG_SUB;
	}

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_SUB::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_SUB != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_SUB);
		}
		else{
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_ADD);
		}
	}
	
	const std::string OPERATOR_TYPE_MUL::OutPutString(size_t pos) const {
		return pos ? "*" : "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_MUL::GetFlag() const {
		return OPERATOR_TYPE_FLAG_MUL;
	}

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_MUL::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_DIV != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_MUL);
		}
		else {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_DIV);
		}
	}

	const std::string OPERATOR_TYPE_DIV::OutPutString(size_t pos) const {
		return "/";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_DIV::GetFlag() const {
		return OPERATOR_TYPE_FLAG_DIV;
	}
	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_DIV::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_DIV != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_DIV);
		}
		else {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_MUL);
		}
	}


	const std::string OPERATOR_TYPE_POWER::OutPutString(size_t pos) const {
		return pos ? "^" : "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_POWER::GetFlag() const {
		return OPERATOR_TYPE_FLAG_POWER;
	}
	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_POWER::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_ROOT != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_POWER);
		}
		else {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_ROOT);
		}
	}

	const std::string OPERATOR_TYPE_ROOT::OutPutString(size_t pos) const {
		return "@";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_ROOT::GetFlag() const {
		return OPERATOR_TYPE_FLAG_ROOT;
	}
	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_ROOT::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_ROOT != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_ROOT);
		}
		else {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_POWER);
		}
	}
}