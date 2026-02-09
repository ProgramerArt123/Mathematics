#include <cassert>

#include "number/Fraction.h"
#include "number/Logarithm.h"
#include "number/Root.h"

#include "Operator.h"


namespace expression {

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE::OperatorFactory(OPERATOR_TYPE_FLAG flag) {
		switch (flag)
		{
		case expression::OPERATOR_TYPE_FLAG_NONE:
			return std::make_unique<OPERATOR_TYPE_NONE>();
			break;
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
		case expression::OPERATOR_TYPE_FLAG_LOGARITHM:
			return std::make_unique<OPERATOR_TYPE_LOGARITHM>();
			break;
		default:
			return nullptr;
			break;
		}
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_NONE::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_NONE;
	}

	const std::string OPERATOR_TYPE_NONE::OutPutString(size_t pos) const {
		assert(0 == pos);
		return "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_NONE::GetFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}
	
	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_NONE::Superposition(const OPERATOR_TYPE& other) const {
		return OperatorFactory(other.GetFlag());
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_ADD_SUB::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_ADD_SUB;
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_MUL_DIV::GetLevel() const{
		return OPERATOR_TYPE_LEVEL_MUL_DIV;
	}

	void OPERATOR_TYPE_MUL_DIV::DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const {
		if (OPERATOR_TYPE_FLAG_DIV == flag) {
			number::Fraction::DenominatorDomainVerification(domain.Value());
		}
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_POWER_ROOT::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_POWER_ROOT;
	}

	void OPERATOR_TYPE_POWER_ROOT::DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const {
		if (OPERATOR_TYPE_FLAG_ROOT == flag) {
			number::Root::ExponentDomainVerification(domain);
		}
	}

	const OPERATOR_TYPE_LEVEL OPERATOR_TYPE_LOGARITHM::GetLevel() const {
		return OPERATOR_TYPE_LEVEL_LOGARITHM;
	}
	
	const std::string OPERATOR_TYPE_ADD::OutPutString(size_t pos) const {
		return 0 < pos ? "+" : "";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_ADD::GetFlag() const {
		return OPERATOR_TYPE_FLAG_ADD;
	}

	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_ADD::Superposition(const OPERATOR_TYPE &other) const {
		return OperatorFactory(other.GetFlag());
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
		return 0 < pos ? "*" : "";
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
		assert(pos);
		return "^";
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
		assert(pos);
		return "&";
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

	const std::string OPERATOR_TYPE_LOGARITHM::OutPutString(size_t pos) const {
		assert(pos);
		return "|";
	}

	OPERATOR_TYPE_FLAG OPERATOR_TYPE_LOGARITHM::GetFlag() const {
		return OPERATOR_TYPE_FLAG_LOGARITHM;
	}
	std::unique_ptr<OPERATOR_TYPE> OPERATOR_TYPE_LOGARITHM::Superposition(const OPERATOR_TYPE &other) const {
		if (OPERATOR_TYPE_FLAG_LOGARITHM != other.GetFlag()) {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_LOGARITHM);
		}
		else {
			return OperatorFactory(expression::OPERATOR_TYPE_FLAG_POWER);
		}
	}
	void OPERATOR_TYPE_LOGARITHM::DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const {
		if (OPERATOR_TYPE_FLAG_NONE == flag) {
			number::Logarithm::PowerDomainVerification(domain);
		}
		else if (OPERATOR_TYPE_FLAG_LOGARITHM == flag) {
			number::Logarithm::PowerDomainVerification(domain);
		}
		else {
			assert(0);
		}
	}
}