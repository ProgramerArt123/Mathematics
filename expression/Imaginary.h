#ifndef __EXPRESSION_IMAGINARY_H__
#define __EXPRESSION_IMAGINARY_H__

#include "Symbol.h"

#define IMAGINARY_NAME "i"

namespace expression {
	class Imaginary : public Symbol {
	public:
		Imaginary() :
			Symbol(IMAGINARY_NAME){

		}
		bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) override;

		std::shared_ptr<Symbol> GetClone() const override;
	};
}

#endif