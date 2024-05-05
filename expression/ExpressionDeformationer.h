#ifndef __EXPRESSION_EXPRESSION_DEFORMATIONER_H__
#define __EXPRESSION_EXPRESSION_DEFORMATIONER_H__

#include "Expression.hpp"

namespace expression {
	template<typename OperatorType>
	class ExpressionDeformationer : public Output{
	public:
		ExpressionDeformationer(const std::string &expression) :
			m_expression(expression) {

		}
		ExpressionDeformationer(const Expression<OperatorType> &expression) :
			m_expression(expression.OutPutString()) {
			if (expression.Collectable()) {
				Deformation(expression.Collect());
			}
		}

		const std::string OutPutString(size_t pos) const override {
			if (m_collects.empty()) {
				return m_expression;
			}
			else {
				std::stringstream ss;
				for (const auto &collect : m_collects) {
					for (size_t i = 0; i < pos; i++) {
						ss << "\t";
					}
					ss << m_expression + "\t==>\t" + collect.OutPutString(pos + 1) << std::endl;
				}
				return ss.str();
			}
		}
		const ExpressionDeformationer<OperatorType> &Deformation(const Expression<OperatorType> &child) {
			return *this;
		}
	private:

		const std::string m_expression;

		std::list<ExpressionDeformationer<OperatorType>> m_collects;

	};

}

#endif