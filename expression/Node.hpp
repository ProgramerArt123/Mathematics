#ifndef __EXPRESSION_NODE_HPP__
#define __EXPRESSION_NODE_HPP__

#include <list>
#include "Output.h"
#include "Operator.h"
#include "number/Natural.h"

namespace expression {
	class Node : public Output {
	public:
		Node(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		Node(const Node &prototype);

		const std::string OutPutString(size_t pos = 0) const override;
		
		const Node &operator=(const Node &right);
		bool operator==(const Node &other) const;
		const OPERATOR_TYPE &Operator() const;
		OPERATOR_TYPE_LEVEL OperatorLevel() const;
		OPERATOR_TYPE_FLAG Flag() const;
		bool IsNone() const;
		bool IsAdd() const;
		bool IsSub() const;
		bool IsMul() const;
		bool IsDiv() const;
		bool IsPower() const;
		bool IsRoot() const;
		bool IsLogarithm() const;


		virtual bool IsEqual(const Node &other, bool ignoreSigned = false, bool ignoreOperator = false) const;
		virtual size_t Size() const;
		virtual bool EqualZero() const = 0;
		virtual bool EqualPositiveOne() const = 0;
		virtual bool EqualNegativeOne() const = 0;
		virtual const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const = 0;
		virtual bool IsDisplaySigned() const;

		virtual bool Signed();
		virtual size_t AddSubSigned();
		virtual size_t MulDivSigned();
		virtual size_t PowerRootSigned();

		virtual void Opposite();

		virtual void Substitution(OPERATOR_TYPE_FLAG flag);

		virtual void SetOperator(OPERATOR_TYPE_FLAG flag);
		
		void SuperpositionFlag(const OPERATOR_TYPE &other);


		bool IsUnSigned() const;

		void SetUnSigned(bool isUnSigned);
		
	protected:

		std::unique_ptr<OPERATOR_TYPE> m_operator;

		bool m_unsigned = true;

	};
}

#endif