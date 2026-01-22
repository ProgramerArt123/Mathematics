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
#include "Imaginary.h"
#include "Operator.h"
#include "number/Root.h"
#include "number/Logarithm.h"
#include "inf/Infinitesimal.h"


namespace expression {

	class Polymorphism;
	class PolymorphismAddSub;
	class PolymorphismMulDiv;
	class PolymorphismPowerRoot;
	class PolymorphismLogarithm;

	template<typename OperatorType = OPERATOR_TYPE_ADD_SUB>
	class Expression : public Node {
	public:
		typedef std::variant<ClosureNumber, SymbolWrapper, Expression<OPERATOR_TYPE_ADD_SUB>, Expression<OPERATOR_TYPE_MUL_DIV>, Expression<OPERATOR_TYPE_POWER_ROOT>, Expression<OPERATOR_TYPE_LOGARITHM>> ExpressionNode;
		typedef std::list<ExpressionNode> ExpressionNodes;

		typedef std::variant<Expression<OPERATOR_TYPE_ADD_SUB>, Expression<OPERATOR_TYPE_MUL_DIV>, Expression<OPERATOR_TYPE_POWER_ROOT>, Expression<OPERATOR_TYPE_LOGARITHM>> ExpressionSome;

		Expression(OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE) {
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
			return *this;
		}

		bool operator==(const Expression<OperatorType> &other) const {
			if (IsUnSigned() != other.IsUnSigned()) {
				return false;
			}
			if (Size() != other.Size()) {
				return false;
			}
			auto i = m_nodes.cbegin(), j = other.m_nodes.cbegin();
			while (i != m_nodes.cend() && j != other.m_nodes.cend()) {
				if (!Visit(*i++)->IsEqual(*Visit(*j++))) {
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
		Expression(const ConcreteOperatorType &o, const expression::SymbolWrapper &n, Append ...append) : Expression(append...) {
			static_assert(std::is_base_of<OperatorType, ConcreteOperatorType>::value, "ConcreteOperatorType invalid");
			AddSymbol(n, o);
		}
		template<typename ...Append>
		Expression(const expression::SymbolWrapper &n, Append ...append) : Expression(append...) {
			InitPolymorphism();
			AddSymbol(n);
		}

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const {
			std::stringstream ss;
			if (IsDisplaySigned()) {
				ss << "-";
			}
			if (IsDisplaySigned() || m_is_child) {
				ss << "(";
			}
			size_t pos = 0;
			for (auto& node : m_nodes) {
				ss << Visit(node)->OutPutString(pos++);
			}
			if (IsDisplaySigned() || m_is_child) {
				ss << ")";
			}
			return ss.str();
		}

		bool IsEqual(const Node &other, bool ignoreSigned = false, bool ignoreOperator = false) const override {
			if (!Node::IsEqual(other, ignoreSigned, ignoreOperator)) {
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
			if (!IsSingle()) {
				return false;
			}
			return Visit(Front())->EqualPositiveOne();
		}
		bool EqualNegativeOne() const override {
			if (!IsSingle()) {
				return false;
			}
			return Visit(Front())->EqualNegativeOne();
		}
		bool Signed() override {
			if (m_polymorphism->Signed()) {
				return true;
			}
			for (auto &node : m_nodes) {
				if (Visit(node)->Signed()) {
					return true;
				}
			}
			return false;
		}
		void Substitution(OPERATOR_TYPE_FLAG flag) override {
			Node::Substitution(flag);
			SetChild(true);
		}
		std::optional<Expression<OperatorType>> Collect() const{
			Expression<OperatorType> collect(*this);
			if (collect.CollectChild()) {
				return collect;
			}
			if (collect.Signed()) {
				return collect;
			}
			if (collect.Sort()) {
				return collect;
			}
			if (collect.Flat()) {
				return collect;
			}
			if (collect.Closure()) {
				return collect;
			}
			if (collect.CollectCommon()) {
				return collect;
			}
			if (collect.Special()) {
				return collect;
			}
			if (collect.Cancel()) {
				return collect;
			}
			if (collect.Symbol()) {
				return collect;
			}
			return std::nullopt;
		}


		template<typename ChildOperatorType>
		std::optional<expression::Expression<ChildOperatorType>> ForwardChild(Expression<OperatorType>& current) const {
			auto child = current.GetFirst<expression::Expression<ChildOperatorType>>();
			if (child.has_value()) {
				bool currentIsUnSigned = current.IsUnSigned();
				OPERATOR_TYPE_FLAG currentFlag = current.Flag();
				expression::Expression<ChildOperatorType> &flat = std::get<expression::Expression<ChildOperatorType>>(*child.value());
				flat.SetOperator(currentFlag);
				flat.SetUnSigned(flat.IsUnSigned() == currentIsUnSigned);
				return flat.SetChild(false);
			}
			return std::nullopt;
		}

		template<typename ChildOperatorType>
		bool ForwardChildOutput(Expression<OperatorType> &current, std::ostream &out) const {
			auto child = ForwardChild<ChildOperatorType>(current);
			if (child.has_value()) {
				out << " --> "; child.value().CollectForwardOutput(out);
				return true;
			}
			return false;
		}

		std::shared_ptr<ExpressionSome> ForwardSingleChild(Expression<OperatorType>& current) const {
			if (auto child = ForwardChild<OPERATOR_TYPE_ADD_SUB>(current)) {
				return std::make_shared<ExpressionSome>(child.value());
			}

			if (auto child = ForwardChild<OPERATOR_TYPE_MUL_DIV>(current)) {
				return std::make_shared<ExpressionSome>(child.value());
			}

			if (auto child = ForwardChild<OPERATOR_TYPE_POWER_ROOT>(current)) {
				return std::make_shared<ExpressionSome>(child.value());
			}

			if (auto child = ForwardChild<OPERATOR_TYPE_LOGARITHM>(current)) {
				return std::make_shared<ExpressionSome>(child.value());
			}

			return nullptr;
		}

		std::list<ExpressionSome> CollectForward() const {
			std::list<ExpressionSome> forwards;
			auto current = std::make_optional<Expression<OperatorType>>(*this);
			while (true) {
				auto forward = current.value().Collect();
				if (forward.has_value()) {
					forwards.push_back(forward.value());
					current = forward;
				}
				else {
					auto reduction = current.value().Reduce();
					if (reduction) {
						const auto &reductionForwards = reduction->CollectForward();
						forwards.insert(forwards.end(), reductionForwards.begin(), reductionForwards.end());
					}
					else if (current.value().IsSingle()) {
						auto child = ForwardSingleChild(current.value());
						if (child) {
							forwards.push_back(*child);
						}
					}
					break;
				}
			}
			return forwards;
		}

		std::list<ExpressionSome> CollectForwardOutput(std::ostream& out) const{
			out << *this;
			const auto &forwards = CollectForward();
			for (const auto &forward : forwards) {
				out << " --> ";
				std::visit([&out](const auto &value) {
					out << value;
				}, forward);
			}
			return forwards;
		}

		std::list<ExpressionSome> ExpandForwardOutput(std::ostream& out) const {
			out << *this;
			const auto& forwards = ExpandForward();
			for (const auto& forward : forwards) {
				out << " --< ";
				std::visit([&out](const auto& value) {
					out << value;
					}, forward);
			}
			return forwards;
		}

		Expression<OperatorType> Substitution(const SymbolWrapper &source, const ExpressionNode &destination) const {
			Expression<OperatorType> magnitude(*this);
			magnitude.ForeachNodes([&source, &destination](ExpressionNodes::iterator itor) {
				if (source.IsEqual(*Visit(*itor), true)) {
					OPERATOR_TYPE_FLAG flag = Visit(*itor)->Flag();
					*itor = destination;
					Visit(*itor)->Substitution(flag);
				}
				return true;
			});
			return magnitude;
		}

		template<typename ChildOperatorType>
		bool ExpandChild() {
			std::vector<ExpressionNodes::iterator> exps = GetAll<expression::Expression<ChildOperatorType>>();

			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType>& exp = std::get<Expression<ChildOperatorType>>(*exps.at(index));
				OPERATOR_TYPE_FLAG flag = exp.Flag();
				auto expand = exp.Expand();
				if (expand.has_value()) {
					*exps.at(index) = expand.value();
					return true;
				}
			}

			return false;
		}

		bool ExpandChild() {
			if (ExpandChild<OPERATOR_TYPE_ADD_SUB>()) {
				return true;
			}
			if (ExpandChild<OPERATOR_TYPE_MUL_DIV>()) {
				return true;
			}
			if (ExpandChild<OPERATOR_TYPE_POWER_ROOT>()) {
				return true;
			}
			if (ExpandChild<OPERATOR_TYPE_LOGARITHM>()) {
				return true;
			}
			return false;
		}

		template<typename ChildOperatorType>
		bool ExpandExpression() {
			std::vector<ExpressionNodes::iterator> exps = GetAll<expression::Expression<ChildOperatorType>>();

			for (size_t i = 0; i < exps.size(); ++i) {
				Expression<ChildOperatorType>& exp = std::get<Expression<ChildOperatorType>>(*exps.at(i));
				auto expand = m_polymorphism->ExpandExpression(*exp.m_polymorphism, exps.at(i));
				if (expand.has_value()) {
					Clear();
					AppendChild(expand.value());
					return true;
				}
			}

			return false;
		}

		bool ExpandExpression() {
			return m_polymorphism->ExpandExpression();
		}

		std::optional<Expression<OperatorType>> Expand() const {
			Expression<OperatorType> expand(*this);
			if (expand.ExpandChild()) {
				return expand;
			}
			if (expand.Signed()) {
				return expand;
			}
			if (expand.Sort()) {
				return expand;
			}
			if (expand.Flat()) {
				return expand;
			}
			if (expand.ExpandExpression()) {
				return expand;
			}
			if (expand.Special()) {
				return expand;
			}
			if (expand.Cancel()) {
				return expand;
			}
			if (expand.Symbol()) {
				return expand;
			}
			return std::nullopt;
		}

		std::list<ExpressionSome> ExpandForward() const {
			std::list<ExpressionSome> forwards;
			auto current = std::make_optional<Expression<OperatorType>>(*this);
			while (true) {
				auto forward = current.value().Expand();
				if (forward.has_value()) {
					forwards.push_back(forward.value());
					current = forward;
				}
				else {
					auto reduction = current.value().Reduce();
					if (reduction) {
						const auto& reductionForwards = reduction->ExpandForward();
						forwards.insert(forwards.end(), reductionForwards.begin(), reductionForwards.end());
					}
					else if (current.value().IsSingle()) {
						auto child = ForwardSingleChild(current.value());
						if (child) {
							forwards.push_back(*child);
						}
					}
					break;
				}
			}
			return forwards;
		}


		Expression<OperatorType> GetOpposite() {
			Expression<OperatorType> opposite(*this);
			opposite.Opposite();
			return opposite;
		}

		static Expression<OPERATOR_TYPE_ADD_SUB> Absorb(const number::Fraction &number) {
			const Expression<OPERATOR_TYPE_MUL_DIV> reduction(number::Integer(number.ReductionNumerator(), number.IsPositive()),
				DIV, number::Integer(number.ReductionDenominator()));
			return Expression<OPERATOR_TYPE_ADD_SUB>(number::Integer(number.ReductionInteger(), number.IsPositive()), ADD, reduction);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Absorb(const number::Imaginary& number) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(Absorb(number.Value()), MUL, SYMBOL_IMAGINARY);
		}
		static Expression<OPERATOR_TYPE_ADD_SUB> Absorb(const number::Complex& number) {
			return Expression<OPERATOR_TYPE_ADD_SUB>(Absorb(number.Real()), ADD, Absorb(number.Image()));
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Absorb(const number::Root &number) {
			const Expression<OPERATOR_TYPE_ADD_SUB> coefficient(number.ReductionCoefficient());
			const Expression<OPERATOR_TYPE_POWER_ROOT> reduction(number.ReductionPower(), ROOT, number.ReductionExponent());
			return Expression<OPERATOR_TYPE_MUL_DIV>(coefficient, MUL, reduction);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::ClosureNumber &number) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, number);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const number::Fraction &number) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(number.Numerator(), DIV, number.Denominator());
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::SymbolWrapper &symbol) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, symbol);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &exp) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &exp) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &exp) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, exp);
		}
		static Expression<OPERATOR_TYPE_MUL_DIV> Reciprocal(const expression::Expression<OPERATOR_TYPE_LOGARITHM>& exp) {
			return Expression<OPERATOR_TYPE_MUL_DIV>(expression::ClosureNumber(1), DIV, exp);
		}

		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition);

		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend);

		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier);

		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor);

		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &addition);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &addition);

		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &subtrahend);
		//friend Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &subtrahend);

		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &multiplier);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &multiplier);
		
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &divisor);
		//friend Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &divisor);

	private:
		
		ExpressionNodes m_nodes;

		bool m_is_child = false;

		template<typename OPERATOR_TYPE_ADD_SUB> friend class Expression;
		template<typename OPERATOR_TYPE_MUL_DIV> friend class Expression;
		template<typename OPERATOR_TYPE_POWER_ROOT> friend class Expression;

		template<typename OPERATOR_TYPE_ADD_SUB> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_MUL_DIV> friend class ExpressionDeformationer;
		template<typename OPERATOR_TYPE_MUL_DIV> friend class ExpressionDeformationer;

		friend class expression::Imaginary;
		friend class inf::Infinitesimal;

		friend class Polymorphism;
		friend class PolymorphismAddSub;
		friend class PolymorphismMulDiv;
		friend class PolymorphismPowerRoot;
		friend class PolymorphismLogarithm;
		
		expression::ClosureNumber &AddClosure(const expression::ClosureNumber &n) {
			m_nodes.push_front(expression::ClosureNumber(n));
			Visit(Front())->SetOperator(m_polymorphism->FrontDefaultFlag());
			return std::get<expression::ClosureNumber>(Front());
		}

		template<typename ConcreteOperatorType>
		void AddClosure(const expression::ClosureNumber &n, const ConcreteOperatorType &o){
			m_nodes.push_front(expression::ClosureNumber(n, o.GetFlag()));
		}
		
		template<typename AbstractOperatorType>
		expression::Expression<AbstractOperatorType> &AddChild(const expression::Expression<AbstractOperatorType> &child) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child).SetChild());
			Visit(Front())->SetOperator(m_polymorphism->FrontDefaultFlag());
			return std::get<expression::Expression<AbstractOperatorType>>(Front());
		}

		template<typename AbstractOperatorType, typename ConcreteOperatorType>
		void AddChild(const expression::Expression<AbstractOperatorType> &child, const ConcreteOperatorType &o) {
			m_nodes.push_front(expression::Expression<AbstractOperatorType>(child, o.GetFlag()).SetChild());
		}

		expression::SymbolWrapper &AddSymbol(const expression::SymbolWrapper &s) {
			m_nodes.push_front(s);
			Visit(Front())->SetOperator(m_polymorphism->FrontDefaultFlag());
			return std::get<expression::SymbolWrapper>(Front());
		}

		template<typename ConcreteOperatorType>
		void AddSymbol(const expression::SymbolWrapper &s, const ConcreteOperatorType &o) {
			m_nodes.push_front(s);
			Visit(Front())->SetOperator(o.GetFlag());
		}

		void AppendNode(const ExpressionNode &node) {
			m_nodes.push_back(node);
		}

		void AppendChild(const Expression<OPERATOR_TYPE_ADD_SUB> &child) {
			AppendNode(Expression<OPERATOR_TYPE_ADD_SUB>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_MUL_DIV> &child) {
			AppendNode(Expression<OPERATOR_TYPE_MUL_DIV>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_POWER_ROOT> &child) {
			AppendNode(Expression<OPERATOR_TYPE_POWER_ROOT>(child).SetChild());
		}

		void AppendChild(const Expression<OPERATOR_TYPE_LOGARITHM>& child) {
			AppendNode(Expression<OPERATOR_TYPE_LOGARITHM>(child).SetChild());
		}

		void RemoveNode(const ExpressionNodes::iterator &node) {
			m_nodes.erase(node);
		}

		void RemoveNode(const ExpressionNodes::const_iterator &node) {
			m_nodes.erase(node);
		}

		std::optional<ClosureNumber> GetIntegerFront() {
			if (ClosureNumber *front = std::get_if<ClosureNumber>(&Front())) {
				return *front;
			}
			else {
				return std::nullopt;
			}
		}
		
		bool ForeachClosure(OPERATOR_TYPE_FLAG flag, std::function<std::optional<Expression<OPERATOR_TYPE_MUL_DIV>>(
			const expression::ClosureNumber &, const expression::ClosureNumber &)> factor) {
			const std::optional<ClosureNumber> front(GetIntegerFront());
			if (!front.has_value()) {
				return false;
			}
			std::vector<ExpressionNodes::iterator> integers =
				GetAll<expression::ClosureNumber>([&flag](const expression::ClosureNumber& node) {
				return flag == node.Flag();
					});
			
			if (integers.empty()) {
				return false;
			}

			typename std::vector<ExpressionNodes::iterator>::iterator itor = integers.begin();
			while (itor != integers.end()) {
				const expression::ClosureNumber &closure = std::get<expression::ClosureNumber>(**itor);
				const std::optional<Expression<OPERATOR_TYPE_ADD_SUB>> reduction(factor(front.value(), closure));
				if (reduction.has_value()) {
					ReplaceSingle(begin(), reduction.value());
					RemoveNode(*itor);
					return true;
				}
				else {
					return false;
				}
				itor++;
			}
			return false;
		}

		template<typename ChildOperatorType>
		bool Flat() {
			std::vector<ExpressionNodes::iterator> exps = GetAll<expression::Expression<ChildOperatorType>>();
			
			for (auto exp : exps) {
				if (Flat<ChildOperatorType>(exp)) {
					return true;
				}
			}
			return false;
		}

		bool Flat() {
			if (Flat<OPERATOR_TYPE_ADD_SUB>()) {
				return true;
			}
			if (Flat<OPERATOR_TYPE_MUL_DIV>()) {
				return true;
			}
			if (Flat<OPERATOR_TYPE_POWER_ROOT>()) {
				return true;
			}
			if (Flat<OPERATOR_TYPE_LOGARITHM>()) {
				return true;
			}
			return false;
		}

		bool Sort() {
			const ExpressionNodes original(m_nodes.cbegin(), m_nodes.cend());
			m_nodes.sort([](const ExpressionNode& previous, const ExpressionNode& next)
				{
					OPERATOR_TYPE_FLAG previousFlag = Visit(previous)->Flag();
					OPERATOR_TYPE_FLAG nextFlag = Visit(next)->Flag();
					if (previousFlag != nextFlag) {
						return previousFlag < nextFlag;
					}

					auto compare = CompareNode(previous, next);
					if (compare.has_value()) {
						return compare.value();
					}

					return false;
				});
			return !std::equal(original.cbegin(), original.cend(), m_nodes.cbegin());
		}

		bool Special() {
			return m_polymorphism->Special();
		}

		bool Cancel() {
			return m_polymorphism->Cancel();
		}

		bool Closure() {
			return m_polymorphism->Closure();
		}

		bool Symbol() {
			if (m_polymorphism->SymbolExtend()) {
				return true;
			}
			return SubstitutionSymbols();
		}

		std::shared_ptr<Expression<OPERATOR_TYPE_ADD_SUB>> Reduce() {
			if (2 != Size()) {
				return nullptr;
			}
			if (!std::get_if<expression::ClosureNumber>(&Front())) {
				return nullptr;
			}
			if (!std::get_if<expression::ClosureNumber>(&Back())) {
				return nullptr;
			}
			auto reduction = m_polymorphism->Reduce();
			if (reduction.has_value()) {
				return std::make_shared<Expression<OPERATOR_TYPE_ADD_SUB>>(reduction.value());
			}
			return nullptr;
		}

		std::optional<bool> Compare(const Expression<OperatorType> &other) const {
			auto i = m_nodes.cbegin(), j = other.m_nodes.cbegin();
			while (i != m_nodes.cend() && j != other.m_nodes.cend()) {
				auto compare = CompareNode(*i++, *j++);
				if (compare.has_value()) {
					return compare.value();
				}
			}
			return std::nullopt;
		}

		bool CollectChild() {
			if (CollectChild<OPERATOR_TYPE_ADD_SUB>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_MUL_DIV>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_POWER_ROOT>()) {
				return true;
			}
			if (CollectChild<OPERATOR_TYPE_LOGARITHM>()) {
				return true;
			}
			return false;
		}

		bool CollectCommon() {
			std::vector<ExpressionNodes::iterator> exps = m_polymorphism->GetChildren();
			
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

		Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const {
			return m_polymorphism->GetCommonAdpterMulDiv();
		}

		bool IsSingle() const{
			return 1 == Size();
		}

		bool IsEmpty() const {
			return m_nodes.empty();
		}

		size_t Size() const override {
			return m_nodes.size();
		}

		void Clear() {
			return m_nodes.clear();
		}

		ExpressionNodes::const_iterator begin() const{ return m_nodes.begin(); }
		ExpressionNodes::iterator begin() { return m_nodes.begin(); }

		ExpressionNodes::const_iterator end() const { return m_nodes.end(); }
		ExpressionNodes::iterator end() { return m_nodes.end(); }

		bool ForeachNodes(std::function<bool(ExpressionNodes::iterator)> nodeCallback) {
			for (ExpressionNodes::iterator itor = begin(); itor != end(); itor ++) {
				if (expression::Expression<OPERATOR_TYPE_ADD_SUB>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_ADD_SUB>>(&*itor)) {
					if (!exp->ForeachNodes(nodeCallback)) {
						return false;
					}
				}
				else if (expression::Expression<OPERATOR_TYPE_MUL_DIV>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(&*itor)) {
					if (!exp->ForeachNodes(nodeCallback)) {
						return false;
					}
				}
				else if (expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(&*itor)) {
					if (!exp->ForeachNodes(nodeCallback)) {
						return false;
					}
				}
				else if (expression::Expression<OPERATOR_TYPE_LOGARITHM>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(&*itor)) {
					if (!exp->ForeachNodes(nodeCallback)) {
						return false;
					}
				}
				if (!nodeCallback(itor)) {
					return false;
				}
			}
			return true;
		}

		void ReplaceSingle(const ExpressionNodes::iterator oldChild, const ExpressionNode &newChild) {
			bool oldIsUnSigned = Visit(*oldChild)->IsUnSigned();
			OPERATOR_TYPE_FLAG oldFlag = Visit(*oldChild)->Flag();
			typename ExpressionNodes::iterator newItor = m_nodes.insert(oldChild, newChild);
			Visit(*newItor)->SetOperator(oldFlag);
			Visit(*newItor)->SetUnSigned(Visit(*newItor)->IsUnSigned() == oldIsUnSigned);
			RemoveNode(oldChild);
		}

		template<typename ChildOperatorType>
		void Replace(const ExpressionNodes::iterator oldChild, const Expression<ChildOperatorType> &newChild) {
			bool oldIsUnSigned = Visit(*oldChild)->IsUnSigned();
			const OPERATOR_TYPE &oldFlag = Visit(*oldChild)->Operator();
			for (const auto &child : newChild) {
				typename ExpressionNodes::iterator newItor = m_nodes.insert(oldChild, child);
				Visit(*newItor)->SuperpositionFlag(oldFlag);
				Visit(*newItor)->SetUnSigned(Visit(*newItor)->IsUnSigned() == oldIsUnSigned);
			}
			RemoveNode(oldChild);
		}

		template<typename ChildOperatorType>
		void FlatSingle(const ExpressionNodes::iterator old) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*old);
			ReplaceSingle(old, exp.Front());
		}

		template<typename ChildOperatorType>
		void FlatSame(const ExpressionNodes::iterator old) {
			const auto &exp = std::get<Expression<ChildOperatorType>>(*old);
			Replace(old, exp);
		}

		template<typename ChildOperatorType>
		bool Flat(const ExpressionNodes::iterator child) {
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
			for (auto node = begin(); node != end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						return node;
					}
				}
			}
			return std::nullopt;
		}

		const ExpressionNode &Front() const{
			return m_nodes.front();
		}

		ExpressionNode &Front() {
			return m_nodes.front();
		}
		
		template<typename NodeType>
		std::optional < ExpressionNodes::iterator> GetLast(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) {
			ExpressionNodes::iterator last = end();
			for (auto node = begin(); node != end(); ++node) {
				if (NodeType *typeNode = std::get_if<NodeType>(&*node)) {
					if (filter(*typeNode)) {
						last = node;
					}
				}
			}
			if (last != end()) {
				return last;
			}
			else {
				return std::nullopt;
			}
		}

		const ExpressionNode &Back() const {
			return m_nodes.back();
		}

		ExpressionNode &Back() {
			return m_nodes.back();
		}

		template<typename NodeType>
		std::vector<ExpressionNodes::const_iterator> GetAll(std::function<bool(const NodeType &)> filter = [](const NodeType &node) {return true; }) const{
			std::vector<ExpressionNodes::const_iterator> nodes;
			for (auto itor = m_nodes.cbegin(); itor != m_nodes.cend(); ++ itor) {
				if (const NodeType *node = std::get_if<NodeType>(&*itor)) {
					if (filter(*node)) {
						nodes.push_back(itor);
					}
				}
			}
			return nodes;
		}

		template<typename NodeType>
		std::vector<ExpressionNodes::iterator> GetAll(std::function<bool(const NodeType&)> filter = [](const NodeType& node) {return true; }) {
			std::vector<ExpressionNodes::iterator> nodes;
			for (auto itor = begin(); itor != end(); ++itor) {
				if (const NodeType* node = std::get_if<NodeType>(&*itor)) {
					if (filter(*node)) {
						nodes.push_back(itor);
					}
				}
			}
			return nodes;
		}

		std::vector<ExpressionNodes::const_iterator> GetAll() const {
			std::vector<ExpressionNodes::const_iterator> nodes;
			for (auto itor = m_nodes.cbegin(); itor != m_nodes.cend(); ++itor) {
				nodes.push_back(itor);
			}
			return nodes;
		}

		std::vector<ExpressionNodes::iterator> GetAll() {
			std::vector<ExpressionNodes::iterator> nodes;
			for (auto itor = begin(); itor != end(); ++itor) {
				nodes.push_back(itor);
			}
			return nodes;
		}

		std::optional<expression::Expression<OperatorType>> CollectCommon(const Expression<OperatorType> &right) const {
			std::vector<ExpressionNodes::const_iterator> leftChildren = GetAll();
			std::vector<ExpressionNodes::const_iterator> rightChildren = right.GetAll();
			std::list<ExpressionNode> commons;

			for (auto leftChild = leftChildren.begin(); leftChild != leftChildren.end(); ) {
				if ([&] {
					for (auto rightChild = rightChildren.begin(); rightChild != rightChildren.end(); ++rightChild) {
						if (Visit(**leftChild)->IsEqual(*Visit(**rightChild)) &&
							!Visit(**leftChild)->EqualPositiveOne()) {

							commons.push_back(**leftChild);
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

			if (!commons.empty()) {
				return m_polymorphism->BuildCommon(leftChildren, rightChildren, right.Flag(), commons);
			}
			else {
				return std::nullopt;
			}
		}

		template<typename ChildOperatorType>
		bool CollectChild() {
			std::vector<ExpressionNodes::iterator> exps = GetAll<expression::Expression<ChildOperatorType>>();
			
			for (size_t index = 0; index < exps.size(); ++index) {
				Expression<ChildOperatorType> &exp = std::get<Expression<ChildOperatorType>>(*exps.at(index));
				OPERATOR_TYPE_FLAG flag = exp.Flag();
				auto collect = exp.Collect();
				if (collect.has_value()) {
					*exps.at(index) = collect.value();
					return true;
				}
				else {
					auto reduction = exp.Reduce();
					if (reduction) {
						reduction->SetOperator(flag);
						*exps.at(index) = reduction->SetChild(true);
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
			return std::make_unique<Node>(original);
		}

		template<typename NodeType>
		static std::optional<bool> CompareTypeNode(const ExpressionNode& one, const ExpressionNode& other) {
			if (!std::get_if<NodeType>(&one) || !std::get_if<NodeType>(&other)) {
				return std::nullopt;
			}
			return std::get<NodeType>(one).Compare(std::get<NodeType>(other));
		}

		static std::optional<bool> CompareNode(const ExpressionNode& one, const ExpressionNode& other) {

			size_t oneType = one.index();
			size_t otherType = other.index();
			if (oneType != otherType) {
				return oneType < otherType;
			}
			
			size_t previousSize = Visit(one)->Size();
			size_t nextSize = Visit(other)->Size();
			if (previousSize != nextSize) {
				return previousSize < nextSize;
			}

			{
				auto compare = CompareTypeNode<expression::ClosureNumber>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			{
				auto compare = CompareTypeNode<expression::SymbolWrapper>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			{
				auto compare = CompareTypeNode<expression::Expression<OPERATOR_TYPE_ADD_SUB>>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			{
				auto compare = CompareTypeNode<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			{
				auto compare = CompareTypeNode<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			{
				auto compare = CompareTypeNode<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(one, other);
				if (compare.has_value()) {
					return compare.value();
				}
			}

			return std::nullopt;
		}

		bool SubstitutionSymbols() {
			return !ForeachNodes([](ExpressionNodes::iterator itor) {
				if (const expression::SymbolWrapper* symbol = std::get_if<expression::SymbolWrapper>(&*itor)) {
					const std::shared_ptr<Node> substitution = symbol->GetSubstitution();
					if (substitution) {
						OPERATOR_TYPE_FLAG flag = Visit(*itor)->Flag();
						if (typeid(*substitution) == typeid(expression::ClosureNumber)) {
							*itor = *std::dynamic_pointer_cast<expression::ClosureNumber>(substitution);
						}
						else if (typeid(*substitution) == typeid(expression::SymbolWrapper)) {
							*itor = *std::dynamic_pointer_cast<expression::SymbolWrapper>(substitution);
						}
						else if (typeid(*substitution) == typeid(expression::Expression<OPERATOR_TYPE_ADD_SUB>)) {
							*itor = *std::dynamic_pointer_cast<expression::Expression<OPERATOR_TYPE_ADD_SUB>>(substitution);
						}
						else if (typeid(*substitution) == typeid(expression::Expression<OPERATOR_TYPE_MUL_DIV>)) {
							*itor = *std::dynamic_pointer_cast<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(substitution);
						}
						else if (typeid(*substitution) == typeid(expression::Expression<OPERATOR_TYPE_POWER_ROOT>)) {
							*itor = *std::dynamic_pointer_cast<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(substitution);
						}
						else if (typeid(*substitution) == typeid(expression::Expression<OPERATOR_TYPE_LOGARITHM>)) {
							*itor = *std::dynamic_pointer_cast<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(substitution);
						}
						else {
							assert(0);
						}
						Visit(*itor)->Substitution(flag);
						return false;
					}
				}
				return true;
			});
		}

		protected:

			
			void InitPolymorphism() {
				if (!m_polymorphism) {
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_ADD_SUB>::value) {
						m_polymorphism = std::make_unique<PolymorphismAddSub>(*this);
					}
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_MUL_DIV>::value) {
						m_polymorphism = std::make_unique<PolymorphismMulDiv>(*this);
					}
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_POWER_ROOT>::value) {
						m_polymorphism = std::make_unique<PolymorphismPowerRoot>(*this);
					}
					if constexpr (std::is_same<OperatorType, OPERATOR_TYPE_LOGARITHM>::value) {
						m_polymorphism = std::make_unique<PolymorphismLogarithm>(*this);
					}
				}
			}
		private:
			std::unique_ptr<Polymorphism> m_polymorphism;
	};
	
	typedef Expression<OPERATOR_TYPE_ADD_SUB>::ExpressionNode ExpressionNode;
	typedef Expression<OPERATOR_TYPE_ADD_SUB>::ExpressionNodes ExpressionNodes;

	class Polymorphism {
	public:
		virtual bool Special() = 0;
		virtual bool Cancel() = 0;
		virtual std::vector<ExpressionNodes::iterator> GetChildren() = 0;
		virtual bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) = 0;
		virtual Expression<OPERATOR_TYPE_MUL_DIV> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
			const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) = 0;

		virtual bool Closure(ClosureNumber& closure) = 0;
		virtual bool Closure() = 0;

		virtual bool FlatAble(const ExpressionNodes::iterator child) const = 0;
		virtual Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const = 0;

		virtual OPERATOR_TYPE_FLAG FrontDefaultFlag() const = 0;

		virtual OPERATOR_TYPE_FLAG Flag() const = 0;

		virtual OPERATOR_TYPE_LEVEL Level() const = 0;

		virtual bool SymbolExtend() = 0;

		virtual ExpressionNodes BuildPowerRootOriginNodes() const = 0;

		virtual ExpressionNodes BuildPowerRootDriverNodes() const = 0;

		virtual ExpressionNodes BuildLogarithmOriginNodes() const = 0;

		virtual ExpressionNodes BuildMulNodes() const = 0;

		virtual std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Reduce() const;

		virtual bool ExpandExpression() const;

		virtual std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const;

		virtual bool Signed();

		template<typename ChildOperatorType>
		static std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> Closures(const std::vector<ExpressionNodes::iterator>& closures,
			const std::vector<ExpressionNodes::iterator>& exps);

		static Expression<OPERATOR_TYPE_MUL_DIV> NodesBuild(const std::vector<ExpressionNodes::const_iterator>& nodes, OPERATOR_TYPE_FLAG reciprocal);

		static const Node* Visit(const ExpressionNode& node);

		static Node* Visit(ExpressionNode& node);
	};

	class PolymorphismAddSub : public Polymorphism {
	public:
		PolymorphismAddSub(Expression<OPERATOR_TYPE_ADD_SUB>& exp);
		bool Special() override;
		bool Cancel() override;
		std::vector<ExpressionNodes::iterator> GetChildren() override;
		bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
		Expression<OPERATOR_TYPE_MUL_DIV> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
			const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) override;

		bool Closure(ClosureNumber& closure) override;
		bool Closure() override;


		bool FlatAble(const ExpressionNodes::iterator child) const override;
		Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const override;

		OPERATOR_TYPE_FLAG FrontDefaultFlag() const override;

		OPERATOR_TYPE_FLAG Flag() const override;

		OPERATOR_TYPE_LEVEL Level() const override;

		bool SymbolExtend() override;

		ExpressionNodes BuildPowerRootOriginNodes() const override;

		ExpressionNodes BuildPowerRootDriverNodes() const override;

		ExpressionNodes BuildLogarithmOriginNodes() const override;

		ExpressionNodes BuildMulNodes() const override;

		bool Signed() override;

	private:
		static Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpter(const ExpressionNode* node);

		static Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv(const SymbolWrapper& symbol);
	private:
		bool CheckCombine(expression::Expression<OPERATOR_TYPE_LOGARITHM>& one, expression::Expression<OPERATOR_TYPE_LOGARITHM>& other);
		bool CollectCommonChildFull(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start);
		bool CollectCommonChildPartial(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start);

		bool NodesSigned();
		bool FrontNodeSigned();

		Expression<OPERATOR_TYPE_ADD_SUB>& m_exp;
	};

	class PolymorphismMulDiv : public Polymorphism {
	public:
		PolymorphismMulDiv(Expression<OPERATOR_TYPE_MUL_DIV>& exp);
		bool Special() override;
		bool Cancel() override;
		std::vector<ExpressionNodes::iterator> GetChildren() override;
		bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
		Expression<OPERATOR_TYPE_MUL_DIV> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
			const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) override;

		bool Closure(ClosureNumber& closure) override;
		bool Closure() override;

		bool FlatAble(const ExpressionNodes::iterator child) const override;
		Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const override;

		OPERATOR_TYPE_FLAG FrontDefaultFlag() const override;

		OPERATOR_TYPE_FLAG Flag() const override;

		OPERATOR_TYPE_LEVEL Level() const override;

		bool SymbolExtend() override;

		ExpressionNodes BuildPowerRootOriginNodes() const override;

		ExpressionNodes BuildPowerRootDriverNodes() const override;

		ExpressionNodes BuildLogarithmOriginNodes() const override;

		ExpressionNodes BuildMulNodes() const override;

		bool ExpandExpression() const override;

		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const override;

		std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Reduce() const override;

		bool Signed() override;

		template<typename ChildOperatorType>
		bool ClosureExp();


	private:
		Expression<OPERATOR_TYPE_MUL_DIV>& m_exp;

	private:
		static Expression<OPERATOR_TYPE_POWER_ROOT> GetCommonAdpter(const ExpressionNode* node);

		static Expression<OPERATOR_TYPE_POWER_ROOT> GetCommonAdpterPowerRoot(const SymbolWrapper& symbol);
	private:
		bool MulClosure();
		bool DivClosure();
		std::optional<bool> Divisors();
		std::optional<bool> Reduction();
		bool ClosurePower(ClosureNumber& closure);
		bool ClosureRoot(ClosureNumber& closure);

		int NodesSigned();

		ExpressionNodes BuildCommonNodes(ExpressionNodes::const_iterator pos) const;

		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandMulExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const;
	
		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandDivExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const;
	
		size_t GetDivisorCount() const;
	};

	class PolymorphismPowerRoot : public Polymorphism {
	public:
		PolymorphismPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT>& exp);
		bool Special() override;
		bool Cancel() override;
		std::vector<ExpressionNodes::iterator> GetChildren() override;
		bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
		Expression<OPERATOR_TYPE_MUL_DIV> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
			const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) override;

		bool Closure(ClosureNumber& closure) override;
		bool Closure() override;


		bool FlatAble(const ExpressionNodes::iterator child) const override;
		Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const override;

		OPERATOR_TYPE_FLAG FrontDefaultFlag() const override;

		OPERATOR_TYPE_FLAG Flag() const override;

		OPERATOR_TYPE_LEVEL Level() const override;

		bool SymbolExtend() override;

		ExpressionNodes BuildPowerRootOriginNodes() const override;

		ExpressionNodes BuildPowerRootDriverNodes() const override;

		ExpressionNodes BuildLogarithmOriginNodes() const override;

		ExpressionNodes BuildMulNodes() const override;

		bool ExpandExpression() const override;

		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const override;

		std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Reduce() const override;

		bool Signed() override;

		const Node* Origin() const;

		template<typename ChildOperatorType>
		bool ClosureExp();

		static bool IsOriginEqualPositiveOne(const ExpressionNode& node);
		static bool IsDriverEqualZero(const ExpressionNode& node);
		static bool IsDriverEqualPositiveOne(const ExpressionNode& node);
	private:

		bool PowerClosure();
		bool RootClosure();

		int DriversSigned();

		std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> ExpandAddSubOrigin(const Polymorphism& exp) const;

		std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> ExpandMulDivOrigin(const Polymorphism& exp) const;

		std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> ExpandAddSubDriver(const Polymorphism& exp) const;

		std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> ExpandMulDivDriver(const Polymorphism& exp) const;
	private:
		static bool CancelRoot(const ExpressionNode& one, const ExpressionNode& other);
		static std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> CancelLogarithm(const ExpressionNode& base, const ExpressionNode& mixture);
		static bool ContainFront(const std::list<ExpressionNode>& nodes);

	private:
		Expression<OPERATOR_TYPE_POWER_ROOT>& m_exp;
	};

	class PolymorphismLogarithm : public Polymorphism {
	public:
		PolymorphismLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp);
		bool Special() override;
		bool Cancel() override;
		std::vector<ExpressionNodes::iterator> GetChildren() override;
		bool CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) override;
		Expression<OPERATOR_TYPE_MUL_DIV> BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
			const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) override;

		bool Closure(ClosureNumber& closure) override;
		bool Closure() override;

		bool FlatAble(const ExpressionNodes::iterator child) const override;
		Expression<OPERATOR_TYPE_MUL_DIV> GetCommonAdpterMulDiv() const override;

		OPERATOR_TYPE_FLAG FrontDefaultFlag() const override;

		OPERATOR_TYPE_FLAG Flag() const override;

		OPERATOR_TYPE_LEVEL Level() const override;

		bool SymbolExtend() override;

		ExpressionNodes BuildPowerRootOriginNodes() const override;

		ExpressionNodes BuildPowerRootDriverNodes() const override;

		ExpressionNodes BuildLogarithmOriginNodes() const override;

		ExpressionNodes BuildMulNodes() const override;

		bool ExpandExpression() const override;

		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const override;

		std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Reduce() const override;

	private:

		bool LogarithmClosure();

		std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> ExpandMulDivOrigin(const Polymorphism& exp) const;
	
		std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> ExpandPowerRootOrigin(const Polymorphism& exp) const;

	private:
		static std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> CancelLogarithm(const ExpressionNode& base, const ExpressionNode& mixture);
	private:
		Expression<OPERATOR_TYPE_LOGARITHM>& m_exp;
	};
}

#endif