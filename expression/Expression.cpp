#include <map>

#include "Expression.hpp"


namespace expression {
	Expression<OPERATOR_TYPE_POWER_ROOT> Power(const number::Complex &number, const number::Complex &exponent) {
		return Expression<OPERATOR_TYPE_POWER_ROOT>(Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(number), POWER,
			Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(exponent));
	}
	Expression<OPERATOR_TYPE_POWER_ROOT> Power(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_POWER_ROOT>(number.Value(), POWER, exponent.Value());
	}
	Expression<OPERATOR_TYPE_POWER_ROOT> Root(const expression::ClosureNumber &number, const expression::ClosureNumber &exponent) {
		return Expression<OPERATOR_TYPE_POWER_ROOT>(number.Value(), ROOT, exponent.Value());
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition){
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_ADD_SUB> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_MUL_DIV> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &number, const expression::Expression<OPERATOR_TYPE_POWER_ROOT> &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_ADD_SUB> operator+(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &addition) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, ADD, addition);
	}

	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}
	Expression<OPERATOR_TYPE_ADD_SUB> operator-(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &subtrahend) {
		return Expression<OPERATOR_TYPE_ADD_SUB>(number, SUB, subtrahend);
	}

	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator*(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &multiplier) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, MUL, multiplier);
	}
	
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_ADD_SUB> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}
	Expression<OPERATOR_TYPE_MUL_DIV> operator/(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &number, const expression::ClosureNumber &divisor) {
		return Expression<OPERATOR_TYPE_MUL_DIV>(number, DIV, divisor);
	}

	Expression<OPERATOR_TYPE_MUL_DIV> Collect(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &exp, size_t count) {
		Expression<OPERATOR_TYPE_MUL_DIV> collect(exp);
		return collect;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::Polymorphism::CollectSigned() {
		return false;
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
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::Polymorphism::NodesBuild(const std::vector<ExpressionNodes::const_iterator>& nodes, OPERATOR_TYPE_FLAG reciprocal) {
		Expression<OPERATOR_TYPE_MUL_DIV> child;
		if (nodes.empty()) {
			child.AppendNode(expression::ClosureNumber(1));
			Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
		}
		else {
			for (auto& node : nodes) {
				std::visit([&child, &reciprocal](auto&& n) {
					if (reciprocal == n.Flag()) {
						child.AppendNode(Reciprocal(n));
						Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_DIV);
					}
					else {
						child.AppendNode(n);
						Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					}
				}, *node);
			}
		}
		return child;
	}

	template<typename OperatorType>
	Expression<OperatorType>::PolymorphismAddSub::PolymorphismAddSub(Expression<OPERATOR_TYPE_ADD_SUB> &exp) :m_exp(exp) {

	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (auto &node : nodes) {
			if (Visit(*node)->EqualZero()) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectCancel() {
		return false;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		if (CollectCommonChildFull(exps, start)) {
			return true;
		}
		if (CollectCommonChildPartial(exps, start)) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismAddSub::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		return Expression<OPERATOR_TYPE_MUL_DIV>();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		
		expression::Expression<OPERATOR_TYPE_MUL_DIV> &left = std::get<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(**start);
		const std::optional<number::Fraction> &leftFraction = Exhale(left);
		if (!leftFraction.has_value()) {
			return false;
		}

		for (auto index = ++start; index != exps.end(); ++index) {

			expression::Expression<OPERATOR_TYPE_MUL_DIV> &right = std::get<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(**index);
			const std::optional<number::Fraction> &rightFraction = Exhale(right);
			if (!rightFraction.has_value()) {
				continue;
			}

			Expression<OPERATOR_TYPE_ADD_SUB> combine = expression::Expression<OPERATOR_TYPE_MUL_DIV>::Absorb(leftFraction.value() + rightFraction.value());
			combine.SetOperator(OPERATOR_TYPE_FLAG_ADD);
			m_exp.AppendNode(combine);

			m_exp.RemoveNode(*index);
			exps.erase(index);
			return true;
		}

		return true;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectClosure() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<expression::ClosureNumber>();
		if (2 > closures.size()) {
			return false;
		}
		expression::ClosureNumber& collect = std::get<expression::ClosureNumber>(*closures.front());
		typename std::vector<ExpressionNodes::iterator>::iterator itor = closures.begin();
		while (++itor != closures.end()) {
			const expression::ClosureNumber& closure = std::get<expression::ClosureNumber>(**itor);
			closure.IsAdd() ? collect += closure : collect -= closure;
			m_exp.RemoveNode(*itor);
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismAddSub::SetOpenReduction(const Expression<OPERATOR_TYPE_MUL_DIV>& reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismAddSub::GetOpenReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismAddSub::SetFractionReduction(const Expression<OPERATOR_TYPE_ADD_SUB> &reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Expression<OperatorType>::PolymorphismAddSub::GetFractionReduction() const {
		return std::nullopt;
	}

	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::FlatAble(const ExpressionNodes::iterator child) const {
		return true;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismAddSub::GetCommonAdpterMulDiv() const {
		return Expression<OPERATOR_TYPE_MUL_DIV>();
	}
	template<typename OperatorType>
	OPERATOR_TYPE_FLAG Expression<OperatorType>::PolymorphismAddSub::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_ADD;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectSymbol() {
		auto symbols = m_exp.GetAll<Symbol>();
		for (auto &symbol : symbols) {
			if (SYMBOL(std::get<Symbol>(*symbol).Name()).ExtendAddSub(m_exp)) {
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectSigned() {
		if (CollectNodesSigned()) {
			return true;
		}
		if (CollectFrontNodeSigned()) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	std::optional<number::Fraction> Expression<OperatorType>::PolymorphismAddSub::Exhale(const expression::Expression<OPERATOR_TYPE_MUL_DIV> &exp) {
		if (exp.IsSingle()) {
			if (!std::get_if<expression::ClosureNumber>(&exp.Front())) {
				return std::nullopt;
			}
			return number::Fraction(1, std::get<expression::ClosureNumber>(exp.Front()).Value(), exp.IsAdd());
		}
		else if (2 == exp.Size()) {
			if (!std::get_if<expression::ClosureNumber>(&exp.Front())) {
				return std::nullopt;
			}
			if (!std::get_if<expression::ClosureNumber>(&exp.Back())) {
				return std::nullopt;
			}
			return number::Fraction(std::get<expression::ClosureNumber>(exp.Front()).Value(),
				std::get<expression::ClosureNumber>(exp.Back()).Value(), exp.IsAdd());
		}
		else {
			return std::nullopt;
		}
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismAddSub::GetCommonAdpter(const ExpressionNode* node)
	{
		if (const expression::Symbol* symbol = std::get_if<expression::Symbol>(node)) {
			return GetCommonAdpterMulDiv(*symbol);
		}
		else if (const expression::Expression<OPERATOR_TYPE_MUL_DIV>* exp1 = std::get_if<expression::Expression<OPERATOR_TYPE_MUL_DIV>>(node)) {
			return exp1->GetCommonAdpterMulDiv();
		}
		else if (const expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp2 = std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(node)) {
			return exp2->GetCommonAdpterMulDiv();
		}
		else if (const expression::Expression<OPERATOR_TYPE_LOGARITHM>* exp3 = std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(node)) {
			return exp3->GetCommonAdpterMulDiv();
		}
		return Expression<OPERATOR_TYPE_MUL_DIV>();
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismAddSub::GetCommonAdpterMulDiv(const Symbol& symbol) {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(number::Integer(1), MUL, symbol);
		exp.SetOperator(symbol.Flag());
		return exp;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CheckCombine(expression::Expression<OPERATOR_TYPE_LOGARITHM>& one, expression::Expression<OPERATOR_TYPE_LOGARITHM>& other) {
		std::vector<ExpressionNodes::iterator> oneNodes = one.GetAll();
		
		std::vector<ExpressionNodes::iterator> otherNodes = other.GetAll();
		
		for (const auto &oneNode : oneNodes) {
			for (const auto &otherNode : otherNodes) {
				if (Visit(*oneNode)->IsLogarithm() && Visit(*otherNode)->IsLogarithm() &&
					Visit(*oneNode)->IsEqual(*Visit(*otherNode))) {
					ExpressionNode base = *oneNode;

					one.RemoveNode(oneNode);
					other.RemoveNode(otherNode);

					expression::Expression<OPERATOR_TYPE_MUL_DIV> power;
					power.AppendChild(one);

					other.SetOperator(other.IsAdd() ? OPERATOR_TYPE_FLAG_MUL : OPERATOR_TYPE_FLAG_DIV);

					power.AppendChild(other);

					expression::Expression<OPERATOR_TYPE_POWER_ROOT> logarithm;
					logarithm.AppendChild(power);
					logarithm.AppendNode(base);

					m_exp.AppendChild(logarithm);

					return true;
				}
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectCommonChildFull(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start){
		expression::Expression<OPERATOR_TYPE_MUL_DIV> left = GetCommonAdpter(&**start);

		for (auto index = start + 1; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_MUL_DIV> right = GetCommonAdpter(&**index);

			const std::optional<expression::Expression<OPERATOR_TYPE_MUL_DIV>>& collect = left.CollectCommon(right);
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
	bool Expression<OperatorType>::PolymorphismAddSub::CollectCommonChildPartial(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		if (expression::Expression<OPERATOR_TYPE_LOGARITHM>* left = std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(&**start)) {
			for (auto index = start + 1; index != exps.end(); ++index) {
				if (expression::Expression<OPERATOR_TYPE_LOGARITHM>* right = std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(&**index)) {
					if (CheckCombine(*left, *right)) {
						m_exp.RemoveNode(*start);
						m_exp.RemoveNode(*index);
						return true;
					}
				}
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectNodesSigned() {
		auto node = m_exp.begin();
		while (node != m_exp.end()) {
			if (Visit(*node)->CollectAddSubSigned()) {
				return true;
			}
			node++;
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismAddSub::CollectFrontNodeSigned() {
		auto front = m_exp.Front();
		if (Visit(front)->IsSub()) {
			for (auto& node : m_exp) {
				Visit(node)->SetOperator(Visit(node)->IsAdd() ? 
					OPERATOR_TYPE_FLAG_SUB : OPERATOR_TYPE_FLAG_ADD);
			}
			m_exp.Opposite();
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	Expression<OperatorType>::PolymorphismMulDiv::PolymorphismMulDiv(Expression<OPERATOR_TYPE_MUL_DIV> &exp) :
		m_exp(exp) {
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		const std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (size_t index = 0; index < nodes.size(); ++ index) {
			const auto &node = nodes.at(index);
			if (Visit(*node)->EqualZero()) {
				m_exp.Clear();
				m_exp.AddClosure(ClosureNumber(0));
				return true;
			}
			else if (Visit(*node)->EqualPositiveOne() &&
				!(index == 0 && nodes.size() > 1 && Visit(*nodes.at(1))->IsDiv())) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectCancel() {
		return false;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> left = GetCommonAdpter(&**start);
		for (auto index = start + 1; index != exps.end(); ++index) {
			expression::Expression<OPERATOR_TYPE_POWER_ROOT> right = GetCommonAdpter(&**index);
			const std::optional<expression::Expression<OPERATOR_TYPE_POWER_ROOT>> &collect = left.CollectCommon(right);
			if (collect.has_value()) {
				m_exp.ReplaceSingle(*start, expression::Expression<OPERATOR_TYPE_POWER_ROOT>(collect.value()).SetChild());
				m_exp.RemoveNode(*index);
				exps.erase(index);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismMulDiv::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		
		const Expression<OPERATOR_TYPE_MUL_DIV> &childLeft = Polymorphism::NodesBuild(leftChildren, OPERATOR_TYPE_FLAG_DIV);
		
		const Expression<OPERATOR_TYPE_MUL_DIV> &childRight = Polymorphism::NodesBuild(rightChildren, OPERATOR_TYPE_FLAG_DIV);
		
		Expression<OPERATOR_TYPE_ADD_SUB> child = OPERATOR_TYPE_FLAG_SUB == right ?
			Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, SUB, childRight) :
			Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, ADD, childRight);
		child.SetOperator(OPERATOR_TYPE_FLAG_MUL);

		Expression<OPERATOR_TYPE_MUL_DIV> collect;
		for (auto &common : commons) {
			collect.AppendNode(common);
		}
		collect.AppendChild(child.SetChild());
		
		return collect;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectClosure(ClosureNumber &closure) {

		if (m_exp.Size() > 2) {
			return false;
		}

		if(closure.IsNone()) {
			switch (m_exp.Flag())
			{
			case OPERATOR_TYPE_FLAG_POWER:
			{
				return CollectClosurePower(closure);
			}
				break;
			case OPERATOR_TYPE_FLAG_ROOT:
			{
				return CollectClosureRoot(closure);
			}
				break;
			default:
				break;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectClosure() {
		if (CollectMulClosure()) {
			return true;
		}
		if (CollectDivClosure()) {
			return true;
		}
		if (CollectClosureExp<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		if (CollectClosureExp<OPERATOR_TYPE_POWER_ROOT>()) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismMulDiv::SetOpenReduction(const Expression<OPERATOR_TYPE_MUL_DIV>& reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismMulDiv::GetOpenReduction() const {
		return std::nullopt;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismMulDiv::SetFractionReduction(const Expression<OPERATOR_TYPE_ADD_SUB> &reduction) {
		m_reduction = std::make_unique<Expression<OPERATOR_TYPE_ADD_SUB>>(reduction);
	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Expression<OperatorType>::PolymorphismMulDiv::GetFractionReduction() const {
		if (m_reduction) {
			return *m_reduction;
		}
		else {
			return std::nullopt;
		}
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::FlatAble(const ExpressionNodes::iterator child) const {
		return true;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismMulDiv::GetCommonAdpterMulDiv() const {
		return m_exp;
	}
	template<typename OperatorType>
	OPERATOR_TYPE_FLAG Expression<OperatorType>::PolymorphismMulDiv::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_MUL;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectSymbol() {
		auto symbols = m_exp.GetAll<Symbol>();
		for (auto& symbol : symbols) {
			if (SYMBOL(std::get<Symbol>(*symbol).Name()).ExtendMulDiv(m_exp)) {
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectSigned() {
		int signedCount = CollectNodesSigned();

		if (1 == signedCount % 2) {
			m_exp.Opposite();
		}

		return signedCount > 0;
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectClosureExp() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<ClosureNumber>();
		if (closures.empty()) {
			return false;
		}

		std::vector<ExpressionNodes::iterator> exps = m_exp.GetAll<Expression<ChildOperatorType>>();
		if (exps.empty()) {
			return false;
		}

		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_POWER_ROOT> Expression<OperatorType>::PolymorphismMulDiv::GetCommonAdpter(const ExpressionNode* node) {
		if (const expression::Symbol* symbol = std::get_if<expression::Symbol>(node)) {
			return GetCommonAdpterPowerRoot(*symbol);
		}
		else if (const expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(node)) {
			return *exp;
		}
		return expression::Expression<OPERATOR_TYPE_POWER_ROOT>();
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_POWER_ROOT> Expression<OperatorType>::PolymorphismMulDiv::GetCommonAdpterPowerRoot(const Symbol& symbol) {
		Expression<OPERATOR_TYPE_POWER_ROOT> exp(symbol, POWER, number::Integer(1));
		exp.SetOperator(symbol.Flag());
		return exp;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectMulClosure() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<expression::ClosureNumber>();
		
		if (2 > closures.size()) {
			return false;
		}
		expression::ClosureNumber& collect = std::get<expression::ClosureNumber>(*closures.front());
		typename std::vector<ExpressionNodes::iterator>::iterator itor = closures.begin();
		while (++itor != closures.end()) {
			const expression::ClosureNumber& closure = std::get<expression::ClosureNumber>(**itor);
			if (OPERATOR_TYPE_FLAG_MUL == closure.Flag()) {
				collect *= closure;
			}
			else {
				continue;
			}
			m_exp.RemoveNode(*itor);
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectDivClosure() {

		auto collect = CollectDivisors();
		if (collect.has_value()) {
			return collect.value();
		}

		auto reduction = CollectReduction();
		if (reduction.has_value()) {
			return reduction.value();
		}
		
		return false;
	}
	template<typename OperatorType>
	std::optional<bool> Expression<OperatorType>::PolymorphismMulDiv::CollectDivisors() {
		std::vector<ExpressionNodes::iterator> closureDivisors =
			m_exp.GetAll<expression::ClosureNumber>(
				[](const expression::ClosureNumber& number) {
					return OPERATOR_TYPE_FLAG_DIV == number.Flag();
				}
		);
		if (closureDivisors.empty()) {
			return false;
		}

		expression::ClosureNumber& divFront = std::get<expression::ClosureNumber>(*closureDivisors.front());
		number::Integer collect(divFront.Value());
		typename std::vector<ExpressionNodes::iterator>::iterator itor = closureDivisors.begin();
		while (++itor != closureDivisors.end()) {
			const expression::ClosureNumber& closure = std::get<expression::ClosureNumber>(**itor);
			collect *= closure.Value();
			m_exp.RemoveNode(*itor);
			divFront = expression::ClosureNumber(collect, OPERATOR_TYPE_FLAG_DIV);
			return true;
		}
		return std::nullopt;
	}
	template<typename OperatorType>
	std::optional<bool> Expression<OperatorType>::PolymorphismMulDiv::CollectReduction() {
		std::optional<ExpressionNodes::iterator> closureDivisor =
			m_exp.GetFirst<expression::ClosureNumber>(
				[](const expression::ClosureNumber& number) {
					return number.IsDiv();
				}
		);
		if (!closureDivisor.has_value()) {
			return false;
		}

		number::Integer collect(std::get<expression::ClosureNumber>(*closureDivisor.value()).Value());

		std::vector<ExpressionNodes::iterator> closureMultipliers =
			m_exp.GetAll<expression::ClosureNumber>(
				[](const expression::ClosureNumber& number) {
					return number.IsMul();
				}
		);
		if (closureMultipliers.empty()) {
			return false;
		}

		expression::ClosureNumber& mulFront = std::get<expression::ClosureNumber>(*closureMultipliers.front());

		const number::Fraction reduce(mulFront.Value(), collect);
		if (reduce.IsInteger()) {
			*closureMultipliers.front() = number::Integer(reduce.ReductionInteger());
			m_exp.RemoveNode(closureDivisor.value());
			return true;
		}
		else if (!(reduce.Numerator() == mulFront.Value().Value() &&
			reduce.Denominator() == collect.Value() &&
			reduce.IsPositive() == (mulFront.Value().IsPositive() == collect.Value().IsPositive()))) {
			*closureMultipliers.front() = number::Integer(reduce.Numerator());
			*closureDivisor.value() = expression::ClosureNumber(reduce.Denominator(), OPERATOR_TYPE_FLAG_DIV);
			return true;
		}

		return std::nullopt;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectClosurePower(ClosureNumber& closure) {
		std::optional<ExpressionNodes::iterator> multiplier = m_exp.GetFirst<ClosureNumber>(
			[](const ClosureNumber& node) {return node.Value().IsPositive() && node.IsMul(); });
		if (!multiplier.has_value()) {
			return false;
		}

		closure = ClosureNumber(number::Fraction::Power(closure.Value(),
			std::get<ClosureNumber>(*multiplier.value()).Value()).Numerator());

		m_exp.RemoveNode(multiplier.value());

		if(m_exp.IsSingle() && Visit(m_exp.Front())->IsDiv()){
			Visit(m_exp.Front())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
			m_exp.SetOperator(OPERATOR_TYPE_FLAG_ROOT);
		}

		return true;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismMulDiv::CollectClosureRoot(ClosureNumber& closure) {
		std::optional <ExpressionNodes::iterator> divisor = m_exp.GetLast<ClosureNumber>(
			[](const ClosureNumber& node) {return node.Value().IsPositive() && OPERATOR_TYPE_FLAG_DIV == node.Flag(); });
		if (!divisor.has_value()) {
			return false;
		}

		closure = ClosureNumber(number::Fraction::Power(closure.Value(),
			std::get<ClosureNumber>(*divisor.value()).Value()).Numerator());

		m_exp.RemoveNode(divisor.value());

		if (m_exp.IsSingle() && Visit(m_exp.Front())->IsDiv()) {
			Visit(m_exp.Front())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
			m_exp.SetOperator(OPERATOR_TYPE_FLAG_POWER);
		}

		return true;
	}
	template<typename OperatorType>
	int Expression<OperatorType>::PolymorphismMulDiv::CollectNodesSigned() {
		int signedCount = 0;
		auto node = m_exp.begin();
		while (node != m_exp.end()) {
			if (Visit(*node)->CollectMulDivSigned()) {
				signedCount++;
			}
			node++;
		}
		return signedCount;
	}
	
	template<typename OperatorType>
	Expression<OperatorType>::PolymorphismPowerRoot::PolymorphismPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) :
		m_exp(exp) {

	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectSpecial() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (auto &node : nodes) {
			if (IsOriginEqualPositiveOne(*node) || IsDriverEqualZero(*node)) {
				m_exp.Clear();
				m_exp.AddClosure(ClosureNumber(1));
				return true;
			}
			else if (IsDriverEqualPositiveOne(*node)) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CancelRoot(const ExpressionNode &one, const ExpressionNode& other) {
		return (Expression<OperatorType>::Visit(one)->IsPower() && Expression<OperatorType>::Visit(other)->IsRoot()) ||
			(Expression<OperatorType>::Visit(one)->IsRoot() && Expression<OperatorType>::Visit(other)->IsPower());
	}
	template<typename OperatorType>
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismPowerRoot::CancelLogarithm(const ExpressionNode &base, const ExpressionNode &mixture) {
		if (const expression::Expression<OPERATOR_TYPE_LOGARITHM>* exp =
			std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(&mixture)) {
			std::vector<ExpressionNodes::const_iterator> nodes = exp->GetAll();
			
			bool isEqualBaseExponent = false;

			Expression<OPERATOR_TYPE_POWER_ROOT> newExponent;
			for (size_t index = 0; index < nodes.size(); ++index) {
				ExpressionNode node(*nodes.at(index));

				if (Expression<OperatorType>::Visit(node)->IsNone()) {
					newExponent.AppendNode(node);
				}
				else {
					if (isEqualBaseExponent) {
						Expression<OperatorType>::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_ROOT);
						newExponent.AppendNode(node);
					}
					else {
						if (!Expression<OperatorType>::Visit(node)->IsEqual(
							*Expression<OperatorType>::Visit(base), false, true)) {
							Expression<OperatorType>::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_ROOT);
							newExponent.AppendNode(node);
						}
						else {
							isEqualBaseExponent = true;
						}
					}
				}
			}
			if (isEqualBaseExponent) {
				return newExponent;
			}
			else {
				return std::nullopt;
			}
		}
		return std::nullopt;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::ContainFront(const std::list<ExpressionNode> &nodes) {
		for (auto& node : nodes) {
			if (Visit(node)->IsNone()) {
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectCancel() {
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (size_t i = 1; i < nodes.size(); ++i) {

			for (size_t j = i + i; j < nodes.size(); ++j) {
				if (i != j &&
					Expression<OperatorType>::Visit(*nodes.at(i))->IsEqual(
						*Expression<OperatorType>::Visit(*nodes.at(j)), false, true)) {
					if (CancelRoot(*nodes.at(i), *nodes.at(j))) {
						m_exp.RemoveNode(nodes.at(i));
						m_exp.RemoveNode(nodes.at(j));
						return true;
					}
				}
			}

			if (Expression<OperatorType>::Visit(*nodes.at(i))->IsPower()) {
				const std::optional<Expression<OPERATOR_TYPE_MUL_DIV>>& cancel = CancelLogarithm(*nodes.front(), *nodes.at(i));
				if (cancel.has_value()) {
					*nodes.at(i) = cancel.value();
					m_exp.RemoveNode(nodes.front());
					return true;
				}
			}
		}

		return false;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismPowerRoot::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		
		const Expression<OPERATOR_TYPE_MUL_DIV> &childLeft = Polymorphism::NodesBuild(leftChildren, OPERATOR_TYPE_FLAG_ROOT);

		const Expression<OPERATOR_TYPE_MUL_DIV> &childRight = Polymorphism::NodesBuild(rightChildren, OPERATOR_TYPE_FLAG_ROOT);

		if (ContainFront(commons)) {
			Expression<OPERATOR_TYPE_ADD_SUB> child = OPERATOR_TYPE_FLAG_DIV == right ?
				Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, SUB, childRight) :
				Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, ADD, childRight);
			child.SetOperator(OPERATOR_TYPE_FLAG_POWER);

			Expression<OPERATOR_TYPE_POWER_ROOT> collect;
			for (auto &common : commons) {
				collect.AppendNode(common);
			}
			collect.AppendChild(child.SetChild());
			return collect;
		}
		else {
			Expression<OPERATOR_TYPE_MUL_DIV> child = OPERATOR_TYPE_FLAG_DIV == right ?
				Expression<OPERATOR_TYPE_MUL_DIV>(childLeft, DIV, childRight) :
				Expression<OPERATOR_TYPE_MUL_DIV>(childLeft, MUL, childRight);
			child.SetOperator(OPERATOR_TYPE_FLAG_POWER);

			Expression<OPERATOR_TYPE_POWER_ROOT> collect;
			collect.AppendChild(child.SetChild());
			for (auto &common : commons) {
				collect.AppendNode(common);
			}
			return collect;
		}


	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectFractionChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectClosure(ClosureNumber &closure) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectClosure() {
		if (CollectPowerClosure()) {
			return true;
		}
		if (CollectRootClosure()) {
			return true;
		}
		if (CollectClosureExp<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		if (CollectClosureExp<OPERATOR_TYPE_MUL_DIV>()) {
			return true;
		}
		return false;
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismPowerRoot::SetOpenReduction(const Expression<OPERATOR_TYPE_MUL_DIV>& reduction) {
		m_reduction = std::make_unique<Expression<OPERATOR_TYPE_MUL_DIV>>(reduction);
	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismPowerRoot::GetOpenReduction() const {
		if (m_reduction) {
			return *m_reduction;
		}
		else {
			return std::nullopt;
		}
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismPowerRoot::SetFractionReduction(const Expression<OPERATOR_TYPE_ADD_SUB> &reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Expression<OperatorType>::PolymorphismPowerRoot::GetFractionReduction() const {
		return std::nullopt;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::FlatAble(const ExpressionNodes::iterator child) const {
		return m_exp.begin() == child;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismPowerRoot::GetCommonAdpterMulDiv() const {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(ClosureNumber(1), OPERATOR_TYPE_MUL(), m_exp);
		exp.SetOperator(m_exp.Flag());
		return exp;
	}
	template<typename OperatorType>
	OPERATOR_TYPE_FLAG Expression<OperatorType>::PolymorphismPowerRoot::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectSymbol() {
		auto symbols = m_exp.GetAll<Symbol>();
		for (auto& symbol : symbols) {
			if (SYMBOL(std::get<Symbol>(*symbol).Name()).ExtendPowerRoot(m_exp)) {
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectSigned() {
		return CollectDriversSigned();
	}
	template<typename OperatorType>
	const Node *Expression<OperatorType>::PolymorphismPowerRoot::Origin() const {
		return Visit(m_exp.Front());
	}
	template<typename OperatorType>
	template<typename ChildOperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectClosureExp() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<ClosureNumber>();
		if (closures.empty()) {
			return false;
		}

		std::vector<ExpressionNodes::iterator> exps = m_exp.GetAll<Expression<ChildOperatorType>>();
		if (exps.empty()) {
			return false;
		}

		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template CollectClosures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::IsOriginEqualPositiveOne(const ExpressionNode &node){
		return Visit(node)->IsNone() && Visit(node)->EqualPositiveOne();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::IsDriverEqualZero(const ExpressionNode &node){
		return !Visit(node)->IsNone() && Visit(node)->EqualZero();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::IsDriverEqualPositiveOne(const ExpressionNode& node) {
		return !Visit(node)->IsNone() && Visit(node)->EqualPositiveOne();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectPowerClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_POWER, [](const expression::ClosureNumber& base, const expression::ClosureNumber& exponent) {
			const number::Fraction& power = number::Fraction::Power(base.Value(), exponent.Value());
			return Absorb(power);
			});
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismPowerRoot::CollectRootClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_ROOT,
			[](const expression::ClosureNumber& power, const expression::ClosureNumber& exponent) -> std::optional < Expression<OPERATOR_TYPE_MUL_DIV> > {
				const number::Root root(power.Value(), exponent.Value());
				if (root.IsFraction()) {
					const number::Fraction& coefficient = root.ReductionCoefficient();
					return Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
	}
	template<typename OperatorType>
	int Expression<OperatorType>::PolymorphismPowerRoot::CollectDriversSigned() {
		int signedCount = 0;
		auto node = m_exp.begin();
		while (++node != m_exp.end()) {
			if (Visit(*node)->IsDisplaySigned()) {
				signedCount++;
			}
		}
		if (signedCount > 1) {
			int turnCount = 0;
			node = m_exp.begin();
			while (++node != m_exp.end() && turnCount < (0 == signedCount % 2 ? signedCount : signedCount - 1)) {
				if (Visit(*node)->CollectPowerRootSigned()) {
					turnCount++;
				}
			}
			return turnCount;
		}
		else {
			return 0;
		}
	}

	template<typename OperatorType>
	Expression<OperatorType>::PolymorphismLogarithm::PolymorphismLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp) :
		m_exp(exp) {

	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectSpecial() {
		return false;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectCancel() {
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();

		for (size_t i = 1; i < nodes.size(); ++i) {
			if (OPERATOR_TYPE_FLAG_LOGARITHM == Expression<OperatorType>::Visit(*nodes.at(i))->Flag()) {
				const std::optional<Expression<OPERATOR_TYPE_MUL_DIV>>& cancel = CancelLogarithm(*nodes.at(i), *nodes.front());
				if (cancel.has_value()) {
					m_exp.ReplaceSingle(nodes.front(), cancel.value());
					m_exp.RemoveNode(nodes.at(i));
					return true;
				}
			}
		}
		
		return false;
	}
	
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismLogarithm::BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
		const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) {
		return Expression<OPERATOR_TYPE_MUL_DIV>();
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectFractionChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectClosure(ClosureNumber& closure) {
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectClosure() {
		return CollectLogarithmClosure();
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismLogarithm::SetOpenReduction(const Expression<OPERATOR_TYPE_MUL_DIV>& reduction) {
		m_reduction = std::make_unique<Expression<OPERATOR_TYPE_MUL_DIV>>(reduction);
	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismLogarithm::GetOpenReduction() const {
		if (m_reduction) {
			return *m_reduction;
		}
		else {
			return std::nullopt;
		}
	}
	template<typename OperatorType>
	void Expression<OperatorType>::PolymorphismLogarithm::SetFractionReduction(const Expression<OPERATOR_TYPE_ADD_SUB> &reduction) {

	}
	template<typename OperatorType>
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Expression<OperatorType>::PolymorphismLogarithm::GetFractionReduction() const {
		return std::nullopt;
	}

	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::FlatAble(const ExpressionNodes::iterator child) const {
		return m_exp.begin() == child;
	}
	template<typename OperatorType>
	Expression<OPERATOR_TYPE_MUL_DIV> Expression<OperatorType>::PolymorphismLogarithm::GetCommonAdpterMulDiv() const {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(ClosureNumber(1), OPERATOR_TYPE_MUL(), m_exp);
		exp.SetOperator(m_exp.Flag());
		return exp;
	}
	template<typename OperatorType>
	OPERATOR_TYPE_FLAG Expression<OperatorType>::PolymorphismLogarithm::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectSymbol() {
		auto symbols = m_exp.GetAll<Symbol>();
		for (auto& symbol : symbols) {
			if (SYMBOL(std::get<Symbol>(*symbol).Name()).ExtendLogarithm(m_exp)) {
				return true;
			}
		}
		return false;
	}
	template<typename OperatorType>
	bool Expression<OperatorType>::PolymorphismLogarithm::CollectLogarithmClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_LOGARITHM,
			[](const expression::ClosureNumber& power, const expression::ClosureNumber& base) -> std::optional < Expression<OPERATOR_TYPE_MUL_DIV> > {
				const number::Logarithm logarithm(power.Value(), base.Value());
				if (logarithm.IsFraction()) {
					const number::Fraction& coefficient = logarithm.ReductionCoefficient();
					return Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
	}
	template<typename OperatorType>
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> Expression<OperatorType>::PolymorphismLogarithm::CancelLogarithm(const ExpressionNode& base, const ExpressionNode& mixture) {
		if (const expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp =
			std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(&mixture)) {
			std::vector<ExpressionNodes::const_iterator> nodes = exp->GetAll();

			Expression<OPERATOR_TYPE_MUL_DIV> newExponent;
			for (size_t index = 0; index < nodes.size(); ++index) {
				ExpressionNode node(*nodes.at(index));
				if (Expression<OperatorType>::Visit(*nodes.at(index))->IsNone())
				{
					if (!Expression<OperatorType>::Visit(*nodes.at(index))->IsEqual(
						*Expression<OperatorType>::Visit(base), false, true)) {
						return std::nullopt;
					}
				}
				else if (Expression<OperatorType>::Visit(*nodes.at(index))->IsPower())
				{
					Expression<OperatorType>::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					newExponent.AppendNode(node);
				}
				else
				{
					Expression<OperatorType>::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_DIV);
					newExponent.AppendNode(node);
				}
			}
			return newExponent;
		}
		return std::nullopt;
	}
}