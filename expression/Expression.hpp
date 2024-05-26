#ifndef __EXPRESSION_EXPRESSION_HPP__
#define __EXPRESSION_EXPRESSION_HPP__
#include <list>
#include <memory>
#include <iostream>
#include <stack>
#include <map>
#include <sstream>
#include <variant>
#include "Node.hpp"
#include "ClosureNumber.hpp"
#include "OpenNumber.h"
#include "Operator.h"
#include "number/Root.h"


namespace expression {

#define ExpressionNodes std::list<std::variant<ClosureNumber, OpenNumber, Expression<OPERATOR_TYPE_0>, Expression<OPERATOR_TYPE_1>>>

	class OpenNumber;

	template<typename OperatorType>
	class Expression : public Node {
	public:

		Expression() {}

		Expression(const expression::Expression<OperatorType> &prototype){
			*this = prototype;
		}

		Expression(const expression::Expression<OperatorType> &prototype, OPERATOR_TYPE_FLAG flag) {
			*this = prototype;
			SetOperator(flag);
		}

		const Expression &operator=(const Expression &right) {
			Node::operator=(right);
			m_nodes = right.m_nodes;
			m_is_child = right.m_is_child;
			return *this;
		}

		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::ClosureNumber &n, Append ...append) :Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddClosure(n, o);
		}
		template<typename ...Append>
		Expression(const expression::ClosureNumber &n, Append ...append) :Expression(append...){
			AddClosure(n);
		}

		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::OpenNumber &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddOpen(n, o);
		}
		template<typename ...Append>
		Expression(const expression::OpenNumber &n, Append ...append) :Expression(append...) {
			AddOpen(n);
		}

		template<typename ConcreteOperatorType, typename ChildOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::Expression<ChildOperatorType> &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddChild(n, o);
		}
		template<typename ChildOperatorType, typename ...Append>
		Expression(const expression::Expression<ChildOperatorType> &n, Append ...append) :Expression(append...) {
			AddChild(n);
		}

		const std::string OutPutString(size_t pos = 0) const override {
			std::stringstream ss;
			ss << m_operator->OutPutString(pos);
			if (m_is_child) {
				ss << "(";
			}
			size_t index = 0;
			for (auto& node : m_nodes) {
				std::visit([&](auto &&n) {
					ss << n.OutPutString(index++);
				}, node);
			}
			if (m_is_child) {
				ss << ")";
			}
			return ss.str();
		}

		Expression<OperatorType> Collect(size_t count, size_t &completed) const{
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
			if (count == (completed += collect.EliminationChild(count - completed))) {
				return collect;
			}
			return collect;
		}

		std::ostream& CollectForward(std::ostream& out) const{
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
		
		ExpressionNodes m_nodes;

		bool m_is_child = false;

		template<typename OperatorType> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_0> friend class Expression;
		template<typename OPERATOR_TYPE_1> friend class Expression;

		void AddClosure(const expression::ClosureNumber &n) {
			m_nodes.push_front(n);
		}

		template<typename ConcreteOperatorType>
		void AddClosure(const expression::ClosureNumber &n, const ConcreteOperatorType &o){
			m_nodes.push_front(expression::ClosureNumber(n, o.GetFlag()));
		}

		void AddOpen(const expression::OpenNumber &n) {
			m_nodes.push_front(n);
		}

		template<typename ConcreteOperatorType>
		void AddOpen(const expression::OpenNumber &n, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::OpenNumber(n, o.GetFlag()));
		}

		void AddChild(const expression::Expression<OPERATOR_TYPE_0> &child) {
			m_nodes.push_front(child);
			std::get<expression::Expression<OPERATOR_TYPE_0>>(m_nodes.front()).SetChild();
		}

		template<typename ConcreteOperatorType>
		void AddChild(const expression::Expression<OPERATOR_TYPE_0> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<OPERATOR_TYPE_0>(child, o.GetFlag()));
			std::get<expression::Expression<OPERATOR_TYPE_0>>(m_nodes.front()).SetChild();
		}
		
		void AddChild(const expression::Expression<OPERATOR_TYPE_1> &child) {
			m_nodes.push_front(expression::Expression<OPERATOR_TYPE_1>(child));
			std::get<expression::Expression<OPERATOR_TYPE_1>>(m_nodes.front()).SetChild();
		}

		template<typename ConcreteOperatorType>
		void AddChild(const expression::Expression<OPERATOR_TYPE_1> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<OPERATOR_TYPE_1>(child, o.GetFlag()));
			std::get<expression::Expression<OPERATOR_TYPE_1>>(m_nodes.front()).SetChild();
		}

		size_t EliminationOpen(size_t count) {
			std::vector<ExpressionNodes::iterator> opens;
			GetAll<expression::OpenNumber>(opens);
			size_t completed = 0;
			for (size_t index = 0; index < opens.size(); ++index) {
				const OpenNumber &open = std::get<expression::OpenNumber>(*opens[index]);
				if (open.Value().IsFraction()) {
					ClosureNumber closure(open.Value().ReductionCoefficient(), open.Flag());
					*opens[index] = closure;
					if (++completed == count) {
						return completed;
					}
				}
			}
			return completed;
		}

		size_t CollectClosure(size_t count) {
			std::vector<ExpressionNodes::iterator> closures;
			GetAll<expression::ClosureNumber>(closures);
			if (2 > closures.size()) {
				return 0;
			}
			size_t completed = 0;
			expression::ClosureNumber &collect = std::get<expression::ClosureNumber>(*closures.front());
			typename std::vector<ExpressionNodes::iterator>::iterator itor = closures.begin();
			while (++itor != closures.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				switch (closure.Flag())
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
				m_nodes.erase(*itor);
				if (++completed == count) {
					break;
				}
			}
			return completed;
		}

		size_t CollectOpen(size_t count) {
			std::vector<ExpressionNodes::iterator> opens;
			GetAll<expression::OpenNumber>(opens);
			if (2 > opens.size()) {
				return 0;
			}
			size_t completed = 0;
			for (size_t index = 0; index < opens.size() - 1; ++index) {
				const std::optional<expression::OpenNumber> collect(CollectOpen(opens, index));
				if (collect.has_value()) {
					if (!collect.value().Value().IsFraction()) {
						AddOpen(collect.value());
					}
					else {
						AddClosure(collect.value().Value().ReductionCoefficient());
					}
					if (++completed == count) {
						return completed;
					}
				}
			}
			return completed;
		}

		size_t CollectExpression(size_t count) {
			size_t completed = 0;
			if (count == (completed += CollectOperatorTypeExpression<OPERATOR_TYPE_0>(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectOperatorTypeExpression<OPERATOR_TYPE_1>(count - completed))) {
				return completed;
			}
			return completed;
		}

		size_t EliminationChild(size_t count) {
			size_t completed = 0;
			if (count == (completed += EliminationOperatorTypeChild<OPERATOR_TYPE_0>(count - completed))) {
				return completed;
			}
			if (count == (completed += EliminationOperatorTypeChild<OPERATOR_TYPE_1>(count - completed))) {
				return completed;
			}
			return completed;
		}

		bool IsSingle() const{
			return 1 == m_nodes.size();
		}

		template<typename ChildOperatorType>
		void Replace(const ExpressionNodes::iterator child) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*child);
			const auto &nodes = exp.m_nodes;
			for (auto itor = nodes.rbegin(); itor != nodes.rend(); itor++) {
				typename ExpressionNodes::iterator newItor = m_nodes.insert(child, *itor);
				std::visit([&](auto &&n) {
					n.SuperpositionFlag<OperatorType>(exp.Flag(), newItor == m_nodes.cbegin());
				}, *newItor);
			}
			m_nodes.erase(child);
		}

		template<typename ChildOperatorType>
		bool CheckCollectChild(const ExpressionNodes::iterator child) {
			if (std::get<Expression<ChildOperatorType>>(*child).IsSingle()) {
				Replace<ChildOperatorType>(child);
				return true;
			}
			else if (typeid(ChildOperatorType) == typeid(OperatorType)) {
				Replace<ChildOperatorType>(child);
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


		template<typename NodeType>
		NodeType *GetFirst() {
			for (auto &node : m_nodes){
				if (NodeType *typeNode = std::get_if<NodeType>(&node)) {
					return typeNode;
				}
			}
			return nullptr;
		}

		template<typename NodeType>
		void GetAll(std::vector<ExpressionNodes::iterator> &closures) {
			for (auto itor = m_nodes.begin(); itor != m_nodes.end(); ++ itor) {
				if (NodeType *node = std::get_if<NodeType>(&*itor)) {
					closures.push_back(itor);
				}
			}
		}

		template<typename ChildOperatorType>
		size_t CollectOperatorTypeExpression(size_t count) {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<expression::Expression<ChildOperatorType>>(exps);
			size_t completed = 0;
			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType> &exp = std::get<Expression<ChildOperatorType>>(*exps[index]);
				exp = exp.Collect(1, completed);
				CheckCollectChild<ChildOperatorType>(exps[index]);
				if (completed == count) {
					return completed;
				}
			}
			return completed;
		}

		template<typename ChildOperatorType>
		size_t EliminationOperatorTypeChild(size_t count) {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<expression::Expression<ChildOperatorType>>(exps);
			size_t completed = 0;
			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType> &exp = std::get<Expression<ChildOperatorType>>(*exps[index]);
				completed += exp.EliminationChild(count - completed);
				CheckCollectChild<ChildOperatorType>(exps[index]);
				if (completed == count) {
					return completed;
				}
			}
			return completed;
		}

		std::optional<expression::OpenNumber> CollectOpen(const std::vector<ExpressionNodes::iterator> &opens, size_t start) {
			for (size_t index = start + 1; index < opens.size(); ++index) {
				const OpenNumber &left = std::get<expression::OpenNumber>(*opens[start]);
				const OpenNumber &right = std::get<expression::OpenNumber>(*opens[index]);
				const std::optional<expression::OpenNumber> collect(left.Collect(right, OperatorType::GetLevel()));
				if (collect.has_value()) {
					m_nodes.erase(opens[start]);
					m_nodes.erase(opens[index]);
					return collect;
				}
			}
			return std::nullopt;
		}
	};


}

#endif