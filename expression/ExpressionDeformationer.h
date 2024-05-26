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
			size_t completed = 0;
			const Expression<OperatorType> &collect = expression.Collect(1, completed);
			if (completed) {
				Deformation(collect);
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
			if (1 < child.m_nodes.size())
			{
				std::list < std::pair< ExpressionNodes::const_iterator, ExpressionNodes::const_iterator > > combines;

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
				collect.m_nodes.push_back(child.m_nodes.front());
				m_collects.push_back(ExpressionDeformationer<OperatorType>(collect));
			}
			return *this;
		}
	private:

		const std::string m_expression;

		std::list<ExpressionDeformationer<OperatorType>> m_collects;

	};

}

#endif