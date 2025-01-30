#include <map>

#include "Expression.hpp"


namespace expression {
	Expression<OPERATOR_TYPE_1> Absorb(const number::Imaginary &number) {
		return Expression<OPERATOR_TYPE_1>(Absorb(number.Value()), MUL, Symbol("i"));
	}
	Expression<OPERATOR_TYPE_0> Absorb(const number::Complex &number) {
		return Expression<OPERATOR_TYPE_0>(Absorb(number.Real()), ADD, Absorb(number.Image()));
	}
	
	Expression<OPERATOR_TYPE_2> Power(const number::Complex &number, const number::Complex &exponent) {
		return Expression<OPERATOR_TYPE_2>(Absorb(number), POWER, Absorb(exponent));
	}
	Expression<OPERATOR_TYPE_2> Power(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number.Value(), POWER, exponent.Value());
	}
	Expression<OPERATOR_TYPE_2> Root(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_2>(number.Value(), ROOT, exponent.Value());
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &addition){
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_0> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_1> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_2> &number, const expression::Expression<OPERATOR_TYPE_2> &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_0> operator+(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_0>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_0> operator-(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_0>(number, SUB, subtrahend);
	}

	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_1> operator*(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_1>(number, MUL, multiplier);
	}
	
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_0> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_1> operator/(const expression::Expression<OPERATOR_TYPE_1> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_1>(number, DIV, divisor);
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
	bool Expression<OperatorType>::Polymorphism0::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		for (auto &node : nodes) {
			if (Visit(*node)->EqualZero()) {
				m_exp.RemoveNode(node);
				if (!Visit(m_exp.First())->IsAdd()) {
					Visit(m_exp.First())->Opposite();
					Visit(m_exp.First())->SetOperator(OPERATOR_TYPE_FLAG_ADD);
				}
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_1>>(exps);
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_2>>(exps);
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		expression::Expression<OPERATOR_TYPE_1> *pLeft = nullptr;
		expression::Expression<OPERATOR_TYPE_1> *pRight = nullptr;

		expression::Expression<OPERATOR_TYPE_1> left;
		if (pLeft = std::get_if<expression::Expression<OPERATOR_TYPE_1>>(&**start)) {
			left = *pLeft;
		}
		else{
			left = LevelDown(*start);
		}
		for (auto index = start + 1; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_1> right;
			if (pRight = std::get_if<expression::Expression<OPERATOR_TYPE_1>>(&**index)) {
				right = *pRight;
			}
			else {
				right = LevelDown(*index);
			}

			if (!pLeft && !pRight && left != right) {
				continue;
			}

			const std::optional<expression::Expression<OPERATOR_TYPE_1>> &collect = left.CollectCommon<OPERATOR_TYPE_0>(right);
			if (collect.has_value()) {
				m_exp.ReplaceSingle(*start, collect.value());
				m_exp.RemoveNode(*index);
				exps.erase(index);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	std::variant<Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>> Expression<OperatorType>::Polymorphism0::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) {
		return Expression<OPERATOR_TYPE_1>();
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
	bool Expression<OperatorType>::Polymorphism0::CollectClosureExp1() {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectClosureExp2() {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::SetOpenReduction(const number::Fraction &coefficient, const Expression<OPERATOR_TYPE_2> &reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_1>> Expression<OperatorType>::Polymorphism0::GetOpenReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::SetFractionReduction(const number::Fraction &fraction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_0>> Expression<OperatorType>::Polymorphism0::GetFractionReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism0::IsUnSigned() const {
		return true;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::SetUnSigned(bool isUnSigned) {
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism0::Opposite() {
		std::vector<ExpressionNodes::iterator> nodes;
		m_exp.GetAll(nodes);
		for (auto &node : nodes) {
			Visit(*node)->Opposite();
			break;
		}
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_1> Expression<OperatorType>::Polymorphism0::LevelDown(ExpressionNodes::iterator exp2) {
		Expression<OPERATOR_TYPE_1> exp1(ClosureNumber(1), OPERATOR_TYPE_MUL(), std::get<expression::Expression<OPERATOR_TYPE_2>>(*exp2));
		exp1.SetOperator(Visit(*exp2)->Flag());
		return exp1;
	}
	template<typename OperatorType>
	std::optional<number::Fraction> Expression<OperatorType>::Polymorphism0::Exhale(const expression::Expression<OPERATOR_TYPE_1> &exp1) {
		if (exp1.IsSingle()) {
			if (!std::get_if<expression::ClosureNumber>(&exp1.First())) {
				return std::nullopt;
			}
			return number::Fraction(1, std::get<expression::ClosureNumber>(exp1.First()).Value());
		}
		else if (2 == exp1.Size()) {
			if (!std::get_if<expression::ClosureNumber>(&exp1.First())) {
				return std::nullopt;
			}
			if (!std::get_if<expression::ClosureNumber>(&exp1.Last())) {
				return std::nullopt;
			}
			return number::Fraction(std::get<expression::ClosureNumber>(exp1.First()).Value(),
				std::get<expression::ClosureNumber>(exp1.Last()).Value());
		}
		else {
			return std::nullopt;
		}
	}
	template<typename OperatorType>
	Expression<OperatorType>::Polymorphism1::Polymorphism1(Expression<OPERATOR_TYPE_1> &exp) :
		m_exp(exp), m_reduction(std::make_unique<Expression<OPERATOR_TYPE_0>>()) {
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		for (size_t index = 0; index < nodes.size(); ++ index) {
			const auto &node = nodes.at(index);
			if (Visit(*node)->EqualZero()) {
				m_exp.Clear();
				m_exp.AddClosure(ClosureNumber(0));
				return true;
			}
			else if (Visit(*node)->EqualPositiveOne() &&
				(index == nodes.size() - 1 ||
					(index < nodes.size() - 1 && OPERATOR_TYPE_FLAG_DIV != Visit(*nodes.at(index + 1))->Flag()))) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
		m_exp.GetAll<expression::Expression<OPERATOR_TYPE_2>>(exps);
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		expression::Expression<OPERATOR_TYPE_2> &left = std::get<expression::Expression<OPERATOR_TYPE_2>>(**start);
		for (auto index = start + 1; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_2> &right = std::get<expression::Expression<OPERATOR_TYPE_2>>(**index);
			const std::optional<expression::Expression<OPERATOR_TYPE_2>> &collect = left.CollectCommon<OPERATOR_TYPE_1>(right);
			if (collect.has_value()) {
				m_exp.ReplaceSingle(*start, expression::Expression<OPERATOR_TYPE_2>(collect.value()).SetChild());
				m_exp.RemoveNode(*index);
				exps.erase(index);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	std::variant<Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>> Expression<OperatorType>::Polymorphism1::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) {
		
		Expression<OPERATOR_TYPE_1> childLeft(OPERATOR_TYPE_FLAG_ADD);
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

		Expression<OPERATOR_TYPE_1> childRight(OPERATOR_TYPE_FLAG_ADD);
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

		if (isOpposite) {
			childRight.Opposite();
		}

		Expression<OPERATOR_TYPE_0> child;
		if (OPERATOR_TYPE_FLAG_SUB == right) {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_SUB(), childRight);
		}
		else {
			child = Expression<OPERATOR_TYPE_0>(childLeft, OPERATOR_TYPE_ADD(), childRight);
		}
		child.SetOperator(OPERATOR_TYPE_FLAG_MUL);

		Expression<OPERATOR_TYPE_1> collect;
		for (auto &common : commons) {
			collect.AppendNode(common);
		}
		collect.AppendChild(child.SetChild());
		
		return collect;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectClosureExp1() {
		if (CollectClosureExp1<OPERATOR_TYPE_0>()) {
			return true;
		}
		if (CollectClosureExp1<OPERATOR_TYPE_2>()) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectClosureExp2() {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectClosure(ClosureNumber &closure) {

		if (m_exp.Size() > 2) {
			return false;
		}

		if(closure.IsAdd()) {
			switch (m_exp.Flag())
			{
			case OPERATOR_TYPE_FLAG_POWER:
			{
				std::optional<ExpressionNodes::iterator> multiplier = m_exp.GetFirst<ClosureNumber>(
					[](const ClosureNumber &node) {return node.Value().IsPositive() && (OPERATOR_TYPE_FLAG_MUL == node.Flag() || OPERATOR_TYPE_FLAG_ADD == node.Flag()); });
				if (!multiplier.has_value()) {
					return false;
				}
				
				closure = ClosureNumber(number::Fraction::Power(closure.Value(),
					std::get<ClosureNumber>(*multiplier.value()).Value()).Numerator());
				
				if (OPERATOR_TYPE_FLAG_DIV == m_exp.RemoveNode(multiplier.value())){
					m_exp.SetOperator(OPERATOR_TYPE_FLAG_ROOT);
				}

				return true;
			}
				break;
			case OPERATOR_TYPE_FLAG_ROOT:
			{
				std::optional <ExpressionNodes::iterator> divisor = m_exp.GetLast<ClosureNumber>(
					[](const ClosureNumber &node) {return node.Value().IsPositive() && OPERATOR_TYPE_FLAG_DIV == node.Flag(); });
				if (!divisor.has_value()) {
					return false;
				}
				
				closure = ClosureNumber(number::Fraction::Power(closure.Value(),
					std::get<ClosureNumber>(*divisor.value()).Value()).Numerator());

				if (OPERATOR_TYPE_FLAG_DIV == m_exp.RemoveNode(divisor.value())) {
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
	void Expression<OperatorType>::Polymorphism1::SetOpenReduction(const number::Fraction &coefficient, const Expression<OPERATOR_TYPE_2> &reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_1>> Expression<OperatorType>::Polymorphism1::GetOpenReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::SetFractionReduction(const number::Fraction &fraction) {
		*m_reduction = Absorb(fraction);
	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_0>> Expression<OperatorType>::Polymorphism1::GetFractionReduction() const {
		return *m_reduction;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism1::IsUnSigned() const {
		return true;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::SetUnSigned(bool isUnSigned) {
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism1::Opposite() {
		Visit(m_exp.Last())->Opposite();
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	bool Expression<OperatorType>::Polymorphism1::CollectClosureExp1() {
		std::vector<ExpressionNodes::iterator> closures;
		m_exp.GetAll<ClosureNumber>(closures);
		if (closures.empty()) {
			return false;
		}
		std::vector<ExpressionNodes::iterator> exps;
		m_exp.GetAll<Expression<ChildOperatorType>>(exps);
		if (exps.empty()) {
			return false;
		}
		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	template<typename OperatorType>
	Expression<OperatorType>::Polymorphism2::Polymorphism2(Expression<OPERATOR_TYPE_2> &exp) :
		m_exp(exp), m_reduction(std::make_unique<Expression<OPERATOR_TYPE_1>>()) {

	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::const_iterator> nodes;
		m_exp.GetAll(nodes);
		for (auto &node : nodes) {
			if (IsOriginEqualOne(*node) || IsDriverEqualZero(*node)) {
				m_exp.Clear();
				m_exp.AddClosure(ClosureNumber(1));
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::GetChildren(std::vector<ExpressionNodes::iterator> &exps) {
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	std::variant<Expression<OPERATOR_TYPE_1>, Expression<OPERATOR_TYPE_2>> Expression<OperatorType>::Polymorphism2::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons, bool isOpposite) {
		
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

		bool isCommonBase = false;
		for (auto &common : commons) {
			if (Visit(common)->IsAdd()) {
				isCommonBase = true;
				break;
			}
		}

		if (isCommonBase) {
			Expression<OPERATOR_TYPE_0> child;
			if (OPERATOR_TYPE_FLAG_DIV == right) {
				child = Expression<OPERATOR_TYPE_0>(childLeft, SUB, childRight);
			}
			else {
				child = Expression<OPERATOR_TYPE_0>(childLeft, ADD, childRight);
			}
			child.SetOperator(OPERATOR_TYPE_FLAG_POWER);
			Expression<OPERATOR_TYPE_2> collect;
			for (auto &common : commons) {
				collect.AppendNode(common);
			}
			collect.AppendChild(child.SetChild());
			return collect;
		}
		else {
			Expression<OPERATOR_TYPE_1> child;
			if (OPERATOR_TYPE_FLAG_DIV == right) {
				child = Expression<OPERATOR_TYPE_1>(childLeft, DIV, childRight);
			}
			else {
				child = Expression<OPERATOR_TYPE_1>(childLeft, MUL, childRight);
			}
			child.SetOperator(OPERATOR_TYPE_FLAG_POWER);
			Expression<OPERATOR_TYPE_2> collect;
			collect.AppendChild(child.SetChild());
			for (auto &common : commons) {
				collect.AppendNode(common);
			}
			return collect;
		}


	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectClosureExp1() {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectClosureExp2() {
		if (CollectClosureExp2<OPERATOR_TYPE_0>()) {
			return true;
		}
		if (CollectClosureExp2<OPERATOR_TYPE_1>()) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::SetOpenReduction(const number::Fraction &coefficient, const Expression<OPERATOR_TYPE_2> &reduction) {
		m_reduction->AddChild(reduction, MUL);
		m_reduction->AddClosure(coefficient.Denominator(), DIV);
		m_reduction->AddClosure(coefficient.Numerator());
	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_1>> Expression<OperatorType>::Polymorphism2::GetOpenReduction() const {
		return *m_reduction;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::SetFractionReduction(const number::Fraction &fraction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_0>> Expression<OperatorType>::Polymorphism2::GetFractionReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::IsUnSigned() const {
		return m_unsigned;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::SetUnSigned(bool isUnSigned) {
		m_unsigned = isUnSigned;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::Polymorphism2::Opposite() {
		m_unsigned = !m_unsigned;
	}
	template<typename OperatorType>
	const Node *Expression<OperatorType>::Polymorphism2::Origin() const {
		return Visit(m_exp.First());
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	bool Expression<OperatorType>::Polymorphism2::CollectClosureExp2() {
		std::vector<ExpressionNodes::iterator> closures;
		m_exp.GetAll<ClosureNumber>(closures);
		if (closures.empty()) {
			return false;
		}
		std::vector<ExpressionNodes::iterator> exps;
		m_exp.GetAll<Expression<ChildOperatorType>>(exps);
		if (exps.empty()) {
			return false;
		}
		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::IsOriginEqualOne(const ExpressionNode &node){
		return Visit(node)->IsAdd() && Visit(node)->EqualPositiveOne();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism2::IsDriverEqualZero(const ExpressionNode &node){
		return !Visit(node)->IsAdd() && Visit(node)->EqualZero();
	}
}