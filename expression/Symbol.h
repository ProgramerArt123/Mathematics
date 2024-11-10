#ifndef __EXPRESSION_SYMBOL_H__
#define __EXPRESSION_SYMBOL_H__

#include "Atom.h"

namespace expression {
	class Symbol : public Atom {
	public:
		Symbol(const expression::Symbol &prototype);
		Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag);
		Symbol(const std::string &name, bool isUnSigned = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);

		bool IsUnSigned() const override;

		virtual const std::string GetString(size_t pos = 0, uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		const std::string &Name() const;

		const Symbol &operator=(const Symbol &right);

		bool operator==(const Symbol &other) const;

		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		void Opposite() override;
	private:
		std::string m_name;

		bool m_unsigned = true;

	};
}

#endif