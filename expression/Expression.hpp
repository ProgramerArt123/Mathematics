#ifndef __EXPRESSION_EXPRESSION_HPP__
#define __EXPRESSION_EXPRESSION_HPP__
#include <list>
#include <memory>
#include <iostream>
#include <stack>
#include <map>
#include <sstream>
#include "Node.hpp"
#include "ClosureNumber.hpp"
#include "OpenNumber.h"
#include "Operator.h"
#include "number/Root.h"


namespace expression {

	class OpenNumber;

	template<typename OperatorType>
	class Expression : public Node {
	public:
		Expression() {
		}

		Expression(const expression::Expression<OperatorType> &prototype) {
			*this = prototype;
			m_is_clone = true;
		}

		const Expression &operator=(const Expression &right) {
			Node::operator=(right);
			m_closures = right.m_closures;
			m_opens = right.m_opens;
			m_expressions0 = right.m_expressions0;
			m_expressions1 = right.m_expressions1;
			m_sequence = right.m_sequence;
			m_is_child = right.m_is_child;
			m_is_clone = right.m_is_clone;
			return *this;
		}

		Expression(const expression::ClosureNumber &n) {
			m_closures.push_back(n);
			m_sequence.push_front({ SEQUENCE_TYPE_CLOSURE, m_closures.size() - 1 });
		}
		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const expression::ClosureNumber &n, const ConcreteOperatorType& o, Append ...append) :Expression(append...){
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			CheckLastNode();
			SetNodeOperator<ConcreteOperatorType>();
			m_closures.push_back(n);
			m_sequence.push_front({ SEQUENCE_TYPE_CLOSURE, m_closures.size() - 1 });
		}

		Expression(const expression::OpenNumber &n) {
			m_opens.push_back(n);
			m_sequence.push_front({SEQUENCE_TYPE_OPEN, m_opens.size() - 1 });
		}
		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const expression::OpenNumber &n, const ConcreteOperatorType& o, Append ...append) :Expression(append...) {
			CheckLastNode();
			SetNodeOperator<ConcreteOperatorType>();
			m_opens.push_back(n);
			m_sequence.push_front({ SEQUENCE_TYPE_OPEN, m_opens.size() - 1 });
		}

		template<typename ChildOperatorType>
		Expression(const expression::Expression<ChildOperatorType> &n) {
			AddChild(n);
		}
		template<typename ChildOperatorType, typename ConcreteOperatorType, typename ...Append>
		Expression(const expression::Expression<ChildOperatorType> &n, const ConcreteOperatorType& o, Append ...append) :Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			CheckLastNode();
			SetNodeOperator<ConcreteOperatorType>();
			AddChild(n);
		}

		void Clear() {
			m_expressions0.clear();
			m_expressions1.clear();
			m_closures.clear();
			m_opens.clear();
			m_is_child = false;
			m_is_clone = false;
		}

		void CheckLastNode() {
			if (m_is_clone){
				const expression::Expression<OperatorType> self(*this);
				Clear();
				AddChild(self);
			}
		}

		const std::string OutPutString(size_t pos = 0) const override {
			std::stringstream ss;
			if (m_operator) {
				ss << m_operator->OutPutString(pos);
			}
			if (m_is_child) {
				ss << "(";
			}
			size_t index = 0;
			for (auto seq : m_sequence) {
				ss << GetNode(seq).OutPutString(index++);
			}
			if (m_is_child) {
				ss << ")";
			}
			return ss.str();
		}

		Expression<OperatorType> Collect(size_t count, size_t &completed) {
			Expression<OperatorType> collect(*this);
			if (count == (completed += collect.EliminationOpen(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectExpression(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectClosure(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectOpen(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectClosureExpression(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectOpenExpression(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.EliminationParentheses(count - completed))) {
				return collect;
			}
			return collect;
		}

		std::ostream& Forward(std::ostream& out) const{
			out << *this;
			expression::Expression<OperatorType> collect = *this;
			while (true) {
				size_t completed = 0;
				collect = collect.Collect(1, completed);
				if (completed) {
					std::cout << " --> " << collect;
				}
				else {
					break;
				}
			}
			return out;
		}

		friend Expression<OPERATOR_TYPE_0> operator+(const expression::OpenNumber &number, const expression::OpenNumber &addition);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::OpenNumber &number, const expression::OpenNumber &subtrahend);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::OpenNumber &number, const expression::OpenNumber &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::OpenNumber &number, const expression::OpenNumber &divisor);

		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &addition);

		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend);

		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier);

		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor);

		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &addition);

		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &subtrahend);

		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &multiplier);
		
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &divisor);

		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &addition);
		
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &subtrahend);
		
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &multiplier);

		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::OpenNumber &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::OpenNumber &divisor);

	private:
		
		template<typename ConcreteOperatorType>
		void SetNodeOperator() {
			switch (m_sequence.front().type)
			{
			case SEQUENCE_TYPE_CLOSURE:
				m_closures[m_sequence.front().index].m_operator.reset(new ConcreteOperatorType);
				break;
			case SEQUENCE_TYPE_OPEN:
				m_opens[m_sequence.front().index].m_operator.reset(new ConcreteOperatorType);
				break;
			case SEQUENCE_TYPE_EXP0:
				m_expressions0[m_sequence.front().index].m_operator.reset(new ConcreteOperatorType);
				break;
			case SEQUENCE_TYPE_EXP1:
				m_expressions1[m_sequence.front().index].m_operator.reset(new ConcreteOperatorType);
				break;
			default:
				break;
			}
		}

		std::vector<ClosureNumber> m_closures;

		std::vector<OpenNumber> m_opens;

		std::vector<Expression<OPERATOR_TYPE_0>> m_expressions0;

		std::vector<Expression<OPERATOR_TYPE_1>> m_expressions1;

		enum SEQUENCE_TYPE {
			SEQUENCE_TYPE_CLOSURE,
			SEQUENCE_TYPE_OPEN,
			SEQUENCE_TYPE_EXP0,
			SEQUENCE_TYPE_EXP1
		};

		struct SEQUENCE {
			SEQUENCE_TYPE type = SEQUENCE_TYPE_CLOSURE;
			size_t index = 0;
		};

		std::list<SEQUENCE> m_sequence;

		const expression::Node &GetNode(const SEQUENCE &seq) const{
			switch (seq.type)
			{
			case SEQUENCE_TYPE_CLOSURE:
				return m_closures.at(seq.index);
				break;
			case SEQUENCE_TYPE_OPEN:
				return m_opens.at(seq.index);
				break;
			case SEQUENCE_TYPE_EXP0:
				return m_expressions0.at(seq.index);
				break;
			case SEQUENCE_TYPE_EXP1:
				return m_expressions1.at(seq.index);
				break;
			default:
				return *this;
				break;
			}
		}

		bool m_is_child = false;
		bool m_is_clone = false;

		template<typename OperatorType> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_0> friend class Expression;
		template<typename OPERATOR_TYPE_1> friend class Expression;

		void AddChild(const expression::Expression<OPERATOR_TYPE_0> &child) {
			m_expressions0.push_back(child);
			m_sequence.push_front({ SEQUENCE_TYPE_EXP0, m_expressions0.size() - 1 });
			m_expressions0.back().SetChild();
		}
		void AddChild(const expression::Expression<OPERATOR_TYPE_1> &child) {
			m_expressions1.push_back(child);
			m_sequence.push_front({SEQUENCE_TYPE_EXP1, m_expressions1.size() - 1 });
			m_expressions1.back().SetChild();
		}

		size_t EliminationOpen(size_t count) {
			size_t completed = 0;
			for (size_t index = 0; index < m_opens.size();) {
				size_t reverseIndex = m_opens.size() - 1 - index;
				const OpenNumber &open = m_opens[reverseIndex];
				if (open.Value().IsFraction()) {
					ClosureNumber closure(open.Value().ReductionCoefficient());
					closure.SetOperator(open.m_operator);
					m_closures.push_back(closure);
					for (auto node = m_sequence.begin(); node != m_sequence.end(); ++node) {
						if (&GetNode(*node) == &open) {
							node->type = SEQUENCE_TYPE_CLOSURE;
							node->index = m_closures.size() - 1;
							break;
						}
					}
					m_opens.erase(m_opens.cbegin() + reverseIndex);
					if (++completed == count) {
						return completed;
					}
				}
				else {
					++index;
				}
			}
			return completed;
		}

		size_t CollectClosure(size_t count) {
			if (2 > m_closures.size()) {
				return 0;
			}
			size_t completed = -1;
			ClosureNumber collect(number::Complex(OperatorType::GetLevel(), 0));
			for (size_t index = 0; index < m_closures.size(); ) {
				size_t reverseIndex = m_closures.size() - 1 - index;
				const ClosureNumber &closure = m_closures[reverseIndex];
				if (!closure.m_operator) {
					switch (OperatorType::GetLevel())
					{
					case 0:
						collect += closure;
						break;
					case 1:
						collect *= closure;
						break;
					default:
						break;
					}
				}
				else {
					switch (closure.m_operator->GetFlag())
					{
					case OPERATOR_TYPE_FLAG_ADD:
						collect += closure;
						break;
					case OPERATOR_TYPE_FLAG_SUB:
						collect -= closure;
						break;
					case OPERATOR_TYPE_FLAG_MUL:
						collect *= closure;
						break;
					case OPERATOR_TYPE_FLAG_DIV:
						collect /= closure;
						break;
					default:
						break;
					}
				}
				DeleteClosure(reverseIndex);
				if (++completed == count || m_closures.empty()) {
					break;
				}
			}
			m_closures.push_back(collect);
			m_sequence.push_front({SEQUENCE_TYPE_CLOSURE, m_closures.size() - 1});
			return completed;
		}

		size_t CollectOpen(size_t count) {
			if (2 > m_opens.size()) {
				return 0;
			}
			size_t completed = 0;
			for (size_t i = 0; i < m_opens.size() - 1;) {
				size_t reverseI = m_opens.size() - 1 - i;
				bool isCollected = false;
				expression::OpenNumber collect(number::Root(0, 1));
				for (size_t j = i + 1; j < m_opens.size(); ++j) {
					size_t reverseJ = m_opens.size() - 1 - j;
					const OpenNumber &left = m_opens[reverseI];
					const OpenNumber &right = m_opens[reverseJ];
					switch (OperatorType::GetLevel())
					{
					case 0:
						if (left.Collect0(right, collect)) {
							DeleteOpen(reverseI);
							DeleteOpen(reverseJ);
							isCollected = true;
							break;
						}
						break;
					case 1:
						if (left.Collect1(right, collect)) {
							DeleteOpen(reverseI);
							DeleteOpen(reverseJ);
							isCollected = true;
							break;
						}
						break;
					default:
						break;
					}

				}
				if (isCollected) {
					if (!collect.Value().IsFraction()) {
						m_opens.push_back(collect);
						m_sequence.push_front({ SEQUENCE_TYPE_OPEN, m_opens.size() - 1 });
					}
					else {
						m_closures.push_back(collect.Value().ReductionCoefficient());
						m_sequence.push_front({ SEQUENCE_TYPE_CLOSURE, m_closures.size() - 1 });
					}
					if (++completed == count) {
						return completed;
					}
				}
				else {
					++i;
				}
			}
			return completed;
		}

		size_t CollectExpression(size_t count) {
			size_t completed = 0;
			for (size_t index = 0; index < m_expressions0.size();) {
				size_t reverseIndex = m_expressions0.size() - 1 - index;
				Expression<OPERATOR_TYPE_0> &exp = m_expressions0[reverseIndex];
				exp = exp.Collect(1, completed);
				if (CheckSingleChild(exp)) {
					DeleteExp0(reverseIndex);
				}
				else {
					++ index;
				}
				if (completed == count) {
					return completed;
				}
			}
			for (size_t index = 0; index < m_expressions1.size();) {
				size_t reverseIndex = m_expressions1.size() - 1 - index;
				Expression<OPERATOR_TYPE_1> &exp = m_expressions1[reverseIndex];
				exp = exp.Collect(1, completed);
				if (CheckSingleChild(exp)) {
					DeleteExp1(reverseIndex);
				}
				else {
					++ index;
				}
				if (completed == count) {
					return completed;
				}
			}
			return completed;
		}

		size_t CollectClosureExpression(size_t count) {
			size_t completed = 0;
			return completed;
		}

		size_t CollectOpenExpression(size_t count) {
			size_t completed = 0;
			return completed;
		}

		size_t EliminationParentheses(size_t count) {
			size_t completed = 0;
			for (size_t index = 0; index < m_expressions0.size();) {
				Expression<OPERATOR_TYPE_0> &exp = m_expressions0[index];
				completed += exp.EliminationParentheses(count - completed);
				if (CheckSingleChild(exp)) {
					DeleteExp0(index);
				}
				else {
					++index;
				}
				if (completed == count) {
					return completed;
				}
			}
			for (size_t index = 0; index < m_expressions1.size();) {
				Expression<OPERATOR_TYPE_1> &exp = m_expressions1[index];
				completed += exp.EliminationParentheses(count - completed);
				if (CheckSingleChild(exp)) {
					DeleteExp1(index);
				}
				else {
					++index;
				}
				if (completed == count) {
					return completed;
				}
			}
			return completed;
		}

		bool IsSingle() const{
			size_t count = 0;
			for (auto node : m_sequence) {
				++count;
			}
			return 1 == count;
		}

		template<typename OtherOperatorType>
		void Replace(const Expression<OtherOperatorType> &other) {
			for (auto exp : other.m_expressions0) {
				m_expressions0.push_back(exp);
				for (auto node = m_sequence.begin(); node != m_sequence.end(); ++node) {
					if (&GetNode(*node) == &other) {
						node->type = SEQUENCE_TYPE_EXP0;
						node->index = m_expressions0.size() - 1;
						m_expressions0.back().SetOperator(other.m_operator);
						return;
					}
				}
			}
			for (auto exp : other.m_expressions1) {
				m_expressions1.push_back(exp);
				for (auto node = m_sequence.begin(); node != m_sequence.end(); ++node) {
					if (&GetNode(*node) == &other) {
						node->type = SEQUENCE_TYPE_EXP1;
						node->index = m_expressions1.size() - 1;
						m_expressions1.back().SetOperator(other.m_operator);
						return;
					}
				}
			}
			for (auto closure : other.m_closures) {
				m_closures.push_back(closure);
				for (auto node = m_sequence.begin(); node != m_sequence.end(); ++node) {
					if (&GetNode(*node) == &other) {
						node->type = SEQUENCE_TYPE_CLOSURE;
						node->index = m_closures.size() - 1;
						m_closures.back().SetOperator(other.m_operator);
						return;
					}
				}
			}
			for (auto open : other.m_opens) {
				m_opens.push_back(open);
				for (auto node = m_sequence.begin(); node != m_sequence.end(); ++node) {
					if (&GetNode(*node) == &other) {
						node->type = SEQUENCE_TYPE_OPEN;
						node->index = m_opens.size() - 1;
						m_opens.back().SetOperator(other.m_operator);
						return;
					}
				}
			}
		}

		template<typename ChildOperatorType>
		bool CheckSingleChild(const Expression<ChildOperatorType> &Child) {
			if (Child.IsSingle()) {
				Replace(Child);
				return true;
			}
			else {
				return false;
			}
		}


		Expression<OperatorType> SetChild() {
			m_is_child = true;
			return *this;
		}


		void DeleteClosure(size_t index) {
			m_closures.erase(m_closures.cbegin() + index);
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_CLOSURE == itor->type && index == itor->index) {
					itor = m_sequence.erase(itor);
					break;
				}
			}
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_CLOSURE == itor->type && index < itor->index) {
					itor->index--;
				}
			}
		}
		void DeleteOpen(size_t index) {
			m_opens.erase(m_opens.cbegin() + index);
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_OPEN == itor->type && index == itor->index) {
					itor = m_sequence.erase(itor);
					break;
				}
			}
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_OPEN == itor->type && index < itor->index) {
					itor->index--;
				}
			}
		}
		void DeleteExp0(size_t index) {
			m_expressions0.erase(m_expressions0.cbegin() + index);
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_EXP0 == itor->type && index == itor->index) {
					itor = m_sequence.erase(itor);
					break;
				}
			}
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_EXP0 == itor->type && index < itor->index) {
					itor->index--;
				}
			}
		}
		void DeleteExp1(size_t index) {
			m_expressions1.erase(m_expressions1.cbegin() + index);
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_EXP1 == itor->type && index == itor->index) {
					itor = m_sequence.erase(itor);
					break;
				}
			}
			for (auto itor = m_sequence.begin(); itor != m_sequence.end(); ++itor) {
				if (SEQUENCE_TYPE_EXP1 == itor->type && index < itor->index) {
					itor->index--;
				}
			}
		}
	};


}

#endif