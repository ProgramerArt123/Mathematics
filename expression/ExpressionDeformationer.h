#ifndef __EXPRESSION_EXPRESSION_DEFORMATIONER_H__
#define __EXPRESSION_EXPRESSION_DEFORMATIONER_H__

#include "Expression.h"

namespace expression {
	
	class ExpressionDeformationer : public Output{
	public:
		ExpressionDeformationer(const std::string &expression);

		ExpressionDeformationer(const Expression &expression, const ExpressionDeformationer *parent);

		const std::string OutPutString(size_t pos = 0) const override;

		const ExpressionDeformationer &Deformation(const Expression &child);
	private:

		const std::string m_expression;

		std::list<ExpressionDeformationer> m_collects;

		const ExpressionDeformationer *m_parent = nullptr;
	};

}

#endif