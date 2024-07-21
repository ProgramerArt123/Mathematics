#ifndef __EXPRESSION_OPEN_NUMBER_H__
#define __EXPRESSION_OPEN_NUMBER_H__

#include <optional>
#include "Number.h"
#include "number/Root.h"
#include "Operator.h"

namespace expression {
	class OpenNumber : public Number {
	public:
		OpenNumber(const expression::OpenNumber &prototype);
		OpenNumber(const expression::OpenNumber &prototype, OPERATOR_TYPE_FLAG flag);
		OpenNumber(const number::Root &value, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);
		const std::string GetString(size_t pos = 0, uint8_t radix = 10) const override;
		bool EqualZero() const override;
		bool EqualOne() const override;
		const OpenNumber &operator=(const OpenNumber &right);
		std::optional<expression::OpenNumber> Collect(const expression::OpenNumber &right) const;
		const number::Root &Value()const;

		void Opposite() override;
	private:

		std::optional<expression::OpenNumber> Collect0(const expression::OpenNumber &right) const;
		std::optional<expression::OpenNumber> Collect1(const expression::OpenNumber &right) const;

		number::Root m_value;
	};
}

#endif