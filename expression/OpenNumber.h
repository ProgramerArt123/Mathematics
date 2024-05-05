#ifndef __EXPRESSION_OPEN_NUMBER_H__
#define __EXPRESSION_OPEN_NUMBER_H__

#include "Number.h"
#include "number/Root.h"
#include "Operator.h"

namespace expression {
	class OpenNumber : public Number {
	public:
		OpenNumber(const expression::OpenNumber &prototype);
		OpenNumber(const number::Root &value);
		const std::string OutPutString(size_t pos = 0) const override;
		const OpenNumber &operator=(const OpenNumber &right);
		bool Collect0(const expression::OpenNumber &right, expression::OpenNumber &collect) const;
		bool Collect1(const expression::OpenNumber &right, expression::OpenNumber &collect) const;
		const number::Root &Value()const;
	private:
		number::Root m_value;
	};
}

#endif