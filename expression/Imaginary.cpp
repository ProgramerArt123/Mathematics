
#include "number/Complex.h"
#include "ClosureNumber.hpp"
#include "Expression.hpp"
#include "Imaginary.h"

namespace expression {
	bool Imaginary::ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) {
		if (const expression::Symbol *symbol = std::get_if<expression::Symbol>(&exp.Front())) {
			if (Name() != symbol->Name()) {
				return false;
			}
			auto driver = exp.GetFirst<expression::ClosureNumber>();
			if (!driver.has_value()) {
				return false;
			}
			const number::Integer &exponent = std::get<expression::ClosureNumber>(*driver.value()).Value();
			const number::Complex &power = number::Complex::Power(number::Imaginary(number::Integer(1, symbol->IsUnSigned())), exponent.Value());
			if (exponent.IsPositive()) {
				*exp.begin() = Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(power).SetChild();
			}
			else {
				*exp.begin() = Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(power)).SetChild();
			}
			exp.RemoveNode(driver.value());
			return true;
		}
		return false;
	}
}