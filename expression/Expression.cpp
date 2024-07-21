#include <map>

#include "OpenNumber.h"
#include "Expression.hpp"


namespace expression {
	Expression<OPERATOR_TYPE_1> Absorb(const number::Imaginary &number) {
		return Expression<OPERATOR_TYPE_1>(Absorb(number.Value()), OPERATOR_TYPE_MUL(), Symbol("i"));
	}
	Expression<OPERATOR_TYPE_0> Absorb(const number::Complex &number) {
		return Expression<OPERATOR_TYPE_0>(Absorb(number.Real()), OPERATOR_TYPE_ADD(), Absorb(number.Image()));
	}
	
	Expression<OPERATOR_TYPE_2> Power(const number::Complex &number, const number::Complex &exponent) {
		return Expression<OPERATOR_TYPE_2>(Absorb(number), OPERATOR_TYPE_POWER(), Absorb(exponent));
	}
	Expression<OPERATOR_TYPE_2> Power(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number.Value(), OPERATOR_TYPE_POWER(), exponent.Value());
	}
	Expression<OPERATOR_TYPE_2> Root(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number.Value(), OPERATOR_TYPE_ROOT(), exponent.Value());
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> operator+(const OpenNumber &number, const OpenNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> operator-(const OpenNumber &number, const OpenNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> operator*(const OpenNumber &number, const OpenNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> operator/(const OpenNumber &number, const OpenNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_2> Power(const expression::OpenNumber &number, const expression::OpenNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number, OPERATOR_TYPE_POWER(), exponent);
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_2> Root(const expression::OpenNumber &number, const expression::OpenNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number, OPERATOR_TYPE_ROOT(), exponent);
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &addition){
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_ADD(), addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, OPERATOR_TYPE_SUB(), subtrahend);
	}

	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_MUL(), multiplier);
	}
	
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, OPERATOR_TYPE_DIV(), divisor);
	}

	Expression<OPERATOR_TYPE_1> Collect(const expression::Expression<OPERATOR_TYPE_1> &exp, size_t count) {
		Expression<OPERATOR_TYPE_1> collect(exp);
		return collect;
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> Expression<OperatorType>::Polymorphism::CollectClosures(const std::vector<ExpressionNodes::iterator> &closures,
		const std::vector<ExpressionNodes::iterator> &exps) {
		for (auto closure = closures.begin(); closure != closures.end(); ++closure) {
			for (auto exp = exps.begin(); exp != exps.end(); ++exp) {
				if (std::get<Expression<ChildOperatorType>>(**exp).m_polymorphism->
					CollectClosure(std::get<ClosureNumber>(**closure))) {
					return *exp;
				}
			}
		}
		return std::nullopt;
	}

	template<typename OperatorType>
	Expression<OperatorType>::Polymorphism0::Polymorphism0(Expression<OPERATOR_TYPE_0> &exp) :m_exp(exp) {

	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism0::CollectSpecial(size_t count) {
		if (1 == m_exp.m_nodes.size()) {
			return 0;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		size_t completed = 0;
		for (auto &node : nodes) {
			if (Visit(*node)->EqualZero()) {
				m_exp.RemoveNode(node);
				if (++completed == count) {
					break;
				}
			}
		}
		return completed;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_1>>(exps);
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_2>>(exps);
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		expression::Expression<OPERATOR_TYPE_1> left;
		if (expression::Expression<OPERATOR_TYPE_1> *pLeft = std::get_if<expression::Expression<OPERATOR_TYPE_1>>(&**start)) {
			left = *pLeft;
		}
		else{
			left = LevelDown(*start);
		}
		for (auto index = ++start; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_1> right;
			if (expression::Expression<OPERATOR_TYPE_1> *pRight = std::get_if<expression::Expression<OPERATOR_TYPE_1>>(&**index)) {
				right = *pRight;
			}
			else {
				right = LevelDown(*index);
			}
			const std::optional<expression::Expression<OPERATOR_TYPE_1>> &collect = left.CollectCommon<OPERATOR_TYPE_0>(right);
			if (collect.has_value()) {
				m_exp.RemoveNode(*index);
				m_exp.AddChild(collect.value());
				exps.erase(index);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> Expression<OperatorType>::Polymorphism0::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) {
		return Expression<OPERATOR_TYPE_0>();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::IsEqual(const Node &other) const {
		return true;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		
		expression::Expression<OPERATOR_TYPE_1> &left = std::get<expression::Expression<OPERATOR_TYPE_1>>(**start);
		const std::optional<number::Fraction> &leftFraction = Exhale(left);
		if (!leftFraction.has_value()) {
			return false;
		}

		for (auto index = ++start; index != exps.end(); ++index) {

			expression::Expression<OPERATOR_TYPE_1> &right = std::get<expression::Expression<OPERATOR_TYPE_1>>(**index);
			const std::optional<number::Fraction> &rightFraction = Exhale(right);
			if (!rightFraction.has_value()) {
				continue;
			}

			switch (right.Flag())
			{
			case OPERATOR_TYPE_FLAG_ADD:
				m_exp.AddChild(expression::Expression<OPERATOR_TYPE_1>::Absorb(leftFraction.value() + rightFraction.value()));
				break;
			case OPERATOR_TYPE_FLAG_SUB:
				m_exp.AddChild(expression::Expression<OPERATOR_TYPE_1>::Absorb(leftFraction.value() - rightFraction.value()));
				break;
			default:
				continue;
				break;
			}
			m_exp.RemoveNode(*index);
			exps.erase(index);
			return true;
		}

		return true;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism0::CollectClosureExp1(size_t count) {
		return 0;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism0::CollectClosureExp2(size_t count) {
		return 0;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::MarkFirst(Node *first) {

	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> Expression<OperatorType>::Polymorphism0::LevelDown(ExpressionNodes::iterator exp2) {
		Expression<OPERATOR_TYPE_1> exp1(ClosureNumber(1), OPERATOR_TYPE_MUL(), std::get<expression::Expression<OPERATOR_TYPE_2>>(*exp2));
		exp1.SetOperator(Visit(*exp2)->Flag());
		return exp1;
	}
	template<typename OperatorType>
	std::optional<number::Fraction> Expression<OperatorType>::Polymorphism0::Exhale(const expression::Expression<OPERATOR_TYPE_1> &exp1) {
		if (1 == exp1.m_nodes.size()) {
			if (!std::get_if<expression::ClosureNumber>(&exp1.m_nodes.front())) {
				return std::nullopt;
			}
			return number::Fraction(1, std::get<expression::ClosureNumber>(exp1.m_nodes.front()).Value());
		}
		else if (2 == exp1.m_nodes.size()) {
			if (!std::get_if<expression::ClosureNumber>(&exp1.m_nodes.front())) {
				return std::nullopt;
			}
			if (!std::get_if<expression::ClosureNumber>(&exp1.m_nodes.back())) {
				return std::nullopt;
			}
			return number::Fraction(std::get<expression::ClosureNumber>(exp1.m_nodes.front()).Value(),
				std::get<expression::ClosureNumber>(exp1.m_nodes.back()).Value());
		}
		else {
			return std::nullopt;
		}
	}
	template<typename OperatorType>
	Expression<OperatorType>::Polymorphism1::Polymorphism1(Expression<OPERATOR_TYPE_1> &exp) :m_exp(exp) {

	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism1::CollectSpecial(size_t count) {
		if (1 == m_exp.m_nodes.size()) {
			return 0;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		size_t completed = 0;
		for (auto &node : nodes) {
			if (Visit(*node)->EqualZero()) {
				m_exp.m_nodes.clear();
				m_exp.AddClosure(ClosureNumber(0));
				++completed;
				break;
			}
		}
		return completed;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_2>>(exps);
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		expression::Expression<OPERATOR_TYPE_2> &left = std::get<expression::Expression<OPERATOR_TYPE_2>>(**start);
		for (auto index = ++start; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_2> &right = std::get<expression::Expression<OPERATOR_TYPE_2>>(**index);
			const std::optional<expression::Expression<OPERATOR_TYPE_2>> &collect = left.CollectCommon<OPERATOR_TYPE_1>(right);
			if (collect.has_value()) {
				m_exp.RemoveNode(*index);
				m_exp.AddChild(collect.value());
				exps.erase(index);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> Expression<OperatorType>::Polymorphism1::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) {
		Expression<OPERATOR_TYPE_0> child;

		Expression<OPERATOR_TYPE_1> childLeft;
		if (leftChildren.empty()) {
			childLeft.AppendNode(expression::ClosureNumber(1));
		}
		else {
			for (auto &diff : leftChildren) {
				std::visit([&childLeft](auto &&n) {
					if (OPERATOR_TYPE_FLAG_DIV == n.Flag()) {
						childLeft.AppendNode(Reciprocal(n));
					}
					else {
						childLeft.AppendNode(n);
					}
				}, *diff);
			}
		}

		Expression<OPERATOR_TYPE_1> childRight;
		if (rightChildren.empty()) {
			childRight.AppendNode(expression::ClosureNumber(1));
		}
		else {
			for (auto &diff : rightChildren) {
				std::visit([&childRight](auto &&n) {
					if (OPERATOR_TYPE_FLAG_DIV == n.Flag()) {
						childRight.AppendNode(Reciprocal(n));
					}
					else {
						childRight.AppendNode(n);
					}
				}, *diff);
			}
		}

		if (OPERATOR_TYPE_FLAG_SUB == right) {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_SUB(), childRight);
		}
		else {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_ADD(), childRight);
		}

		child.SetOperator(OPERATOR_TYPE_FLAG_MUL);

		return child;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::IsEqual(const Node &other) const {
		return true;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism1::CollectClosureExp1(size_t count) {
		size_t completed = 0;
		if (count == (completed += CollectClosureExp1<OPERATOR_TYPE_0>(count - completed))) {
			return completed;
		}
		if (count == (completed += CollectClosureExp1<OPERATOR_TYPE_2>(count - completed))) {
			return completed;
		}
		return completed;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism1::CollectClosureExp2(size_t count) {
		return 0;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectClosure(ClosureNumber &closure) {

		if (m_exp.m_nodes.size() > 2) {
			return false;
		}

		if(closure.IsBase()) {
			switch (m_exp.Flag())
			{
			case OPERATOR_TYPE_FLAG_POWER:
			{
				ExpressionNodes::iterator multiplier = m_exp.GetFirst<ClosureNumber>(
					[](const ClosureNumber &node) {return node.Value().IsPositive() && OPERATOR_TYPE_FLAG_MUL == node.Flag(); });
				if (multiplier == m_exp.m_nodes.end()) {
					return false;
				}
				
				closure = ClosureNumber(number::Fraction::Power(closure.Value(),
					std::get<ClosureNumber>(*multiplier).Value()).Numerator(), OPERATOR_TYPE_FLAG_POWER);
				closure.SetBase();
				m_exp.RemoveNode(multiplier);

				if (OPERATOR_TYPE_FLAG_DIV == Visit(m_exp.FirstChild())->Flag()){
					Visit(m_exp.FirstChild())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					m_exp.SetOperator(OPERATOR_TYPE_FLAG_ROOT);
				}

				return true;
			}
				break;
			case OPERATOR_TYPE_FLAG_ROOT:
			{
				ExpressionNodes::iterator divisor = m_exp.GetLast<ClosureNumber>(
					[](const ClosureNumber &node) {return node.Value().IsPositive() && OPERATOR_TYPE_FLAG_DIV == node.Flag(); });
				if (divisor == m_exp.m_nodes.end()) {
					return false;
				}
				
				closure = ClosureNumber(number::Fraction::Power(closure.Value(),
					std::get<ClosureNumber>(*divisor).Value()).Numerator(), OPERATOR_TYPE_FLAG_POWER);
				closure.SetBase();
				m_exp.RemoveNode(divisor);

				if (OPERATOR_TYPE_FLAG_DIV == Visit(m_exp.FirstChild())->Flag()) {
					Visit(m_exp.FirstChild())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					m_exp.SetOperator(OPERATOR_TYPE_FLAG_POWER);
				}

				return true;
			}
				break;
			default:
				break;
			}
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::MarkFirst(Node *first) {
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	size_t Expression<OperatorType>::Polymorphism1::CollectClosureExp1(size_t count) {
		std::vector<ExpressionNodes::iterator> closures;
		m_exp.GetAll<ClosureNumber>(closures);
		if (closures.empty()) {
			return 0;
		}
		std::vector<ExpressionNodes::iterator> exps;
		m_exp.GetAll<Expression<ChildOperatorType>>(exps);
		if (exps.empty()) {
			return 0;
		}
		size_t completed = 0;
		while (true) {
			std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
			if (exp.has_value()){
				m_exp.CheckCollectChild<ChildOperatorType>(exp.value());
				if (++completed == count) {
					break;
				}
			}
			else {
				break;
			}
		}
		return completed;
	}
	template<typename OperatorType>
	Expression<OperatorType>::Polymorphism2::Polymorphism2(Expression<OPERATOR_TYPE_2> &exp) :m_exp(exp) {

	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism2::CollectSpecial(size_t count) {
		if (1 == m_exp.m_nodes.size()) {
			return 0;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		size_t completed = 0;
		for (auto &node : nodes) {
			if (node != m_exp.m_nodes.begin() && Visit(*node)->EqualZero()) {
				m_exp.m_nodes.clear();
				m_exp.AddClosure(ClosureNumber(1));
				++completed;
				break;
			}
		}
		return completed;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_0> Expression<OperatorType>::Polymorphism2::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right) {
		Expression<OPERATOR_TYPE_0> child;

		Expression<OPERATOR_TYPE_1> childLeft;
		if (leftChildren.empty()) {
			childLeft.AppendNode(expression::ClosureNumber(1));
		}
		else {
			for (auto &diff : leftChildren) {
				std::visit([&childLeft](auto &&n) {
					if (OPERATOR_TYPE_FLAG_ROOT == n.Flag()) {
						childLeft.AppendNode(Reciprocal(n));
					}
					else {
						childLeft.AppendNode(n);
					}
				}, *diff);
			}
		}

		Expression<OPERATOR_TYPE_1> childRight;
		if (rightChildren.empty()) {
			childRight.AppendNode(expression::ClosureNumber(1));
		}
		else {
			for (auto &diff : rightChildren) {
				std::visit([&childRight](auto &&n) {
					if (OPERATOR_TYPE_FLAG_ROOT == n.Flag()) {
						childRight.AppendNode(Reciprocal(n));
					}
					else {
						childRight.AppendNode(n);
					}
				}, *diff);
			}
		}

		if (OPERATOR_TYPE_FLAG_DIV == right) {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_SUB(), childRight);
		}
		else {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_ADD(), childRight);
		}

		child.SetOperator(OPERATOR_TYPE_FLAG_POWER);
		
		return child;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::IsEqual(const Node &other) const {
		return *Base() == other;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism2::CollectClosureExp1(size_t count) {
		return 0;
	}
	template<typename OperatorType>
	size_t Expression<OperatorType>::Polymorphism2::CollectClosureExp2(size_t count) {
		size_t completed = 0;
		if (count == (completed += CollectClosureExp2<OPERATOR_TYPE_0>(count - completed))) {
			return completed;
		}
		if (count == (completed += CollectClosureExp2<OPERATOR_TYPE_1>(count - completed))) {
			return completed;
		}
		return completed;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::MarkFirst(Node *first) {
		first->SetBase();
	}
	template<typename OperatorType>
	const Node *Expression<OperatorType>::Polymorphism2::Base() const {
		return Visit(m_exp.m_nodes.front());
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	size_t Expression<OperatorType>::Polymorphism2::CollectClosureExp2(size_t count) {
		std::vector<ExpressionNodes::iterator> closures;
		m_exp.GetAll<ClosureNumber>(closures);
		if (closures.empty()) {
			return 0;
		}
		std::vector<ExpressionNodes::iterator> exps;
		m_exp.GetAll<Expression<ChildOperatorType>>(exps);
		if (exps.empty()) {
			return 0;
		}
		size_t completed = 0;
		while (true) {
			std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
			if (exp.has_value()) {
				m_exp.CheckCollectChild<ChildOperatorType>(exp.value());
				if (++completed == count) {
					break;
				}
			}
			else {
				break;
			}
		}
		return completed;
	}
}