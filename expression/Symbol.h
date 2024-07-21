#ifndef __EXPRESSION_SYMBOL_H__
#define __EXPRESSION_SYMBOL_H__

#include "Node.hpp"

namespace expression {
	class Symbol : public Node {
	public:
		Symbol(const expression::Symbol &prototype);
		Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag);
		Symbol(const std::string &name, bool isPositive = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);

		const std::string &Name() const;

		const Symbol &operator=(const Symbol &right);

		bool operator==(const Symbol &other) const;

		const std::string OutPutString(size_t pos = 0) const override;
		bool EqualZero() const override;
		bool EqualOne() const override;

		void Opposite() override;
	private:
		std::string m_name;

		bool m_positive = true;

	};
}

#endif