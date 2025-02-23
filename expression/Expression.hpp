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
#include <optional>

#include "Node.hpp"
#include "ClosureNumber.hpp"
#include "Symbol.h"
#include "Operator.h"
#include "number/Root.h"
#include "number/Logarithm.h"


namespace expression {

	template<typename OperatorType>
	class Expression : public Node {
	public:
		typedef std::variant<ClosureNumber, Symbol, Expression<OPERATOR_TYPE_0>, Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>, Expression<OPERATOR_TYPE_3>> ExpressionNode;
		typedef std::list<ExpressionNode> ExpressionNodes;

		Expression(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD) {
			SetOperator(flag);
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
			m_polymorphism->SetUnSigned(right.m_polymorphism->IsUnSigned());
			return *this;
		}

		bool operator==(const Expression<OperatorType> &other) const {
			if (m_polymorphism->IsUnSigned() != other.m_polymorphism->IsUnSigned()) {
				return false;
			}
			if (Size() != other.Size()) {
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

		bool operator!=(const Expression<OperatorType> &other) const {
			return !(*this == other);
		}

		template<typename ConcreteOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::ClosureNumber &n, Append ...append) :Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddClosure(n, o);
		}
		template<typename ...Append>
		Expression(const expression::ClosureNumber &n, Append ...append) :Expression(append...){
			InitPolymorphism();
			AddClosure(n);
		}

		template<typename ConcreteOperatorType, typename ChildOperatorType, typename ...Append>
		Expression(const ConcreteOperatorType &o, const expression::Expression<ChildOperatorType> &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddChild(n, o);
		}
		template<typename ChildOperatorType, typename ...Append>
		Expression(const expression::Expression<ChildOperatorType> &n, Append ...append) :Expression(append...) {
			InitPolymorphism();
			AddChild(n);
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

		const std::string OutPutString() const override {
			std::stringstream ss;
			ss << m_operator->updatePosition(m_position).OutPutString();
			if (!m_polymorphism->IsUnSigned()) {
				ss << "-";
			}
			if (m_is_child || !m_polymorphism->IsUnSigned()) {
				ss << "(";
			}
			size_t index = 0;
			for (auto& node : m_nodes) {
				ss << Visit(node)->updatePosition(index++).OutPutString();
			}
			if (m_is_child || !m_polymorphism->IsUnSigned()) {
				ss << ")";
			}
			std::string s = ss.str();
			return ss.str();
		}
		
		bool IsEqual(const Node &other, bool ignoreOperator = false) const override {
			if (!Node::IsEqual(other, ignoreOperator)) {
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
		bool EqualPositiveOne() const override {
			if (1 != m_nodes.size()) {
				return false;
			}
			return Visit(m_nodes.front())->EqualPositiveOne();
		}
		bool EqualNegativeOne() const override {
			if (1 != m_nodes.size()) {
				return false;
			}
			return Visit(m_nodes.front())->EqualNegativeOne();
		}
		void Opposite() override {
			m_polymorphism->Opposite();
		}
		std::optional<Expression<OperatorType>> Collect() const{
			Expression<OperatorType> collect(*this);
			if (collect.CollectChild()) {
				return collect;
			}
			if (collect.CollectFlat()) {
				return collect;
			}
			if (collect.CollectClosure()) {
				return collect;
			}
			if (collect.CollectFraction()) {
				return collect;
			}
			if (collect.CollectCommon()) {
				return collect;
			}
			if (collect.CollectSpecial()) {
				return collect;
			}
			if (collect.CollectCancel()) {
				return collect;
			}
			if (collect.CollectCombine()) {
				return collect;
			}
			return std::nullopt;
		}

		std::ostream& CollectForward(std::ostream& out) const{
			out << *this;
			auto current = std::make_optional<Expression<OperatorType>>(*this);
			while (true) {
				auto forward = current.value().Collect();
				if (forward.has_value()) {
					std::cout << " --> " << forward.value();
					current = forward;
				}
				else {
					if (current.value().ReduceFraction()) {
						std::cout << " --> "; current.value().GetFractionReduction().CollectForward(out);
					}
					else if (current.value().ReduceRoot() || current.value().ReduceLogarithm()) {
						std::cout << " --> "; current.value().GetOpenReduction().CollectForward(out);
					}
					else if(current.value().IsSingle()){
						{
							auto child = current.value().GetFirst<expression::Expression<OPERATOR_TYPE_0>>();
							if (child.has_value()) {
								std::cout << " --> "; std::get<expression::Expression<OPERATOR_TYPE_0>>(*child.value()).SetChild(false).CollectForward(out);
								break;
							}
						}

						{
							auto child = current.value().GetFirst<expression::Expression<OPERATOR_TYPE_1>>();
							if (child.has_value()) {
								std::cout << " --> "; std::get<expression::Expression<OPERATOR_TYPE_1>>(*child.value()).SetChild(false).CollectForward(out);
								break;
							}
						}

						{
							auto child = current.value().GetFirst<expression::Expression<OPERATOR_TYPE_2>>();
							if (child.has_value()) {
								std::cout << " --> "; std::get<expression::Expression<OPERATOR_TYPE_2>>(*child.value()).SetChild(false).CollectForward(out);
								break;
							}
						}
					}
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


		Expression<OperatorType> GetOpposite() {
			Expression<OperatorType> opposite(*this);
			opposite.Opposite();
			return opposite;
		}

		static Expression<OPERATOR_TYPE_0> Absorb(const number::Fraction &number) {
			const Expression<OPERATOR_TYPE_1> reduction(number.ReductionNumerator(),
				DIV, number.Denominator());
			return Expression<OPERATOR_TYPE_0>(number.ReductionInteger(), ADD, reduction);
		}
		static Expression<OPERATOR_TYPE_1> Absorb(const number::Imaginary &number);
		static Expression<OPERATOR_TYPE_0> Absorb(const number::Complex &number);
		static Expression<OPERATOR_TYPE_1> Absorb(const number::Root &number) {
			const Expression<OPERATOR_TYPE_2> numeratorReduction(number.Power().Numerator(),
				POWER, number.Exponent().Denominator(), ROOT, number.Exponent().Numerator());
			const Expression<OPERATOR_TYPE_2> denominatorReduction(number.Power().Denominator(),
				POWER, number.Exponent().Denominator(), ROOT, number.Exponent().Numerator());
			return Expression<OPERATOR_TYPE_1>(numeratorReduction, DIV, denominatorReduction);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::ClosureNumber &number) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, number);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const number::Fraction &number) {
			return Expression<OPERATOR_TYPE_1>(number.Numerator(), DIV, number.Denominator());
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Symbol &symbol) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, symbol);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_0> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_1> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_2> &exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_1> Reciprocal(const expression::Expression<OPERATOR_TYPE_3>& exp) {
			return Expression<OPERATOR_TYPE_1>(expression::ClosureNumber(1), DIV, exp);
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

		template<typename OPERATOR_TYPE_0> friend class Expression;
		template<typename OPERATOR_TYPE_1> friend class Expression;
		template<typename OPERATOR_TYPE_2> friend class Expression;

		template<typename OPERATOR_TYPE_0> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_1> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_1> friend class ExpressionDeformationer;
		
		expression::ClosureNumber &AddClosure(const expression::ClosureNumber &n) {
			m_nodes.push_front(expression::ClosureNumber(n));
			return std::get<expression::ClosureNumber>(m_nodes.front());
		}

		template<typename ConcreteOperatorType>
		void AddClosure(const expression::ClosureNumber &n, const ConcreteOperatorType &o){
			m_nodes.push_front(expression::ClosureNumber(n, o.GetFlag()));
		}
		
		template<typename AbstractOperatorType>
		expression::Expression<AbstractOperatorType> &AddChild(const expression::Expression<AbstractOperatorType> &child) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child).SetChild());
			return std::get<expression::Expression<AbstractOperatorType>>(m_nodes.front());
		}

		template<typename AbstractOperatorType, typename ConcreteOperatorType>
		void AddChild(const expression::Expression<AbstractOperatorType> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, o.GetFlag()).SetChild());
		}

		expression::Symbol &AddSymbol(const expression::Symbol &s) {
			m_nodes.push_front(expression::Symbol(s));
			return std::get<expression::Symbol>(m_nodes.front());
		}

		template<typename ConcreteOperatorType>
		void AddSymbol(const expression::Symbol &s, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Symbol(s, o.GetFlag()));
		}

		void AppendNode(const ExpressionNode &node) {
			m_nodes.push_back(node);
			if (IsSingle()) {
				Visit(m_nodes.front())->SetOperator(OPERATOR_TYPE_FLAG_ADD);
			}
		}

		void AppendChild(const Expression<OPERATOR_TYPE_0> &child) {
			AppendNode(Expression<OPERATOR_TYPE_0>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_1> &child) {
			AppendNode(Expression<OPERATOR_TYPE_1>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_2> &child) {
			AppendNode(Expression<OPERATOR_TYPE_2>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_3>& child) {
			AppendNode(Expression<OPERATOR_TYPE_3>(child).SetChild());
		}

		OPERATOR_TYPE_FLAG RemoveNode(const ExpressionNodes::iterator &node) {
			m_nodes.erase(node);
			OPERATOR_TYPE_FLAG flag = Visit(m_nodes.front())->Flag();
			if (IsSingle()) {
				Visit(m_nodes.front())->SetOperator(OPERATOR_TYPE_FLAG_ADD);
				if (OPERATOR_TYPE_FLAG_SUB == flag) {
					Visit(m_nodes.front())->Opposite();
				}
			}
			return flag;
		}

		OPERATOR_TYPE_FLAG RemoveNode(const ExpressionNodes::const_iterator &node) {
			m_nodes.erase(node);
			OPERATOR_TYPE_FLAG flag = Visit(m_nodes.front())->Flag();
			if (IsSingle()) {
				Visit(m_nodes.front())->SetOperator(OPERATOR_TYPE_FLAG_ADD);
				if (OPERATOR_TYPE_FLAG_SUB == flag) {
					Visit(m_nodes.front())->Opposite();
				}
			}
			return flag;
		}

		ExpressionNode &FirstChild() {
			return m_nodes.front();
		}

		std::optional<ClosureNumber> GetIntegerFront() {
			if (ClosureNumber *front = std::get_if<ClosureNumber>(&m_nodes.front())) {
				return *front;
			}
			else {
				return std::nullopt;
			}
		}
		
		bool ForeachClosure(OPERATOR_TYPE_FLAG flag, std::function<std::optional<Expression<OPERATOR_TYPE_1>>(
			const expression::ClosureNumber &, const expression::ClosureNumber &)> factor) {
			const std::optional<ClosureNumber> front(GetIntegerFront());
			if (!front.has_value()) {
				return false;
			}
			std::vector<ExpressionNodes::iterator> integers;
			GetAll<expression::ClosureNumber>(integers, [&flag](const expression::ClosureNumber &node) {
				return flag == node.Flag();
			});
			if (2 > integers.size()) {
				return false;
			}
			typename std::vector<ExpressionNodes::iterator>::iterator itor = integers.begin();
			while (++itor != integers.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				const std::optional<Expression<OPERATOR_TYPE_0>> reduction(factor(front.value(), closure));
				if (reduction.has_value()) {
					ReplaceSingle(m_nodes.begin(), reduction.value());
					RemoveNode(*itor);
					return true;
				}
				else {
					return false;
				}
			}
			return false;
		}

		bool CollectClosureExp0() {
			std::vector<ExpressionNodes::iterator> closures;
			GetAll<expression::ClosureNumber>(closures);
			if (2 > closures.size()) {
				return false;
			}
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
				return true;
			}
			return false;
		}

		bool CollectClosureExp1() {
			return m_polymorphism->CollectClosureExp1();
		}

		bool CollectClosureExp2() {
			return m_polymorphism->CollectClosureExp2();
		}

		template<typename ChildOperatorType>
		bool CollectFlat() {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<expression::Expression<ChildOperatorType>>(exps);
			for (auto exp : exps) {
				if (CollectFlat<ChildOperatorType>(exp)) {
					return true;
				}
			}
			return false;
		}

		bool CollectFlat() {
			if (CollectFlat<OPERATOR_TYPE_0>()) {
				return true;
			}
			if (CollectFlat<OPERATOR_TYPE_1>()) {
				return true;
			}
			if (CollectFlat<OPERATOR_TYPE_2>()) {
				return true;
			}
			if (CollectFlat<OPERATOR_TYPE_3>()) {
				return true;
			}
			return false;
		}

		static bool compareNode(const ExpressionNode &previous, const ExpressionNode &next)
		{
			return Visit(previous)->Flag() < Visit(next)->Flag();
		}

		void SortNodes() {
			m_nodes.sort(compareNode);
		}

		bool CollectSpecial() {
			SortNodes();
			return m_polymorphism->CollectSpecial();
		}

		bool CollectCancel() {
			return m_polymorphism->CollectCancel();
		}

		bool CollectCombine() {
			return m_polymorphism->CollectCombine();
		}

		bool CollectClosure() {
			if (CollectPowerClosure()) {
				return true;
			}
			if (CollectRootClosure()) {
				return true;
			}
			if (CollectLogarithmClosure()) {
				return true;
			}
			if (CollectMulClosure()) {
				return true;
			}
			if (CollectDivClosure()) {
				return true;
			}
			if (CollectClosureExp0()) {
				return true;
			}
			if (CollectClosureExp1()) {
				return true;
			}
			if (CollectClosureExp2()) {
				return true;
			}
			return false;
		}

		bool Reduce(std::function<bool()> factor) {
			if (2 != m_nodes.size()) {
				return false;
			}
			if (!std::get_if<expression::ClosureNumber>(&m_nodes.front())) {
				return false;
			}
			if (!std::get_if<expression::ClosureNumber>(&m_nodes.back())) {
				return false;
			}
			if (factor()) {
				return true;
			}
			else {
				return false;
			}
		}

		const Expression<OPERATOR_TYPE_0> GetFractionReduction() const {
			return m_polymorphism->GetFractionReduction().value();
		}

		bool ReduceFraction() {
			if constexpr (std::is_same<OPERATOR_TYPE_1, OperatorType>::value) {
				return Reduce([&]() {
					auto &numerator = std::get<expression::ClosureNumber>(m_nodes.front());
					auto &denominator = std::get<expression::ClosureNumber>(m_nodes.back());
					if (OPERATOR_TYPE_FLAG_DIV != denominator.Flag()) {
						return false;
					}
					if (number::Fraction::CheckReduce(numerator.Value(), denominator.Value())) {
						return false;
					}
					m_polymorphism->SetFractionReduction(number::Fraction(numerator.Value(), denominator.Value()));
					return true;
				});
			}
			return false;
		}

		const Expression<OPERATOR_TYPE_1> GetOpenReduction() const {
			return m_polymorphism->GetOpenReduction().value();
		}

		bool ReduceRoot() {
			if constexpr (std::is_same<OPERATOR_TYPE_2, OperatorType>::value) {
				return Reduce([&]() {
					auto &power = std::get<expression::ClosureNumber>(m_nodes.front());
					auto &exponent = std::get<expression::ClosureNumber>(m_nodes.back());
					if (OPERATOR_TYPE_FLAG_ROOT != exponent.Flag()) {
						return false;
					}
					const std::optional<number::Root> &root = number::Root::CheckReduce(power.Value(), exponent.Value());
					if (!root.has_value()) {
						return false;
					}
					m_polymorphism->SetOpenReduction(root.value().ReductionCoefficient(),
						root.value().ReductionPower(), root.value().ReductionExponent());
					return true;
				});
			}
			return false;
		}

		bool ReduceLogarithm() {
			if constexpr (std::is_same<OPERATOR_TYPE_3, OperatorType>::value) {
				return Reduce([&]() {
					auto &power = std::get<expression::ClosureNumber>(m_nodes.front());
					auto &base = std::get<expression::ClosureNumber>(m_nodes.back());
					if (OPERATOR_TYPE_FLAG_LOGARITHM != base.Flag()) {
						return false;
					}
					const std::optional<number::Logarithm> &logarithm = number::Logarithm::CheckReduce(power.Value(), base.Value());
					if (!logarithm.has_value()) {
						return false;
					}
					m_polymorphism->SetOpenReduction(logarithm.value().ReductionCoefficient(),
						logarithm.value().ReductionPower(), logarithm.value().ReductionBase());
					return true;
				});
			}
			return false;
		}

		bool CollectPowerClosure() {
			return ForeachClosure(OPERATOR_TYPE_FLAG_POWER, [](const expression::ClosureNumber &base, const expression::ClosureNumber &exponent) {
				const number::Fraction &power = number::Fraction::Power(base.Value(), exponent.Value());
				return Absorb(power);
			});
		}

		bool CollectRootClosure() {
			return ForeachClosure(OPERATOR_TYPE_FLAG_ROOT, 
				[](const expression::ClosureNumber &power, const expression::ClosureNumber &exponent) -> std::optional < Expression<OPERATOR_TYPE_1> > {
				const number::Root root(power.Value(), exponent.Value());
				if (root.IsFraction()) {
					const number::Fraction &coefficient = root.ReductionCoefficient();
					return Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
		}

		bool CollectLogarithmClosure() {
			return ForeachClosure(OPERATOR_TYPE_FLAG_LOGARITHM, 
				[](const expression::ClosureNumber &power, const expression::ClosureNumber &base) -> std::optional < Expression<OPERATOR_TYPE_1> > {
				const number::Logarithm logarithm(power.Value(), base.Value());
				if (logarithm.IsFraction()) {
					const number::Fraction &coefficient = logarithm.ReductionCoefficient();
					return Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
		}

		bool CollectMulClosure() {
			std::vector<ExpressionNodes::iterator> closures;
			GetAll<expression::ClosureNumber>(closures);
			if (2 > closures.size()) {
				return false;
			}
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
				return true;
			}
			return false;
		}

		bool CollectDivClosure() {
			std::vector<ExpressionNodes::iterator> closureDivisors;
			GetAll<expression::ClosureNumber>(closureDivisors,
				[](const expression::ClosureNumber &number) {
					return OPERATOR_TYPE_FLAG_DIV == number.Flag();
				}
			);
			if (closureDivisors.empty()) {
				return false;
			}
			expression::ClosureNumber &divFront = std::get<expression::ClosureNumber>(*closureDivisors.front());
			number::Integer collect(divFront.Value());
			typename std::vector<ExpressionNodes::iterator>::iterator itor = closureDivisors.begin();
			while (++itor != closureDivisors.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				collect *= closure.Value();
				RemoveNode(*itor);
				divFront = expression::ClosureNumber(collect, OPERATOR_TYPE_FLAG_DIV);
				return true;
			}
			std::vector<ExpressionNodes::iterator> closureMultipliers;
			GetAll<expression::ClosureNumber>(closureMultipliers,
				[](const expression::ClosureNumber &number) {
					return OPERATOR_TYPE_FLAG_MUL == number.Flag() || OPERATOR_TYPE_FLAG_ADD == number.Flag();
				}
			);
			if (closureMultipliers.empty()) {
				return false;
			}
			expression::ClosureNumber &mulFront = std::get<expression::ClosureNumber>(*closureMultipliers.front());
			const number::Fraction reduce(mulFront.Value(), collect);
			if (reduce.IsInteger()) {
				*closureMultipliers.front() = reduce.ReductionInteger();
				RemoveNode(closureDivisors.front());
				return true;
			}
			else if (!(reduce.Numerator() == mulFront.Value() &&
						reduce.Denominator() == collect)) {
				*closureMultipliers.front() = reduce.Numerator();
				*closureDivisors.front() = expression::ClosureNumber(reduce.Denominator(), OPERATOR_TYPE_FLAG_DIV);
				return true;
			}
			return false;
		}

		bool CollectChild() {
			if (CollectChild<OPERATOR_TYPE_0>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_1>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_2>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_3>()) {
				return true;
			}
			return false;
		}

		bool CollectFraction() {
			std::vector<ExpressionNodes::iterator> exp1s;
			GetAll<expression::Expression<OPERATOR_TYPE_1>>(exp1s);
			if (2 > exp1s.size()) {
				return false;
			}
			for (auto itor = exp1s.begin(); itor != exp1s.end(); ++itor) {
				if (m_polymorphism->CollectFractionChild(exp1s, itor)) {
					RemoveNode(*itor);
					exp1s.erase(itor);
					return true;
				}
			}
			return false;
		}

		bool CollectCommon() {
			std::vector<ExpressionNodes::iterator> exps;
			m_polymorphism->GetChildren(exps);
			if (2 > exps.size()) {
				return false;
			}
			for (auto itor = exps.begin(); itor != exps.end(); ++itor) {
				if (m_polymorphism->CollectCommonChild(exps, itor)) {
					exps.erase(itor);
					return true;
				}
			}
			return false;
		}

		bool IsSingle() const{
			return 1 == m_nodes.size();
		}

		bool IsEmpty() const {
			return m_nodes.empty();
		}

		size_t Size() const {
			return m_nodes.size();
		}

		void Clear() {
			return m_nodes.clear();
		}

		ExpressionNodes::const_iterator begin() const{ return m_nodes.begin(); }
		ExpressionNodes::const_iterator end() const { return m_nodes.end(); }

		void ReplaceSingle(const ExpressionNodes::iterator oldChild, const ExpressionNode &newChild) {
			OPERATOR_TYPE_FLAG oldFlag = Visit(*oldChild)->Flag();
			typename ExpressionNodes::iterator newItor = m_nodes.insert(oldChild, newChild);
			Visit(*newItor)->SetOperator(oldFlag);
			RemoveNode(oldChild);
		}

		template<typename ChildOperatorType>
		void Replace(const ExpressionNodes::iterator oldChild, const Expression<ChildOperatorType> &newChild) {
			const OPERATOR_TYPE &oldFlag = Visit(*oldChild)->Operator();
			for (const auto &child : newChild) {
				typename ExpressionNodes::iterator newItor = m_nodes.insert(oldChild, child);
				Visit(*newItor)->SuperpositionFlag(oldFlag);
			}
			RemoveNode(oldChild);
		}

		template<typename ChildOperatorType>
		void FlatSingle(const ExpressionNodes::iterator old) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*old);
			ReplaceSingle(old, exp.First());
		}

		template<typename ChildOperatorType>
		void FlatSame(const ExpressionNodes::iterator old) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*old);
			Replace(old, exp);
		}

		template<typename ChildOperatorType>
		bool CollectFlat(const ExpressionNodes::iterator child) {
			if (std::get<Expression<ChildOperatorType>>(*child).IsSingle()) {
				FlatSingle<ChildOperatorType>(child);
				return true;
			}
			if constexpr (std::is_same<ChildOperatorType, OperatorType>::value) {
				if (m_polymorphism->FlatAble(child)) {
					FlatSame<ChildOperatorType>(child);
					return true;
				}
			}
			return false;
		}


		Expression<OperatorType> SetChild(bool isChild = true) {
			m_is_child = isChild;
			return *this;
		}


		template<typename NodeType>
		std::optional<ExpressionNodes::iterator> GetFirst(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			for (auto node = m_nodes.begin(); node != m_nodes.end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						return node;
					}
				}
			}
			return std::nullopt;
		}

		const ExpressionNode &First() const{
			return m_nodes.front();
		}

		ExpressionNode &First() {
			return m_nodes.front();
		}
		
		template<typename NodeType>
		std::optional < ExpressionNodes::iterator> GetLast(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			ExpressionNodes::iterator last = m_nodes.end();
			for (auto node = m_nodes.begin(); node != m_nodes.end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						last = node;
					}
				}
			}
			if (last != m_nodes.end()) {
				return last;
			}
			else {
				return std::nullopt;
			}
		}

		const ExpressionNode &Last() const {
			return m_nodes.back();
		}

		ExpressionNode &Last() {
			return m_nodes.back();
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

		void GetAll(std::vector<ExpressionNodes::iterator> &nodes) {
			for (auto itor = m_nodes.begin(); itor != m_nodes.end(); ++itor) {
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
			std::list<ExpressionNode> commons;
			bool isOpposite = false;
			for (auto leftChild = leftChildren.begin(); leftChild != leftChildren.end(); ) {
				if ([&] {
					for (auto rightChild = rightChildren.begin(); rightChild != rightChildren.end(); ++rightChild) {
						if (Visit(**leftChild)->IsEqual(*Visit(**rightChild), true)) {
							if (Visit(**leftChild)->Flag() == Visit(**rightChild)->Flag()) {
								commons.push_back(**leftChild);
								rightChildren.erase(rightChild);
								return true;
							}
							if ((OPERATOR_TYPE_FLAG_ADD == Visit(**leftChild)->Flag() && OPERATOR_TYPE_FLAG_MUL == Visit(**rightChild)->Flag()) ||
								(OPERATOR_TYPE_FLAG_MUL == Visit(**leftChild)->Flag() && OPERATOR_TYPE_FLAG_ADD == Visit(**rightChild)->Flag())) {
								commons.push_back(**leftChild);
								rightChildren.erase(rightChild);
								return true;
							}
						}

						if (OPERATOR_TYPE_LEVEL_1 == OperatorType::LEVEL) {
							std::unique_ptr<Node> clone = std::move(GetClone(**leftChild));
							clone->Opposite();
							if (clone->IsEqual(*Visit(**rightChild), true)) {
								commons.push_back(**leftChild);
								rightChildren.erase(rightChild);
								isOpposite = !isOpposite;
								return true;
							}
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
			else {
				return m_polymorphism->BuildCommon(leftChildren, rightChildren, right.Flag(), commons, isOpposite);
			}
		}

		template<typename ChildOperatorType>
		bool CollectChild() {
			std::vector<ExpressionNodes::iterator> exps;
			GetAll<expression::Expression<ChildOperatorType>>(exps);
			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType> &exp = std::get<Expression<ChildOperatorType>>(*exps.at(index));
				OPERATOR_TYPE_FLAG flag = exp.Flag();
				auto collect = exp.Collect();
				if (collect.has_value()) {
					*exps.at(index) = collect.value();
					return true;
				}
				else {
					if (exp.ReduceFraction()) {
						Expression<OPERATOR_TYPE_0> fraction(exp.GetFractionReduction());
						fraction.SetChild().SetOperator(flag);
						*exps.at(index) = fraction;
						return true;
					}
					else if (exp.ReduceRoot() || exp.ReduceLogarithm()) {
						Expression<OPERATOR_TYPE_1> open(exp.GetOpenReduction());
						open.SetChild().SetOperator(flag);
						*exps.at(index) = open;
						return true;
					}
				}
			}
			return false;
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

		static std::unique_ptr<Node> GetClone(const ExpressionNode &original) {
			if (std::get_if<expression::ClosureNumber>(&original)) {
				return std::make_unique<expression::ClosureNumber>(std::get<expression::ClosureNumber>(original));
			}
			if (std::get_if<expression::Symbol>(&original)) {
				return std::make_unique<expression::Symbol>(std::get<expression::Symbol>(original));
			}
			if (std::get_if<expression::Expression<OPERATOR_TYPE_0>>(&original)) {
				return std::make_unique<expression::Expression<OPERATOR_TYPE_0>>(std::get<expression::Expression<OPERATOR_TYPE_0>>(original));
			}
			if (std::get_if<expression::Expression<OPERATOR_TYPE_1>>(&original)) {
				return std::make_unique<expression::Expression<OPERATOR_TYPE_1>>(std::get<expression::Expression<OPERATOR_TYPE_1>>(original));
			}
			if (std::get_if<expression::Expression<OPERATOR_TYPE_2>>(&original)) {
				return std::make_unique<expression::Expression<OPERATOR_TYPE_2>>(std::get<expression::Expression<OPERATOR_TYPE_2>>(original));
			}
			return nullptr;
		}


		protected:

			class Polymorphism {
			public:
				virtual bool CollectSpecial() = 0;
				virtual bool CollectCancel() = 0;
				virtual bool CollectCombine() = 0;
				virtual void GetChildren(std::vector<ExpressionNodes::iterator> &exps) = 0;
				virtual bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
				virtual Expression<OPERATOR_TYPE_1> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) = 0;
				virtual bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
				virtual bool CollectClosureExp1() = 0;
				virtual bool CollectClosureExp2() = 0;
				virtual bool CollectClosure(ClosureNumber &closure) = 0;
				virtual void SetOpenReduction(const number::Fraction &coefficient, const number::Fraction &power, const number::Fraction &factor) = 0;
				virtual std::optional<const Expression<OPERATOR_TYPE_1>> GetOpenReduction() const = 0;
				virtual void SetFractionReduction(const number::Fraction &fraction) = 0;
				virtual std::optional<const Expression<OPERATOR_TYPE_0>> GetFractionReduction() const = 0;
				virtual bool IsUnSigned() const = 0;
				virtual void SetUnSigned(bool isUnSigned) = 0;
				virtual void Opposite() = 0;
				virtual bool FlatAble(const ExpressionNodes::iterator child) const = 0;

				template<typename ChildOperatorType>
				static std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> CollectClosures(const std::vector<ExpressionNodes::iterator> &closures,
					const std::vector<ExpressionNodes::iterator> &exps);
			};

			class Polymorphism0 : public Polymorphism {
			public:
				Polymorphism0(Expression<OPERATOR_TYPE_0> &exp);
				bool CollectSpecial() override;
				bool CollectCancel() override;
				bool CollectCombine() override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_1> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) override;

				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				bool CollectClosureExp1() override;
				bool CollectClosureExp2() override;
				bool CollectClosure(ClosureNumber &closure) override;
				void SetOpenReduction(const number::Fraction& coefficient, const number::Fraction& power, const number::Fraction& factor) override;
				std::optional<const Expression<OPERATOR_TYPE_1>> GetOpenReduction() const override;
				void SetFractionReduction(const number::Fraction &fraction) override;
				std::optional<const Expression<OPERATOR_TYPE_0>> GetFractionReduction() const override;
				bool IsUnSigned() const override;
				void SetUnSigned(bool isUnSigned) override;
				void Opposite() override;
				bool FlatAble(const ExpressionNodes::iterator child) const override;

				Expression<OPERATOR_TYPE_1> LevelDown(ExpressionNodes::iterator exp2);
				static std::optional<number::Fraction> Exhale(const expression::Expression<OPERATOR_TYPE_1> &exp1);
			private:
				bool CheckCombine(expression::Expression<OPERATOR_TYPE_3> &one, expression::Expression<OPERATOR_TYPE_3>& other);

				Expression<OPERATOR_TYPE_0> &m_exp;
			};

			class Polymorphism1 : public Polymorphism {
			public:
				Polymorphism1(Expression<OPERATOR_TYPE_1> &exp);
				bool CollectSpecial() override;
				bool CollectCancel() override;
				bool CollectCombine() override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_1> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				
				bool CollectClosureExp1() override;
				bool CollectClosureExp2() override;
				bool CollectClosure(ClosureNumber &closure) override;
				void SetOpenReduction(const number::Fraction& coefficient, const number::Fraction& power, const number::Fraction& factor) override;
				std::optional<const Expression<OPERATOR_TYPE_1>> GetOpenReduction() const override;
				void SetFractionReduction(const number::Fraction &fraction) override;
				std::optional<const Expression<OPERATOR_TYPE_0>> GetFractionReduction() const override;
				bool IsUnSigned() const override;
				void SetUnSigned(bool isUnSigned) override;
				void Opposite() override;
				bool FlatAble(const ExpressionNodes::iterator child) const override;

				template<typename ChildOperatorType>
				bool CollectClosureExp1();
			private:
				Expression<OPERATOR_TYPE_1> &m_exp;
				std::unique_ptr<Expression<OPERATOR_TYPE_0>> m_reduction;
			};

			class Polymorphism2 : public Polymorphism {
			public:
				Polymorphism2(Expression<OPERATOR_TYPE_2> &exp);
				bool CollectSpecial() override;
				bool CollectCancel() override;
				bool CollectCombine() override;
				void GetChildren(std::vector<ExpressionNodes::iterator> &exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_1> BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
					const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				bool CollectClosureExp1() override;
				bool CollectClosureExp2() override;
				bool CollectClosure(ClosureNumber &closure) override;
				void SetOpenReduction(const number::Fraction& coefficient, const number::Fraction& power, const number::Fraction& factor) override;
				std::optional<const Expression<OPERATOR_TYPE_1>> GetOpenReduction() const override;
				void SetFractionReduction(const number::Fraction &fraction) override;
				std::optional<const Expression<OPERATOR_TYPE_0>> GetFractionReduction() const override;
				bool IsUnSigned() const override;
				void SetUnSigned(bool isUnSigned) override;
				void Opposite() override;
				bool FlatAble(const ExpressionNodes::iterator child) const override;
				
				const Node *Origin() const;

				template<typename ChildOperatorType>
				bool CollectClosureExp2();
				
				static bool IsOriginEqualOne(const ExpressionNode &node);
				static bool IsDriverEqualZero(const ExpressionNode &node);
			private:
				static bool CancelRoot(const ExpressionNode &one, const ExpressionNode &other);
				static std::optional<Expression<OPERATOR_TYPE_1>> CancelLogarithm(const ExpressionNode &base, const ExpressionNode &mixture);
			private:
				Expression<OPERATOR_TYPE_2> &m_exp;
				std::unique_ptr<Expression<OPERATOR_TYPE_1>> m_reduction;
				bool m_unsigned = true;
			};

			class Polymorphism3 : public Polymorphism {
			public:
				Polymorphism3(Expression<OPERATOR_TYPE_3>& exp);
				bool CollectSpecial() override;
				bool CollectCancel() override;
				bool CollectCombine() override;
				void GetChildren(std::vector<ExpressionNodes::iterator>& exps) override;
				bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				Expression<OPERATOR_TYPE_1> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
					const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons, bool isOpposite) override;
				bool CollectFractionChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
				bool CollectClosureExp1() override;
				bool CollectClosureExp2() override;
				bool CollectClosure(ClosureNumber& closure) override;
				void SetOpenReduction(const number::Fraction& coefficient, const number::Fraction& power, const number::Fraction& factor) override;
				std::optional<const Expression<OPERATOR_TYPE_1>> GetOpenReduction() const override;
				void SetFractionReduction(const number::Fraction& fraction) override;
				std::optional<const Expression<OPERATOR_TYPE_0>> GetFractionReduction() const override;
				bool IsUnSigned() const override;
				void SetUnSigned(bool isUnSigned) override;
				void Opposite() override;
				bool FlatAble(const ExpressionNodes::iterator child) const override;
			private:
				static std::optional<Expression<OPERATOR_TYPE_1>> CancelLogarithm(const ExpressionNode& base, const ExpressionNode& mixture);
			private:
				Expression<OPERATOR_TYPE_3>& m_exp;
				std::unique_ptr<Expression<OPERATOR_TYPE_1>> m_reduction;
				bool m_unsigned = true;
			};
			
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
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_3>::value) {
						m_polymorphism = std::make_unique<Polymorphism3>(*this);
					}
				}
			}
		private:
			std::unique_ptr<Polymorphism> m_polymorphism;
	};
	
	
}

#endif