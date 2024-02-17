#include <sstream>
#include "ExpressionDeformationer.h"
namespace expression {
	ExpressionDeformationer::ExpressionDeformationer(const std::string &expression):
		m_expression(expression) {

	}

	ExpressionDeformationer::ExpressionDeformationer(const Expression &expression, const ExpressionDeformationer *parent) :
		m_expression(expression.OutPutString()), m_parent(parent) {
		if (expression.Collectable()) {
			Deformation(expression.Collect());
		}
	}

	const std::string ExpressionDeformationer::OutPutString(size_t pos) const {
		if (m_collects.empty()){
			return m_expression;
		}
		else{
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

	const ExpressionDeformationer &ExpressionDeformationer::Deformation(const Expression &child) {
		if (1 < child.m_fractions.size())
		{
			std::list < std::pair< std::list<std::shared_ptr<Fraction>>::const_iterator,
				std::list<std::shared_ptr<Fraction>>::const_iterator > > combines;

			for (auto itorI = child.m_fractions.cbegin(); itorI != child.m_fractions.cend(); itorI++) {
				for (auto itorJ = itorI; itorJ != child.m_fractions.cend(); itorJ++) {
					if (itorI != itorJ) {
						combines.push_back(std::make_pair(itorI, itorJ));
					}
				}
			}

			for (auto const combine : combines) {
				Expression collect(**combine.first, (**combine.second).m_type, **combine.second);
				for (const auto &i : child.m_fractions) {
					if (i != *combine.first && i != *combine.second) {
						collect.m_fractions.push_back(i);
					}
				}
				m_collects.push_back(ExpressionDeformationer(collect, this));
			}
		}
		else
		{
			m_collects.push_back(ExpressionDeformationer(Expression(*child.m_fractions.front()), this));
		}

		return *this;
	}

}