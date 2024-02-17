#ifndef __EXPRESSION_EXPRESSION_H__
#define __EXPRESSION_EXPRESSION_H__
#include <list>
#include <memory>
#include <iostream>
#include "Node.h"
#include "Number.h"
#include "Operator.h"
#include "Integer.h"
#include "Fraction.h"

namespace expression {
	
	class Expression: public Node {
	public:
		Expression(const Fraction &n) {
			const std::shared_ptr<Fraction> fraction(new Fraction(n));
			m_fractions.push_front(fraction);
		}
		template<typename ...APPEND>
		Expression(const Fraction &n, OPERATOR_TYPE o, APPEND ...append) :Expression(append...) {
			const std::shared_ptr<Fraction> fraction(new Fraction(n));
			m_fractions.front()->m_type = o;
			m_fractions.push_front(fraction);
		}

		const Expression &operator=(const Expression &other) {
			m_fractions = other.m_fractions;
			return *this;
		}

		const std::string OutPutString(size_t pos = 0) const override;

		Expression Collect(size_t count = 2) const;

		bool Collectable() const;

	private:
		std::list<std::shared_ptr<Fraction>> m_fractions;

		friend class ExpressionDeformationer;
	};

}

#endif