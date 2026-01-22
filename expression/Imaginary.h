#ifndef __EXPRESSION_IMAGINARY_H__
#define __EXPRESSION_IMAGINARY_H__

#include "Symbol.h"

namespace expression {
	class Imaginary : public Symbol {
	public:
		Imaginary(const std::string &name = "i") :
			Symbol(name){

		}
		bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) override;

		std::shared_ptr<Symbol> GetClone() const override;
	};
}

#define SYMBOL_IMAGINARY SymbolWrapper(std::make_shared<expression::Imaginary>("i"))

#endif