#ifndef __EXPRESSION_NODE_HPP__
#define __EXPRESSION_NODE_HPP__

#include <list>
#include "Output.h"
#include "Operator.h"

namespace expression {
	class Node : public Output {
	public:
		Node(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		Node(const Node &prototype);



		const Node &operator=(const Node &right);
		OPERATOR_TYPE_FLAG Flag() const;

		template<typename OperatorType>
		void SuperpositionFlag(OPERATOR_TYPE_FLAG flag, bool isFirst) {
			switch (flag)
			{
			case expression::OPERATOR_TYPE_FLAG_NONE:
			{
				if (0 == OperatorType::GetLevel())
				{
					if (OPERATOR_TYPE_FLAG_SUB != Flag())
					{
						if (!isFirst)
						{
							SetOperator(expression::OPERATOR_TYPE_FLAG_ADD);
						}
					}
					else
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_SUB);
					}
				}
				else if (1 == OperatorType::GetLevel())
				{
					if (OPERATOR_TYPE_FLAG_DIV != Flag())
					{
						if (!isFirst)
						{
							SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
						}
					}
					else
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_DIV);
					}
				}
			}
			break;
			case expression::OPERATOR_TYPE_FLAG_ADD:
			{
				if (OPERATOR_TYPE_FLAG_SUB != Flag())
				{
					if (!isFirst)
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_ADD);
					}
				}
				else
				{
					SetOperator(expression::OPERATOR_TYPE_FLAG_SUB);
				}
			}
			break;
			case expression::OPERATOR_TYPE_FLAG_SUB:
			{
				if (OPERATOR_TYPE_FLAG_SUB != Flag())
				{
					SetOperator(expression::OPERATOR_TYPE_FLAG_SUB);
				}
				else
				{
					if (!isFirst)
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_ADD);
					}
				}
			}
			break;
			case expression::OPERATOR_TYPE_FLAG_MUL:
			{
				if (OPERATOR_TYPE_FLAG_DIV != Flag())
				{
					if (!isFirst)
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
					}
				}
				else
				{
					SetOperator(expression::OPERATOR_TYPE_FLAG_DIV);
				}
			}
			break;
			case expression::OPERATOR_TYPE_FLAG_DIV:
			{
				if (OPERATOR_TYPE_FLAG_DIV != Flag())
				{
					SetOperator(expression::OPERATOR_TYPE_FLAG_DIV);
				}
				else
				{
					if (!isFirst)
					{
						SetOperator(expression::OPERATOR_TYPE_FLAG_MUL);
					}
				}
			}
			break;
			default:
				break;
			}
		}
	protected:
		void SetOperator(OPERATOR_TYPE_FLAG flag);

		std::unique_ptr<OPERATOR_TYPE> m_operator;
	};
}

#endif