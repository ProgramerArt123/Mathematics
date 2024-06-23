#ifndef __EXPRESSION_EXPRESSION_HPP__
#define __EXPRESSION_EXPRESSION_HPP__


#include <cassert>

#include <list>
#include <memory>
#include <iostream>
#include <stack>
#include <map>
#include <sstream>
#include <variant>
#include <functional>
#include <set>
#include <algorithm>
#include <iterator>

#include "Node.hpp"
#include "ClosureNumber.hpp"
#include "OpenNumber.h"
#include "Symbol.h"
#include "Operator.h"
#include "number/Root.h"


namespace expression {

	template<typename OperatorType>
	class Expression : public Node {
	public:

		typedef std::list<std::variant<ClosureNumber, Symbol, Expression<OPERATOR_TYPE_0>, Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>>> ExpressionNodes;

		Expression() {
			InitPolymorphism();
		}

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
			InitPolymorphism();
			return *this;
		}

		bool operator==(const Expression<OperatorType> &other) const {
			if (m_nodes.size() != other.m_nodes.size()) {
				return false;
			}
			if (!m_polymorphism->IsEqual(other.m_nodes)) {
				return false;
			}
			for (auto& i : m_nodes) {
				bool hasEqual = false;
				for (auto& j : other.m_nodes) {
					std::visit([&hasEqual](auto &&i, auto &&j) {
						hasEqual = i.IsEqual(j);
					}, i, j);
					if (hasEqual) {
						break;
					}
				}
				if (!hasEqual) {
					return false;
				}
			}
			return true;
		}

		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::ClosureNumber &n, Append ...append) :Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddClosure(n, o);
		}
		template<typename ...Append>
		Expression(const expression::ClosureNumber &n, Append ...append) :Expression(append...){
			AddClosure(n);
			InitPolymorphism();
		}

		template<typename ConcreteOperatorType, typename ChildOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::Expression<ChildOperatorType> &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddChild(n, o);
		}
		template<typename ChildOperatorType, typename ...Append>
		Expression(const expression::Expression<ChildOperatorType> &n, Append ...append) :Expression(append...) {
			AddChild(n);
			InitPolymorphism();
		}

		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::Symbol &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddSymbol(n, o);
		}
		template<typename ...Append>
		Expression(const expression::Symbol &n, Append ...append) : Expression(append...) {
			AddSymbol(n);
			InitPolymorphism();
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
		
		bool IsEqual(const Node &other) const override {
			if (!Node::IsEqual(other)) {
				return false;
			}
			const Expression<OperatorType> &otherExp = dynamic_cast<const Expression<OperatorType>&>(other);
			return *this == otherExp;
		}

		bool EqualZero() const override{
			for (auto &node : m_nodes) {
				bool equalZero = false;
				std::visit([&equalZero](auto &&n) {
					equalZero = n.EqualZero();
				}, node);
				if (!equalZero) {
					return false;
				}
			}
			return true;
		}
		bool EqualOne() const override {
			if (1 != m_nodes.size()) {
				return false;
			}
			bool equalOne = false;
			std::visit([&equalOne](auto &&n) {
				equalOne = n.EqualOne();
			}, m_nodes.front());
			return equalOne;
		}
		Expression<OperatorType> Collect(size_t count, size_t &completed) const{
			Expression<OperatorType> collect(*this);
			if (count == (completed += collect.CollectChild(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectSpecial(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectClosure(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.ReduceOpen(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.EliminationChild(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectCommon(count - completed))) {
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
			out << std::endl;
			return out;
		}

		Expression<OperatorType> Expand(size_t count, size_t &completed) const {
			Expression<OperatorType> expand(*this);
			return expand;
		}

		std::ostream& ExpandForward(std::ostream& out) const {
			out << *this;
			expression::Expression<OperatorType> expand = *this;
			while (true) {
				size_t completed = 0;
				expand = expand.Expand(1, completed);
				if (completed) {
					std::cout << " --< " << expand;
				}
				else {
					break;
				}
			}
			return out;
		}

		static Expression<OPERATOR_TYPE_1> Absorb(const number::Fraction &number);
		static Expression<OPERATOR_TYPE_1> Absorb(const number::Imaginary &number);
		static Expression<OPERATOR_TYPE_0> Absorb(const number::Complex &number);
		static Expression<OPERATOR_TYPE_2> Absorb(const number::Root &number);
		
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &addition);

		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend);

		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier);

		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor);

		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &addition);
		friend Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &addition);

		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &subtrahend);
		friend Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &subtrahend);

		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &multiplier);
		friend Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &multiplier);
		
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &divisor);
		friend Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &divisor);

	private:
		
		ExpressionNodes m_nodes;

		bool m_is_child = false;

		template<typename OperatorType> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_0> friend class Expression;
		template<typename OPERATOR_TYPE_1> friend class Expression;
		template<typename OPERATOR_TYPE_2> friend class Expression;

		void AddClosure(const expression::ClosureNumber &n) {
			m_nodes.push_front(expression::ClosureNumber(n, OperatorType::FLAG));
		}

		template<typename ConcreteOperatorType>
		void AddClosure(const expression::ClosureNumber &n, const ConcreteOperatorType &o){
			m_nodes.push_front(expression::ClosureNumber(n, o.GetFlag()));
		}
		
		template<typename AbstractOperatorType>
		void AddChild(const expression::Expression<AbstractOperatorType> &child) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, OperatorType::FLAG).SetChild());
		}

		template<typename AbstractOperatorType, typename ConcreteOperatorType>
		void AddChild(const expression::Expression<AbstractOperatorType> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, o.GetFlag()).SetChild());
		}

		void AddSymbol(const expression::Symbol &s) {
			m_nodes.push_front(expression::Symbol(s, OperatorType::FLAG));
		}

		template<typename ConcreteOperatorType>
		void AddSymbol(const expression::Symbol &s, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Symbol(s, o.GetFlag()));
		}

		std::optional<ClosureNumber> GetIntegerBase() {
			if (ClosureNumber *base = std::get_if<ClosureNumber>(&m_nodes.front())) {
				return *base;
			}
			else {
				return std::nullopt;
			}
		}
		
		std::pair<size_t, bool> CollectExp2(size_t count, std::function<bool(expression::ClosureNumber &, const expression::ClosureNumber &, size_t &)> factor) {
			if (!GetIntegerBase().has_value()) {
				return std::make_pair(0, false);
			}
			std::vector<ExpressionNodes::iterator> integers;
			GetAll<expression::ClosureNumber>(integers, [](const expression::ClosureNumber &node) {return true; });
			if (2 > integers.size()) {
				return std::make_pair(0, false);
			}
			size_t completed = 0;
			expression::ClosureNumber &collect = std::get<expression::ClosureNumber>(*integers.front());
			typename std::vector<ExpressionNodes::iterator>::iterator itor = integers.begin();
			size_t reciprocalsCount = 0;
			while (++itor != integers.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				if (!factor(collect, closure, reciprocalsCount)) {
					continue;
				}
				m_nodes.erase(*itor);
				if (++completed == count) {
					break;
				}
			}
			if (1 == reciprocalsCount % 2) {
				if (1 == m_nodes.size()) {
					AddChild(Expression<OPERATOR_TYPE_1>(ClosureNumber(1), OPERATOR_TYPE_DIV(), collect));
					m_nodes.erase(m_nodes.cbegin());
				}
				else {
					std::visit([](auto &&n) {
						n.Opposite();
					}, m_nodes.back());
				}
			}
			return std::make_pair(completed, false);
		}

		std::pair<size_t, bool> CollectPower(size_t count) {
			return CollectExp2(count, [](expression::ClosureNumber &collect, const expression::ClosureNumber &closure, size_t &reciprocalsCount) {
				switch (closure.Flag())
				{
				case OPERATOR_TYPE_FLAG_POWER:
				{
					const number::Fraction &power = number::Fraction::Power(collect.Value(), closure.Value());
					if (power.IsInteger()) {
						collect = power.Numerator();
					}
					else {
						collect = power.Denominator();
						++reciprocalsCount;
					}
					return true;
				}
				break;
				default:
					return false;
					break;
				}
			});
		}

		std::pair<size_t, bool> CollectRoot(size_t count) {
			return CollectExp2(count, [](expression::ClosureNumber &collect, const expression::ClosureNumber &closure, size_t &reciprocalsCount) {
				switch (closure.Flag())
				{
				case OPERATOR_TYPE_FLAG_ROOT:
				{
					const number::Root root(collect.Value(), closure.Value());
					if (root.IsFraction()) {
						const number::Fraction &coefficient = root.ReductionCoefficient();
						if (coefficient.IsInteger()) {
							collect = coefficient.Numerator();
						}
						else {
							collect = coefficient.Denominator();
							++reciprocalsCount;
						}
						return true;
					}
					else {
						return false;
					}
				}
				break;
				default:
					return false;
					break;
				}
			});
		}

		size_t CollectAllClosure(size_t count) {
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
					continue;
					break;
				}
				m_nodes.erase(*itor);
				if (++completed == count) {
					break;
				}
			}
			return completed;
		}

		size_t CollectSpecial(size_t count) {
			if (1 == m_nodes.size()) {
				return 0;
			}
			std::vector<ExpressionNodes::const_iterator> nodes;
			GetAll(nodes);
			size_t completed = 0;
			for (auto &node : nodes) {
				bool equalZero = false, equalOne = false;
				std::visit([&equalZero, &equalOne](auto &&n) {
					(equalZero = n.EqualZero()) || (equalOne = n.EqualOne());
				}, *node);
				if (equalZero || equalOne) {
					const std::pair<bool, bool> &collect = m_polymorphism->CollectSpecial(node);
					if (collect.first) {
						completed = 1;
					}
					if (!collect.second) {
						break;
					}
				}
			}
			return completed;
		}

		size_t CollectClosure(size_t count) {
			size_t completed = 0;
			if (count == (completed += CollectPowerClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectRootClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectAllClosure(count - completed))) {
				return completed;
			}
			return completed;
		}

		size_t ReduceOpen(size_t count) {
			std::vector<ExpressionNodes::iterator> exp2s;
			GetAll<Expression<OPERATOR_TYPE_2>>(exp2s);
			for (auto &exp2 : exp2s) {
				const auto &exp = std::get<Expression<OPERATOR_TYPE_2>>(*exp2);
				if (2 != exp.m_nodes.size()) {
					continue;
				}
				auto base = std::get<expression::ClosureNumber>(exp.m_nodes.front());
				auto exponent = std::get<expression::ClosureNumber>(exp.m_nodes.back());
				if (OPERATOR_TYPE_FLAG_ROOT != exponent.Flag()) {
					continue;
				}
				const number::Root root(base.Value(), exponent.Value());
				if (root.ReductionBase() == base.Value() && 
					root.ReductionCoefficient() == number::Fraction(1)) {
					continue;
				}
				const Expression<OPERATOR_TYPE_2> reduction(root.ReductionBase().Numerator(),
					OPERATOR_TYPE_ROOT(), root.Exponent().Numerator());
				*exp2 = Expression<OPERATOR_TYPE_1>(root.ReductionCoefficient().Numerator(), OPERATOR_TYPE_MUL(), reduction);
				return 1;
			}
			return 0;
		}

		size_t CollectPowerClosure(size_t count) {
			size_t completed = 0;
			while (true) {
				const std::pair<size_t, bool> &intCompleted = CollectPower(count - completed);
				if (count == (completed += intCompleted.first)) {
					return completed;
				}
				if (!intCompleted.second) {
					break;
				}
			}
			return completed;
		}

		size_t CollectRootClosure(size_t count) {
			size_t completed = 0;
			while (true) {
				const std::pair<size_t, bool> &intCompleted = CollectRoot(count - completed);
				if (count == (completed += intCompleted.first)) {
					return completed;
				}
				if (!intCompleted.second) {
					break;
				}
			}
			return completed;
		}

		size_t CollectChild(size_t count) {
			size_t completed = 0;
			if (count == (completed += CollectOperatorTypeChild<OPERATOR_TYPE_0>(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectOperatorTypeChild<OPERATOR_TYPE_1>(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectOperatorTypeChild<OPERATOR_TYPE_2>(count - completed))) {
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
			if (count == (completed += EliminationOperatorTypeChild<OPERATOR_TYPE_2>(count - completed))) {
				return completed;
			}
			return completed;
		}

		size_t CollectCommon(size_t count) {
			std::vector<ExpressionNodes::iterator> exps;
			m_polymorphism->GetChildren(exps);
			if (2 > exps.size()) {
				return 0;
			}
			size_t completed = 0;
			for (auto itor = exps.begin(); itor != exps.end();) {
				if (m_polymorphism->CollectCommonChild(exps, itor)) {
					m_nodes.erase(*itor);
					itor = exps.erase(itor);
					++completed;
				}
				else {
					++itor;
				}
				if (completed == count) {
					return completed;
				}
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
					n.SuperpositionFlag(exp.Operator());
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
			if constexpr (std::is_same<ChildOperatorType, OperatorType>::value) {
				Replace<ChildOperatorType>(child);
				return true;
			}
			return false;
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
		void GetAll(std::vector<ExpressionNodes::const_iterator> &nodes, std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) const{
			for (auto itor = m_nodes.cbegin(); itor != m_nodes.cend(); ++ itor) {
				if (const NodeType *node = std::get_if<NodeType>(&*itor)) {
					if (filter(*node)) {
						nodes.push_back(itor);
					}
				}
			}
		}

		void GetAll(std::vector<ExpressionNodes::const_iterator> &nodes) const {
			for (auto itor = m_nodes.cbegin(); itor != m_nodes.cend(); ++itor) {
				nodes.push_back(itor);
			}
		}

		template<typename NodeType>
		void GetAll(std::vector<ExpressionNodes::iterator> &nodes, std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			for (auto itor = m_nodes.begin(); itor != m_nodes.end(); ++itor) {
				if (const NodeType *node = std::get_if<NodeType>(&*itor)) {
					if (filter(*node)) {
						nodes.push_back(itor);
					}
				}
			}
		}
				
		template<typename ParentOperatorType>
		std::optional<expression::Expression<OperatorType>> CollectCommon(const Expression<OperatorType> &right) const {
			std::vector<ExpressionNodes::const_iterator> leftChildren;
			GetAll(leftChildren);
			std::vector<ExpressionNodes::const_iterator> rightChildren;
			right.GetAll(rightChildren);
			std::vector<ExpressionNodes::const_iterator> commons;
			for (auto leftChild = leftChildren.begin(); leftChild != leftChildren.end(); ) {
				if ([&] {
					for (auto rightChild = rightChildren.begin(); rightChild != rightChildren.end(); ++rightChild) {
						bool isEqual = false;
						std::visit([&](auto &&n0, auto &&n1) {
							if (isEqual = n0.IsEqual(n1)) {
								commons.push_back(*leftChild);
								rightChildren.erase(rightChild);
							}
						}, **leftChild, **rightChild);
						if (isEqual) {
							return true;
						}
					}
					return false;
				}()) {
					leftChild = leftChildren.erase(leftChild);
				}
				else {
					++leftChild;
				}
			}

			m_polymorphism->ProcessSpecial(commons);

			if (commons.empty()) {
				return std::nullopt;
			}
			Expression<OperatorType> collect;
			for (auto &common : commons) {
				collect.m_nodes.push_back(*common);
			}
			collect.m_nodes.push_back(m_polymorphism->BuildCommon(leftChildren, rightChildren, right.Flag()).SetChild());
			return collect;
		}

		template<typename ChildOperatorType>
		size_t CollectOperatorTypeChild(size_t count) {
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
				CheckCollectChild<ChildOperatorType>(exps.at(index));
				if (completed == count) {
					return completed;
				}
			}
			return completed;
		}

		protected:

			class Polymorphism {
			public:
				virtual std::pair<bool, bool> CollectSpecial(ExpressionNodes::const_iterator node) = 0;
				virtual void GetChildren(std::vector<ExpressionNodes::iterator> &exps) = 0;
				virtual bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
				virtual void ProcessSpecial(std::vector<ExpressionNodes::const_iterator> &exps) = 0;
				virtual Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) = 0;
				virtual bool IsEqual(const ExpressionNodes &other) const = 0;
			};

			class Polymorphism0 : public Polymorphism {
			public:
				Polymorphism0(Expression<OPERATOR_TYPE_0> &exp);
				std::pair<bool, bool> CollectSpecial(ExpressionNodes::const_iterator node) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				void ProcessSpecial(std::vector<ExpressionNodes::const_iterator> &exps) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const ExpressionNodes &other) const override;

				Expression<OPERATOR_TYPE_1> LevelDown(ExpressionNodes::iterator exp2);
			private:
				Expression<OPERATOR_TYPE_0> &m_exp;
			};

			class Polymorphism1 : public Polymorphism {
			public:
				Polymorphism1(Expression<OPERATOR_TYPE_1> &exp);
				std::pair<bool, bool> CollectSpecial(ExpressionNodes::const_iterator node) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				void ProcessSpecial(std::vector<ExpressionNodes::const_iterator> &exps) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const ExpressionNodes &other) const override;
			
			private:
				Expression<OPERATOR_TYPE_1> &m_exp;
			};

			class Polymorphism2 : public Polymorphism {
			public:
				Polymorphism2(Expression<OPERATOR_TYPE_2> &exp);
				std::pair<bool, bool> CollectSpecial(ExpressionNodes::const_iterator node) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				void ProcessSpecial(std::vector<ExpressionNodes::const_iterator> &exps) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const ExpressionNodes &other) const override;
			
			private:
				Expression<OPERATOR_TYPE_2> &m_exp;
			};

			friend class Polymorphism;
			friend class Polymorphism0;
			friend class Polymorphism1;
			friend class Polymorphism2;

			std::unique_ptr<Polymorphism> m_polymorphism;

			void InitPolymorphism() {
				if (!m_polymorphism) {
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_0>::value) {
						m_polymorphism = std::make_unique<Polymorphism0>(*this);
					}
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_1>::value) {
						m_polymorphism = std::make_unique<Polymorphism1>(*this);
					}
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_2>::value) {
						m_polymorphism = std::make_unique<Polymorphism2>(*this);
					}
				}
			}
	};

}

#endif