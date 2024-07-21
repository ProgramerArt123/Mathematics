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

		typedef std::variant<ClosureNumber, Symbol, Expression<OPERATOR_TYPE_0>, Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>> ExpressionNode;
		typedef std::list<ExpressionNode> ExpressionNodes;

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
			if (!m_polymorphism->IsEqual(*Visit(other.m_nodes.front()))) {
				return false;
			}
			for (auto& i : m_nodes) {
				bool hasEqual = false;
				for (auto& j : other.m_nodes) {
					hasEqual = Visit(i)->IsEqual(*Visit(j));
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
			InitPolymorphism();
			m_polymorphism->MarkFirst(&AddClosure(n));
		}

		template<typename ConcreteOperatorType, typename ChildOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::Expression<ChildOperatorType> &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddChild(n, o);
		}
		template<typename ChildOperatorType, typename ...Append>
		Expression(const expression::Expression<ChildOperatorType> &n, Append ...append) :Expression(append...) {
			InitPolymorphism();
			m_polymorphism->MarkFirst(&AddChild(n));
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
				ss << Visit(node)->OutPutString(index++);
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
				if (!Visit(node)->EqualZero()) {
					return false;
				}
			}
			return true;
		}
		bool EqualOne() const override {
			if (1 != m_nodes.size()) {
				return false;
			}
			return Visit(m_nodes.front())->EqualOne();
		}
		void Opposite() override {
			for (auto &node : m_nodes) {
				Visit(node)->Opposite();
			}
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
			if (count == (completed += collect.ReduceFraction(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.ReduceOpen(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.EliminationChild(count - completed))) {
				return collect;
			}
			if (count == (completed += collect.CollectFraction(count - completed))) {
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
		static Expression<OPERATOR_TYPE_0> Absorb(const number::Fraction &number) {
			const Expression<OPERATOR_TYPE_1> reduction(number.ReductionNumerator(),
				OPERATOR_TYPE_DIV(), number.Denominator());
			return Expression<OPERATOR_TYPE_0>(number.Integer(), OPERATOR_TYPE_ADD(), reduction);
		}
		static Expression<OPERATOR_TYPE_1> Absorb(const number::Imaginary &number);
		static Expression<OPERATOR_TYPE_0> Absorb(const number::Complex &number);
		static Expression<OPERATOR_TYPE_1> Absorb(const number::Root &number) {
			const Expression<OPERATOR_TYPE_2> numeratorReduction(number.ReductionBase().Numerator(),
				OPERATOR_TYPE_POWER(), number.Exponent().Denominator(),
				OPERATOR_TYPE_ROOT(), number.Exponent().Numerator());
			const Expression<OPERATOR_TYPE_2> denominatorReduction(number.ReductionBase().Numerator(),
				OPERATOR_TYPE_POWER(), number.Exponent().Denominator(),
				OPERATOR_TYPE_ROOT(), number.Exponent().Numerator());
			return Expression<OPERATOR_TYPE_1>(number.ReductionCoefficient().Numerator(),
				OPERATOR_TYPE_MUL(), numeratorReduction, OPERATOR_TYPE_DIV(), denominatorReduction);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::ClosureNumber &number) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), OPERATOR_TYPE_DIV(), number);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const number::Fraction &number) {
			return Expression<OPERATOR_TYPE_1>(number.Numerator(), OPERATOR_TYPE_DIV(), number.Denominator());
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Symbol &symbol) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), OPERATOR_TYPE_DIV(), symbol);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_0> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), OPERATOR_TYPE_DIV(), exp);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_1> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), OPERATOR_TYPE_DIV(), exp);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_2> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), OPERATOR_TYPE_DIV(), exp);
		}
		
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

		expression::ClosureNumber &AddClosure(const expression::ClosureNumber &n) {
			m_nodes.push_front(expression::ClosureNumber(n, OperatorType::FLAG));
			return std::get<expression::ClosureNumber>(m_nodes.front());
		}

		template<typename ConcreteOperatorType>
		void AddClosure(const expression::ClosureNumber &n, const ConcreteOperatorType &o){
			m_nodes.push_front(expression::ClosureNumber(n, o.GetFlag()));
		}
		
		template<typename AbstractOperatorType>
		expression::Expression<AbstractOperatorType> &AddChild(const expression::Expression<AbstractOperatorType> &child) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, OperatorType::FLAG).SetChild());
			return std::get<expression::Expression<AbstractOperatorType>>(m_nodes.front());
		}

		template<typename AbstractOperatorType, typename ConcreteOperatorType>
		void AddChild(const expression::Expression<AbstractOperatorType> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, o.GetFlag()).SetChild());
		}

		expression::Symbol &AddSymbol(const expression::Symbol &s) {
			m_nodes.push_front(expression::Symbol(s, OperatorType::FLAG));
			return std::get<expression::Symbol>(m_nodes.front());
		}

		template<typename ConcreteOperatorType>
		void AddSymbol(const expression::Symbol &s, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Symbol(s, o.GetFlag()));
		}

		void AppendNode(const ExpressionNode &node) {
			m_nodes.push_back(node);
		}

		void RemoveNode(const ExpressionNodes::iterator &node) {
			m_nodes.erase(node);
		}

		void RemoveNode(const ExpressionNodes::const_iterator &node) {
			m_nodes.erase(node);
		}

		ExpressionNode &FirstChild() {
			return m_nodes.front();
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
				RemoveNode(*itor);
				if (++completed == count) {
					break;
				}
			}
			if (1 == reciprocalsCount % 2) {
				if (1 == m_nodes.size()) {
					AddChild(Reciprocal(collect));
					RemoveNode(m_nodes.begin());
				}
				else {
					Visit(m_nodes.back())->Opposite();
				}
			}
			return std::make_pair(completed, false);
		}

		size_t CollectClosureExp0(size_t count) {
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
				default:
					continue;
					break;
				}
				RemoveNode(*itor);
				if (++completed == count) {
					break;
				}
			}
			return completed;
		}

		size_t CollectClosureExp1(size_t count) {
			return m_polymorphism->CollectClosureExp1(count);
		}

		size_t CollectClosureExp2(size_t count) {
			return m_polymorphism->CollectClosureExp2(count);
		}

		size_t CollectSpecial(size_t count) {
			return m_polymorphism->CollectSpecial(count);
		}

		size_t CollectClosure(size_t count) {
			size_t completed = 0;
			if (count == (completed += CollectPowerClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectRootClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectMulClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectDivClosure(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectClosureExp0(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectClosureExp1(count - completed))) {
				return completed;
			}
			if (count == (completed += CollectClosureExp2(count - completed))) {
				return completed;
			}
			return completed;
		}

		template<typename ChildOperatorType>
		size_t Reduce(size_t count, std::function<bool(ExpressionNodes::iterator)> factor) {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<Expression<ChildOperatorType>>(exps);
			for (auto &itor : exps) {
				auto &exp = std::get<Expression<ChildOperatorType>>(*itor);
				if (2 != exp.m_nodes.size()) {
					continue;
				}
				if (!std::get_if<expression::ClosureNumber>(&exp.m_nodes.front())) {
					continue;
				}
				if (!std::get_if<expression::ClosureNumber>(&exp.m_nodes.back())) {
					continue;
				}
				if (factor(itor)) {
					return 1;
				}
				else {
					continue;
				}
			}
			return 0;
		}

		size_t ReduceFraction(size_t count) {
			return Reduce<OPERATOR_TYPE_1>(count, [](ExpressionNodes::iterator itor) {
				const auto &exp = std::get<Expression<OPERATOR_TYPE_1>>(*itor);
				auto &numerator = std::get<expression::ClosureNumber>(exp.m_nodes.front());
				auto &denominator = std::get<expression::ClosureNumber>(exp.m_nodes.back());
				if (OPERATOR_TYPE_FLAG_DIV != denominator.Flag()) {
					return false;
				}
				const number::Fraction fraction(numerator.Value(), denominator.Value());
				if (fraction.ReductionNumerator() == numerator.Value() &&
					fraction.Integer() == number::Integer(0)) {
					return false;
				}
				*itor = Absorb(fraction);
				return true;
			});
		}

		size_t ReduceOpen(size_t count) {
			return Reduce<OPERATOR_TYPE_2>(count, [](ExpressionNodes::iterator itor) {
				const auto &exp = std::get<Expression<OPERATOR_TYPE_2>>(*itor);
				auto &base = std::get<expression::ClosureNumber>(exp.m_nodes.front());
				auto &exponent = std::get<expression::ClosureNumber>(exp.m_nodes.back());
				if (OPERATOR_TYPE_FLAG_ROOT != exponent.Flag()) {
					return false;
				}
				const number::Root root(base.Value(), exponent.Value());
				if (root.ReductionBase() == base.Value() &&
					root.ReductionCoefficient() == number::Fraction(1)) {
					return false;
				}
				*itor = Absorb(root);
				return true;
			});
		}

		size_t CollectExp2Closure(size_t count, std::function<std::pair<size_t, bool>(size_t)> factor) {
			size_t completed = 0;
			while (true) {
				const std::pair<size_t, bool> &exp2Completed = factor(count - completed);
				if (count == (completed += exp2Completed.first)) {
					return completed;
				}
				if (!exp2Completed.second) {
					break;
				}
			}
			return completed;
		}

		size_t CollectPowerClosure(size_t count) {
			return CollectExp2Closure(count, [this](size_t count) {
				return CollectExp2(count, [](expression::ClosureNumber &collect, const expression::ClosureNumber &closure, size_t &reciprocalsCount) {
					if (OPERATOR_TYPE_FLAG_POWER == closure.Flag()) {
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
					else {
						return false;
					}
				});
			});
		}

		size_t CollectRootClosure(size_t count) {
			return CollectExp2Closure(count, [this](size_t count) {
				return CollectExp2(count, [](expression::ClosureNumber &collect, const expression::ClosureNumber &closure, size_t &reciprocalsCount) {
					if (OPERATOR_TYPE_FLAG_ROOT == closure.Flag()) {
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
					else {
						return false;
					}
				});
			});
		}

		size_t CollectMulClosure(size_t count) {
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
				if (OPERATOR_TYPE_FLAG_MUL == closure.Flag()){
					collect *= closure;
				}
				else {
					continue;
				}
				RemoveNode(*itor);
				if (++completed == count) {
					break;
				}
			}
			return completed;
		}

		size_t CollectDivClosure(size_t count) {
			std::vector<ExpressionNodes::iterator> closureDivisors;
			GetAll<expression::ClosureNumber>(closureDivisors,
				[](const expression::ClosureNumber &number) {
					return OPERATOR_TYPE_FLAG_DIV == number.Flag();
				}
			);
			std::vector<ExpressionNodes::iterator> closureMultipliers;
			GetAll<expression::ClosureNumber>(closureMultipliers,
				[](const expression::ClosureNumber &number) {
					return OPERATOR_TYPE_FLAG_MUL == number.Flag();
				}
			);
			if (closureDivisors.empty() || closureMultipliers.empty()) {
				return 0;
			}
			size_t completed = 0;
			expression::ClosureNumber &divFront = std::get<expression::ClosureNumber>(*closureDivisors.front());
			number::Integer collect(divFront.Value());
			typename std::vector<ExpressionNodes::iterator>::iterator itor = closureDivisors.begin();
			while (++itor != closureDivisors.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				collect *= closure.Value();
				RemoveNode(*itor);
				if (++completed == count) {
					break;
				}
			}
			if (completed == count) {
				divFront = collect;
			}
			else {
				expression::ClosureNumber &mulFront = std::get<expression::ClosureNumber>(*closureMultipliers.front());
				const number::Fraction reduce(mulFront.Value(), collect);
				if (!(reduce.ReductionNumerator() == mulFront.Value() &&
					reduce.Integer() == number::Integer(0))) {
					*closureMultipliers.front() = reduce.Numerator();
					*closureDivisors.front() = reduce.Denominator();
					++completed;
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

		size_t CollectFraction(size_t count) {
			std::vector<ExpressionNodes::iterator> exp1s;
			GetAll<expression::Expression<OPERATOR_TYPE_1>>(exp1s);
			if (2 > exp1s.size()) {
				return 0;
			}
			size_t completed = 0;
			for (auto itor = exp1s.begin(); itor != exp1s.end();) {
				if (m_polymorphism->CollectFractionChild(exp1s, itor)) {
					RemoveNode(*itor);
					itor = exp1s.erase(itor);
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

		size_t CollectCommon(size_t count) {
			std::vector<ExpressionNodes::iterator> exps;
			m_polymorphism->GetChildren(exps);
			if (2 > exps.size()) {
				return 0;
			}
			size_t completed = 0;
			for (auto itor = exps.begin(); itor != exps.end();) {
				if (m_polymorphism->CollectCommonChild(exps, itor)) {
					RemoveNode(*itor);
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
		void Flat(const ExpressionNodes::iterator child) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*child);
			const auto &nodes = exp.m_nodes;
			for (auto itor = nodes.begin(); itor != nodes.end(); itor++) {
				typename ExpressionNodes::iterator newItor = m_nodes.insert(child, *itor);
				if (exp.IsSingle()) {
					Visit(*newItor)->SuperpositionFlag(exp.Operator());
				}
			}
			RemoveNode(child);
		}

		template<typename ChildOperatorType>
		bool CheckCollectChild(const ExpressionNodes::iterator child) {
			if (std::get<Expression<ChildOperatorType>>(*child).IsSingle()) {
				Flat<ChildOperatorType>(child);
				return true;
			}
			if constexpr (std::is_same<ChildOperatorType, OperatorType>::value) {
				Flat<ChildOperatorType>(child);
				return true;
			}
			return false;
		}


		Expression<OperatorType> SetChild() {
			m_is_child = true;
			return *this;
		}


		template<typename NodeType>
		ExpressionNodes::iterator GetFirst(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			for (auto node = m_nodes.begin(); node != m_nodes.end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						return node;
					}
				}
			}
			return m_nodes.end();
		}

		template<typename NodeType>
		ExpressionNodes::iterator GetLast(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			ExpressionNodes::iterator last = m_nodes.end();
			for (auto node = m_nodes.begin(); node != m_nodes.end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						last = node;
					}
				}
			}
			return last;
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
						if (Visit(**leftChild)->IsEqual(*Visit(**rightChild))) {
							commons.push_back(*leftChild);
							rightChildren.erase(rightChild);
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

			if (commons.empty()) {
				return std::nullopt;
			}
			Expression<OperatorType> collect;
			for (auto &common : commons) {
				collect.AppendNode(*common);
			}
			collect.AppendNode(m_polymorphism->BuildCommon(leftChildren, rightChildren, right.Flag()).SetChild());
			return collect;
		}

		template<typename ChildOperatorType>
		size_t CollectOperatorTypeChild(size_t count) {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<expression::Expression<ChildOperatorType>>(exps);
			size_t completed = 0;
			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType> &exp = std::get<Expression<ChildOperatorType>>(*exps.at(index));
				exp = exp.Collect(1, completed);
				CheckCollectChild<ChildOperatorType>(exps.at(index));
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
		
		static const Node *Visit(const ExpressionNode &node) {
			const Node *pNode = nullptr;
			std::visit([&pNode](auto &&n) {
				pNode = &n;
			}, node);
			return pNode;
		}

		static Node *Visit(ExpressionNode &node) {
			Node *pNode = nullptr;
			std::visit([&pNode](auto &&n) {
				pNode = &n;
			}, node);
			return pNode;
		}

		protected:

			class Polymorphism {
			public:
				virtual size_t CollectSpecial(size_t count) = 0;
				virtual void GetChildren(std::vector<ExpressionNodes::iterator> &exps) = 0;
				virtual bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
				virtual Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) = 0;
				virtual bool IsEqual(const Node &other) const = 0;
				virtual bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
				virtual size_t CollectClosureExp1(size_t count) = 0;
				virtual size_t CollectClosureExp2(size_t count) = 0;
				virtual bool CollectClosure(ClosureNumber &closure) = 0;
				virtual void MarkFirst(Node *first) = 0;

				template<typename ChildOperatorType>
				static std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> CollectClosures(const std::vector<ExpressionNodes::iterator> &closures,
					const std::vector<ExpressionNodes::iterator> &exps);
			};

			class Polymorphism0 : public Polymorphism {
			public:
				Polymorphism0(Expression<OPERATOR_TYPE_0> &exp);
				size_t CollectSpecial(size_t count) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const Node &other) const override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				size_t CollectClosureExp1(size_t count) override;
				size_t CollectClosureExp2(size_t count) override;
				bool CollectClosure(ClosureNumber &closure) override;
				void MarkFirst(Node *first) override;

				Expression<OPERATOR_TYPE_1> LevelDown(ExpressionNodes::iterator exp2);
				static std::optional<number::Fraction> Exhale(const expression::Expression<OPERATOR_TYPE_1> &exp1);
			private:
				Expression<OPERATOR_TYPE_0> &m_exp;
			};

			class Polymorphism1 : public Polymorphism {
			public:
				Polymorphism1(Expression<OPERATOR_TYPE_1> &exp);
				size_t CollectSpecial(size_t count) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const Node &other) const override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				
				size_t CollectClosureExp1(size_t count) override;
				size_t CollectClosureExp2(size_t count) override;
				bool CollectClosure(ClosureNumber &closure) override;
				void MarkFirst(Node *first) override;

				template<typename ChildOperatorType>
				size_t CollectClosureExp1(size_t count);
			private:
				Expression<OPERATOR_TYPE_1> &m_exp;
			};

			class Polymorphism2 : public Polymorphism {
			public:
				Polymorphism2(Expression<OPERATOR_TYPE_2> &exp);
				size_t CollectSpecial(size_t count) override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_0> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) override;
				bool IsEqual(const Node &other) const override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				size_t CollectClosureExp1(size_t count) override;
				size_t CollectClosureExp2(size_t count) override;
				bool CollectClosure(ClosureNumber &closure) override;
				void MarkFirst(Node *first) override;

				const Node *Base() const;

				template<typename ChildOperatorType>
				size_t CollectClosureExp2(size_t count);
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