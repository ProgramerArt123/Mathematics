#ifndef __EXPRESSION_IMAGINARY_H__
#define __EXPRESSION_IMAGINARY_H__

#include "Symbol.h"

namespace expression {
	class Imaginary : public Symbol {
	public:
		Imaginary(const std::string& name, bool isUnSigned = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE):
			Symbol(name, isUnSigned, flag){

		}
		bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) override;
	};
}

#define SYMBOL_IMAGINARY SymbolManager::GetInstance().GetSymbol<expression::Imaginary>("i")

#endif