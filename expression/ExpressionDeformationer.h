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
			std::optional<Expression<OperatorType>> collect = expression.Collect();
			if (collect.has_value()) {
				Deformation(collect.value());
			}
			else {
				Expression<OperatorType> reduction(expression);
				if (reduction.ReduceFraction()) {
					m_fraction = std::make_unique<ExpressionDeformationer<OPERATOR_TYPE_ADD_SUB>>(reduction.GetFractionReduction());
				}
				else if (reduction.ReduceRoot() || reduction.ReduceLogarithm()) {
					m_open = std::make_unique<ExpressionDeformationer<OPERATOR_TYPE_MUL_DIV>>(reduction.GetOpenReduction());
				}
			}
		}

		const std::string OutPutString(size_t pos = 0) const override {
			if (m_fraction) {
				return m_fraction->OutPutString();
			}
			if (m_open) {
				return m_open->OutPutString();
			}

			if (m_collects.empty()) {
				return m_expression;
			}
			else {
				std::stringstream ss;
				for (const auto &collect : m_collects) {
					ss << m_expression + "\t==>\t" + collect.OutPutString() << std::endl;
				}
				return ss.str();
			}
		}
		const ExpressionDeformationer<OperatorType> &Deformation(const Expression<OperatorType> &child) {
			if (1 < child.Size())
			{
				std::list < std::pair<typename Expression<OperatorType>::ExpressionNodes::const_iterator,
					typename Expression<OperatorType>::ExpressionNodes::const_iterator > > combines;

				for (auto itorI = child.m_nodes.cbegin(); itorI != child.m_nodes.cend(); itorI++) {
					for (auto itorJ = itorI; itorJ != child.m_nodes.cend(); itorJ++) {
						if (itorI != itorJ) {
							combines.push_back(std::make_pair(itorI, itorJ));
						}
					}
				}

				for (auto const combine : combines) {
					Expression<OperatorType> collect;
					collect.m_nodes.push_back(*combine.first);
					collect.m_nodes.push_back(*combine.second);
					for (auto itor = child.m_nodes.cbegin(); itor != child.m_nodes.cend(); ++ itor) {
						if (itor != combine.first && itor != combine.second) {
							collect.m_nodes.push_back(*itor);
						}
					}
					m_collects.push_back(ExpressionDeformationer<OperatorType>(collect));
				}
			}
			else
			{
				Expression<OperatorType> collect;
				collect.m_nodes.push_back(child.Front());
				m_collects.push_back(ExpressionDeformationer<OperatorType>(collect));
			}
			return *this;
		}
	private:

		const std::string m_expression;

		std::list<ExpressionDeformationer<OperatorType>> m_collects;

		std::unique_ptr<ExpressionDeformationer<OPERATOR_TYPE_ADD_SUB>> m_fraction;

		std::unique_ptr<ExpressionDeformationer<OPERATOR_TYPE_MUL_DIV>> m_open;
	};

}

#endif