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
	bool Polymorphism::power_root_common_switch = true;
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> Polymorphism::Reduce() const {
		return std::nullopt;
	}
	bool Polymorphism::ExpandExpression() const {
		return false;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> Polymorphism::ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		return std::nullopt;
	}
	bool Polymorphism::Signed() {
		return false;
	}
	template<typename ChildOperatorType>
	std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> Polymorphism::Closures(const std::vector<ExpressionNodes::iterator> &closures,
		const std::vector<ExpressionNodes::iterator> &exps) {
		for (auto closure = closures.begin(); closure != closures.end(); ++closure) {
			for (auto exp = exps.begin(); exp != exps.end(); ++exp) {
				if (std::get<Expression<ChildOperatorType>>(**exp).m_polymorphism->
					Closure(std::get<ClosureNumber>(**closure))) {
					return *exp;
				}
			}
		}
		return std::nullopt;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> Polymorphism::NodesBuild(const std::vector<ExpressionNodes::const_iterator>& nodes, OPERATOR_TYPE_FLAG reciprocal) {
		Expression<OPERATOR_TYPE_MUL_DIV> child;
		if (nodes.empty()) {
			child.AppendNode(expression::ClosureNumber(1));
			Polymorphism::Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
		}
		else {
			for (auto& node : nodes) {
				std::visit([&child, &reciprocal](auto&& n) {
					if (reciprocal == n.Flag()) {
						child.AppendNode(Expression<OPERATOR_TYPE_ADD_SUB>::Reciprocal(n));
						Polymorphism::Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_DIV);
					}
					else {
						child.AppendNode(n);
						Polymorphism::Visit(child.Back())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					}
				}, *node);
			}
		}
		return child;
	}
	const Node* Polymorphism::Visit(const ExpressionNode& node) {
		return Expression<OPERATOR_TYPE_NONE>::Visit(node);
	}
	Node* Polymorphism::Visit(ExpressionNode& node) {
		return Expression<OPERATOR_TYPE_NONE>::Visit(node);
	}
	bool Polymorphism::PowerRootCommon() {
		return power_root_common_switch;
	}
	void Polymorphism::PowerRootCommonOn() {
		power_root_common_switch = true;
	}
	void Polymorphism::PowerRootCommonOff() {
		power_root_common_switch = false;
	}
	PolymorphismAddSub::PolymorphismAddSub(Expression<OPERATOR_TYPE_ADD_SUB> &exp) :m_exp(exp) {

	}
	bool PolymorphismAddSub::Special() {
		if (m_exp.IsSingle()) {
			return false;
		}
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (auto &node : nodes) {
			if (Polymorphism::Visit(*node)->EqualZero()) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	bool PolymorphismAddSub::Cancel() {
		return false;
	}
	std::vector<ExpressionNodes::iterator> PolymorphismAddSub::GetChildren(){
		std::vector<ExpressionNodes::iterator> exps;
		std::vector<ExpressionNodes::iterator> symbols = m_exp.GetAll<expression::SymbolWrapper>();
		exps.insert(exps.end(), symbols.begin(), symbols.end());
		std::vector<ExpressionNodes::iterator> divs = m_exp.GetAll<expression::Expression<OPERATOR_TYPE_MUL_DIV>>();
		exps.insert(exps.end(), divs.begin(), divs.end());
		std::vector<ExpressionNodes::iterator> roots = m_exp.GetAll<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>();
		exps.insert(exps.end(), roots.begin(), roots.end());
		std::vector<ExpressionNodes::iterator> logarithms = m_exp.GetAll<expression::Expression<OPERATOR_TYPE_LOGARITHM>>();
		exps.insert(exps.end(), logarithms.begin(), logarithms.end());
		return exps;
	}
	bool PolymorphismAddSub::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		if (CollectCommonChildFull(exps, start)) {
			return true;
		}
		if (CollectCommonChildPartial(exps, start)) {
			return true;
		}
		return false;
	}
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismAddSub::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		return std::nullopt;
	}
	bool PolymorphismAddSub::Closure(ClosureNumber &closure) {
		return false;
	}
	bool PolymorphismAddSub::Closure() {
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

	bool PolymorphismAddSub::FlatAble(const ExpressionNodes::iterator child) const {
		return true;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismAddSub::GetCommonAdpterMulDiv() const {
		return Expression<OPERATOR_TYPE_MUL_DIV>();
	}
	OPERATOR_TYPE_FLAG PolymorphismAddSub::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_ADD;
	}
	OPERATOR_TYPE_FLAG PolymorphismAddSub::Flag() const {
		return m_exp.Flag();
	}
	OPERATOR_TYPE_LEVEL PolymorphismAddSub::Level() const {
		return OPERATOR_TYPE_LEVEL_ADD_SUB;
	}
	bool PolymorphismAddSub::SymbolExtend() {
		auto symbols = m_exp.GetAll<SymbolWrapper>();
		for (auto &symbol : symbols) {
			if (std::get<SymbolWrapper>(*symbol).ExtendAddSub(m_exp)) {
				return true;
			}
		}
		return false;
	}
	ExpressionNodes PolymorphismAddSub::BuildPowerRootOriginNodes() const {
		return m_exp.m_nodes;
	}
	ExpressionNodes PolymorphismAddSub::BuildPowerRootDriverNodes() const {
		return m_exp.IsPower() ? m_exp.m_nodes : ExpressionNodes();
	}
	ExpressionNodes PolymorphismAddSub::BuildLogarithmOriginNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismAddSub::BuildMulNodes() const {
		bool isUnSigned = m_exp.IsUnSigned();
		auto nodes = m_exp.m_nodes;
		for (auto& node : nodes) {
			int signedCount = (isUnSigned ? 0 : 1) + (Polymorphism::Visit(node)->IsUnSigned() ? 0 : 1) +
				(Polymorphism::Visit(node)->IsAdd() ? 0 : 1);
			Polymorphism::Visit(node)->SetUnSigned(0 == signedCount%2);
			Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_MUL);
		}
		return nodes;
	}
	bool PolymorphismAddSub::Signed() {
		if (NodesSigned()) {
			return true;
		}
		if (FrontNodeSigned()) {
			return true;
		}
		return false;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismAddSub::GetCommonAdpter(const ExpressionNode* node)
	{
		if (const expression::SymbolWrapper* symbol = std::get_if<expression::SymbolWrapper>(node)) {
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
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismAddSub::GetCommonAdpterMulDiv(const SymbolWrapper& symbol) {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(number::Integer(1), MUL, symbol);
		exp.SetOperator(symbol.Flag());
		return exp;
	}
	bool PolymorphismAddSub::CheckCombine(expression::Expression<OPERATOR_TYPE_LOGARITHM>& one, expression::Expression<OPERATOR_TYPE_LOGARITHM>& other) {
		std::vector<ExpressionNodes::iterator> oneNodes = one.GetAll();
		
		std::vector<ExpressionNodes::iterator> otherNodes = other.GetAll();
		
		for (const auto &oneNode : oneNodes) {
			for (const auto &otherNode : otherNodes) {
				if (Polymorphism::Visit(*oneNode)->IsLogarithm() && Polymorphism::Visit(*otherNode)->IsLogarithm() &&
					Polymorphism::Visit(*oneNode)->IsEqual(*Polymorphism::Visit(*otherNode))) {
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
	bool PolymorphismAddSub::CollectCommonChildFull(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start){
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
	bool PolymorphismAddSub::CollectCommonChildPartial(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) {
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
	bool PolymorphismAddSub::NodesSigned() {
		auto node = m_exp.begin();
		while (node != m_exp.end()) {
			if (Polymorphism::Visit(*node)->AddSubSigned()) {
				return true;
			}
			node++;
		}
		return false;
	}
	bool PolymorphismAddSub::FrontNodeSigned() {
		auto front = m_exp.Front();
		if (Polymorphism::Visit(front)->IsSub()) {
			for (auto& node : m_exp) {
				Polymorphism::Visit(node)->SetOperator(Polymorphism::Visit(node)->IsAdd() ?
					OPERATOR_TYPE_FLAG_SUB : OPERATOR_TYPE_FLAG_ADD);
			}
			m_exp.Opposite();
			return true;
		}
		return false;
	}
	PolymorphismMulDiv::PolymorphismMulDiv(Expression<OPERATOR_TYPE_MUL_DIV> &exp) :
		m_exp(exp) {
	}
	bool PolymorphismMulDiv::Special() {
		if (m_exp.IsSingle()) {
			return false;
		}
		const std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (size_t index = 0; index < nodes.size(); ++ index) {
			const auto &node = nodes.at(index);
			if (Polymorphism::Visit(*node)->EqualZero()) {
				m_exp.Clear();
				m_exp.AddClosure(ClosureNumber(0));
				return true;
			}
			else if (Polymorphism::Visit(*node)->EqualPositiveOne() &&
				!(index == 0 && nodes.size() > 1 && Polymorphism::Visit(*nodes.at(1))->IsDiv())) {
				m_exp.RemoveNode(node);
				return true;
			}
		}
		return false;
	}
	bool PolymorphismMulDiv::Cancel() {
		return false;
	}
	std::vector<ExpressionNodes::iterator> PolymorphismMulDiv::GetChildren(){
		std::vector<ExpressionNodes::iterator> exps;
		std::vector<ExpressionNodes::iterator> symbols = m_exp.GetAll<expression::SymbolWrapper>();
		exps.insert(exps.end(), symbols.begin(), symbols.end());
		std::vector<ExpressionNodes::iterator> roots = m_exp.GetAll<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>();
		exps.insert(exps.end(), roots.begin(), roots.end());
		return exps;
	}
	bool PolymorphismMulDiv::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
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
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismMulDiv::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		
		Expression<OPERATOR_TYPE_MUL_DIV> childLeft = Polymorphism::NodesBuild(leftChildren, OPERATOR_TYPE_FLAG_DIV);

		Expression<OPERATOR_TYPE_MUL_DIV> childRight = Polymorphism::NodesBuild(rightChildren, OPERATOR_TYPE_FLAG_DIV);

		OPERATOR_TYPE_FLAG left = m_exp.Flag();
		Expression<OPERATOR_TYPE_ADD_SUB> child =
			(OPERATOR_TYPE_FLAG_SUB == left && OPERATOR_TYPE_FLAG_SUB != right) || 
			(OPERATOR_TYPE_FLAG_SUB != left && OPERATOR_TYPE_FLAG_SUB == right) ?
			Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, SUB, childRight) : Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, ADD, childRight);
		
		Expression<OPERATOR_TYPE_MUL_DIV> collect;

		collect.AppendChild(child.SetChild());
		
		for (auto &common : commons) {
			collect.AppendNode(common);
		}

		return collect;
	}
	bool PolymorphismMulDiv::Closure(ClosureNumber &closure) {

		if (m_exp.Size() > 2) {
			return false;
		}

		if(closure.IsNone()) {
			switch (m_exp.Flag())
			{
			case OPERATOR_TYPE_FLAG_POWER:
			{
				return ClosurePower(closure);
			}
				break;
			case OPERATOR_TYPE_FLAG_ROOT:
			{
				return ClosureRoot(closure);
			}
				break;
			default:
				break;
			}
		}
		return false;
	}
	bool PolymorphismMulDiv::Closure() {
		if (MulClosure()) {
			return true;
		}
		if (DivClosure()) {
			return true;
		}
		if (ClosureExp<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		if (ClosureExp<OPERATOR_TYPE_POWER_ROOT>()) {
			return true;
		}
		return false;
	}
	
	
	bool PolymorphismMulDiv::FlatAble(const ExpressionNodes::iterator child) const {
		return true;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismMulDiv::GetCommonAdpterMulDiv() const {
		return m_exp;
	}
	OPERATOR_TYPE_FLAG PolymorphismMulDiv::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_MUL;
	}
	OPERATOR_TYPE_FLAG PolymorphismMulDiv::Flag() const {
		return m_exp.Flag();
	}
	OPERATOR_TYPE_LEVEL PolymorphismMulDiv::Level() const {
		return OPERATOR_TYPE_LEVEL_MUL_DIV;
	}
	bool PolymorphismMulDiv::SymbolExtend() {
		auto symbols = m_exp.GetAll<SymbolWrapper>();
		for (auto& symbol : symbols) {
			if (std::get<SymbolWrapper>(*symbol).ExtendMulDiv(m_exp)) {
				return true;
			}
		}
		return false;
	}
	ExpressionNodes PolymorphismMulDiv::BuildPowerRootOriginNodes() const {
		return m_exp.m_nodes;
	}
	ExpressionNodes PolymorphismMulDiv::BuildPowerRootDriverNodes() const {
		auto nodes = m_exp.m_nodes;
		for (auto& node : nodes) {
			if (m_exp.IsPower()) {
				Polymorphism::Visit(node)->SetOperator(
					!Polymorphism::Visit(node)->IsDiv() ?
					OPERATOR_TYPE_FLAG_POWER : OPERATOR_TYPE_FLAG_ROOT);
			}
			else {
				Polymorphism::Visit(node)->SetOperator(
					!Polymorphism::Visit(node)->IsDiv() ?
					OPERATOR_TYPE_FLAG_ROOT : OPERATOR_TYPE_FLAG_POWER);
			}
		}
		return nodes;
	}
	ExpressionNodes PolymorphismMulDiv::BuildLogarithmOriginNodes() const {
		return m_exp.m_nodes;
	}
	ExpressionNodes PolymorphismMulDiv::BuildMulNodes() const {
		ExpressionNodes nodes;
		nodes.push_back(m_exp);
		return nodes;
	}

	bool PolymorphismMulDiv::ExpandExpression() const {
		if (m_exp.ExpandExpression<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		return false;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismMulDiv::ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		if (m_exp.Size() < 2) {
			return std::nullopt;
		}
		if (OPERATOR_TYPE_FLAG_DIV != exp.Flag()) {
			return ExpandMulExpression(exp, pos);
		}
		else {
			return ExpandDivExpression(exp, pos);
		}
	}
	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismMulDiv::Reduce() const{
		auto& numerator = std::get<expression::ClosureNumber>(m_exp.Front());
		auto& denominator = std::get<expression::ClosureNumber>(m_exp.Back());
		if (!denominator.IsDiv()) {
			return std::nullopt;
		}
		const std::optional<number::Fraction>& fraction = number::Fraction::CheckReduce(numerator.Value(), denominator.Value());
		if (!fraction.has_value()) {
			return std::nullopt;
		}
		Expression<OPERATOR_TYPE_ADD_SUB> reduction(Expression<OPERATOR_TYPE_MUL_DIV>::Absorb(fraction.value()), m_exp.Flag());
		return reduction;
	}
	bool PolymorphismMulDiv::Signed() {
		int signedCount = NodesSigned();

		if (1 == signedCount % 2) {
			m_exp.Opposite();
		}

		return signedCount > 0;
	}
	template<typename ChildOperatorType>
	bool PolymorphismMulDiv::ClosureExp() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<ClosureNumber>();
		if (closures.empty()) {
			return false;
		}

		std::vector<ExpressionNodes::iterator> exps = m_exp.GetAll<Expression<ChildOperatorType>>();
		if (exps.empty()) {
			return false;
		}

		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template Closures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	Expression<OPERATOR_TYPE_POWER_ROOT> PolymorphismMulDiv::GetCommonAdpter(const ExpressionNode* node) {
		if (const expression::SymbolWrapper* symbol = std::get_if<expression::SymbolWrapper>(node)) {
			return GetCommonAdpterPowerRoot(*symbol);
		}
		else if (const expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp = std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(node)) {
			return *exp;
		}
		return expression::Expression<OPERATOR_TYPE_POWER_ROOT>();
	}
	Expression<OPERATOR_TYPE_POWER_ROOT> PolymorphismMulDiv::GetCommonAdpterPowerRoot(const SymbolWrapper& symbol) {
		Expression<OPERATOR_TYPE_POWER_ROOT> exp(symbol, POWER, number::Integer(1));
		exp.SetOperator(symbol.Flag());
		return exp;
	}
	bool PolymorphismMulDiv::MulClosure() {
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
	bool PolymorphismMulDiv::DivClosure() {

		auto collect = Divisors();
		if (collect.has_value()) {
			return collect.value();
		}

		auto reduction = Reduction();
		if (reduction.has_value()) {
			return reduction.value();
		}
		
		return false;
	}
	std::optional<bool> PolymorphismMulDiv::Divisors() {
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
	std::optional<bool> PolymorphismMulDiv::Reduction() {
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
	bool PolymorphismMulDiv::ClosurePower(ClosureNumber& closure) {
		std::optional<ExpressionNodes::iterator> multiplier = m_exp.GetFirst<ClosureNumber>(
			[](const ClosureNumber& node) {return node.Value().IsPositive() && node.IsMul(); });
		if (!multiplier.has_value()) {
			return false;
		}

		closure = ClosureNumber(number::Fraction::Power(closure.Value(),
			std::get<ClosureNumber>(*multiplier.value()).Value()).Numerator());

		m_exp.RemoveNode(multiplier.value());

		if(m_exp.IsSingle() && Polymorphism::Visit(m_exp.Front())->IsDiv()){
			Polymorphism::Visit(m_exp.Front())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
			m_exp.SetOperator(OPERATOR_TYPE_FLAG_ROOT);
		}

		return true;
	}
	
	bool PolymorphismMulDiv::ClosureRoot(ClosureNumber& closure) {
		std::optional <ExpressionNodes::iterator> divisor = m_exp.GetLast<ClosureNumber>(
			[](const ClosureNumber& node) {return node.Value().IsPositive() && OPERATOR_TYPE_FLAG_DIV == node.Flag(); });
		if (!divisor.has_value()) {
			return false;
		}

		closure = ClosureNumber(number::Fraction::Power(closure.Value(),
			std::get<ClosureNumber>(*divisor.value()).Value()).Numerator());

		m_exp.RemoveNode(divisor.value());

		if (m_exp.IsSingle() && Polymorphism::Visit(m_exp.Front())->IsDiv()) {
			Polymorphism::Visit(m_exp.Front())->SetOperator(OPERATOR_TYPE_FLAG_MUL);
			m_exp.SetOperator(OPERATOR_TYPE_FLAG_POWER);
		}

		return true;
	}
	int PolymorphismMulDiv::NodesSigned() {
		int signedCount = 0;
		auto node = m_exp.begin();
		while (node != m_exp.end()) {
			signedCount += Polymorphism::Visit(*node)->MulDivSigned();
			node++;
		}
		return signedCount;
	}
	ExpressionNodes PolymorphismMulDiv::BuildCommonNodes(ExpressionNodes::const_iterator pos) const {
		ExpressionNodes nodes;

		for (ExpressionNodes::iterator itor = m_exp.begin(); itor != m_exp.end(); itor++) {
			if (pos != itor) {
				nodes.push_back(*itor);
			}
		}

		return nodes;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismMulDiv::ExpandMulExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		
		auto mulNodes = exp.BuildMulNodes();

		if (mulNodes.size() < 2) {
			return std::nullopt;
		}

		auto commonNodes = BuildCommonNodes(pos);

		if (commonNodes.empty()) {
			return std::nullopt;
		}

		expression::Expression<OPERATOR_TYPE_ADD_SUB> expand;

		for (auto mulNode : mulNodes) {

			expression::Expression<OPERATOR_TYPE_MUL_DIV> cross;

			cross.AppendNode(mulNode);

			for (auto commonNode : commonNodes) {
				cross.AppendNode(commonNode);
			}

			cross.SetOperator(OPERATOR_TYPE_FLAG_ADD);
			expand.AppendChild(cross);
		}

		return expand;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismMulDiv::ExpandDivExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		if (2 > GetDivisorCount()) {
			return std::nullopt;
		}
		expression::Expression<OPERATOR_TYPE_MUL_DIV> expand;

		expression::Expression<OPERATOR_TYPE_MUL_DIV> combine;
		combine.SetOperator(OPERATOR_TYPE_FLAG_DIV);

		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (auto& node : nodes) {
			if (Polymorphism::Visit(*node)->IsDiv()) {
				Polymorphism::Visit(*node)->SetOperator(OPERATOR_TYPE_FLAG_MUL);
				combine.AppendNode(*node);
			}
			else {
				expand.AppendNode(*node);
			}
		}
		expand.AppendChild(combine);
		return expand;
	}
	size_t PolymorphismMulDiv::GetDivisorCount() const {
		size_t count = 0;
		for (auto& node : m_exp) {
			if (Polymorphism::Visit(node)->IsDiv()) {
				count++;
			}
		}
		return count;
	}
	PolymorphismPowerRoot::PolymorphismPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) :
		m_exp(exp) {

	}
	bool PolymorphismPowerRoot::Special() {
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
	bool PolymorphismPowerRoot::CancelRoot(const ExpressionNode &one, const ExpressionNode& other) {
		return (Polymorphism::Visit(one)->IsPower() && Polymorphism::Visit(other)->IsRoot()) ||
			(Polymorphism::Visit(one)->IsRoot() && Polymorphism::Visit(other)->IsPower());
	}
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::CancelLogarithm(const ExpressionNode &base, const ExpressionNode &mixture) {
		if (const expression::Expression<OPERATOR_TYPE_LOGARITHM>* exp =
			std::get_if<expression::Expression<OPERATOR_TYPE_LOGARITHM>>(&mixture)) {
			std::vector<ExpressionNodes::const_iterator> nodes = exp->GetAll();
			
			bool isEqualBaseExponent = false;

			Expression<OPERATOR_TYPE_POWER_ROOT> newExponent;
			for (size_t index = 0; index < nodes.size(); ++index) {
				ExpressionNode node(*nodes.at(index));

				if (Polymorphism::Visit(node)->IsNone()) {
					newExponent.AppendNode(node);
				}
				else {
					if (isEqualBaseExponent) {
						Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_ROOT);
						newExponent.AppendNode(node);
					}
					else {
						if (!Polymorphism::Visit(node)->IsEqual(
							*Polymorphism::Visit(base), false, true)) {
							Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_ROOT);
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
	bool PolymorphismPowerRoot::ContainFront(const std::list<ExpressionNode> &nodes) {
		for (auto& node : nodes) {
			if (Polymorphism::Visit(node)->IsNone()) {
				return true;
			}
		}
		return false;
	}
	bool PolymorphismPowerRoot::Cancel() {
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();
		for (size_t i = 1; i < nodes.size(); ++i) {

			for (size_t j = i + 1; j < nodes.size(); ++j) {
				if (i != j &&
					Polymorphism::Visit(*nodes.at(i))->IsEqual(
						*Polymorphism::Visit(*nodes.at(j)), false, true)) {
					if (CancelRoot(*nodes.at(i), *nodes.at(j))) {
						m_exp.RemoveNode(nodes.at(i));
						m_exp.RemoveNode(nodes.at(j));
						return true;
					}
				}
			}

			if (Polymorphism::Visit(*nodes.at(i))->IsPower()) {
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
	std::vector<ExpressionNodes::iterator> PolymorphismPowerRoot::GetChildren()
	{
		return std::vector<ExpressionNodes::iterator>();
	}
	bool PolymorphismPowerRoot::CollectCommonChild(std::vector<ExpressionNodes::iterator> &exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::BuildCommon(const std::vector<ExpressionNodes::const_iterator> &leftChildren,
		const std::vector<ExpressionNodes::const_iterator> &rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode> &commons) {
		
		if (!PowerRootCommon()) {
			return std::nullopt;
		}

		Expression<OPERATOR_TYPE_MUL_DIV> childLeft = Polymorphism::NodesBuild(leftChildren, OPERATOR_TYPE_FLAG_ROOT);

		Expression<OPERATOR_TYPE_MUL_DIV> childRight = Polymorphism::NodesBuild(rightChildren, OPERATOR_TYPE_FLAG_ROOT);

		OPERATOR_TYPE_FLAG left = m_exp.Flag();

		if (ContainFront(commons)) {
			Expression<OPERATOR_TYPE_ADD_SUB> child = 
				(OPERATOR_TYPE_FLAG_DIV == left && OPERATOR_TYPE_FLAG_DIV != right) ||
				(OPERATOR_TYPE_FLAG_DIV != left && OPERATOR_TYPE_FLAG_DIV == right) ? 
				Expression<OPERATOR_TYPE_ADD_SUB>(childLeft, SUB, childRight):
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
			Expression<OPERATOR_TYPE_ADD_SUB> child =
				(OPERATOR_TYPE_FLAG_DIV == left && OPERATOR_TYPE_FLAG_DIV != right) ||
				(OPERATOR_TYPE_FLAG_DIV != left && OPERATOR_TYPE_FLAG_DIV == right) ?
				Expression<OPERATOR_TYPE_MUL_DIV>(childLeft, DIV, childRight) : 
				Expression<OPERATOR_TYPE_MUL_DIV>(childLeft, MUL, childRight);
			
			child.SetOperator(OPERATOR_TYPE_FLAG_MUL);

			Expression<OPERATOR_TYPE_POWER_ROOT> collect;
			collect.AppendChild(child.SetChild());
			for (auto &common : commons) {
				collect.AppendNode(common);
			}
			return collect;
		}


	}
	bool PolymorphismPowerRoot::Closure(ClosureNumber &closure) {
		return false;
	}
	bool PolymorphismPowerRoot::Closure() {
		if (PowerClosure()) {
			return true;
		}
		if (RootClosure()) {
			return true;
		}
		if (ClosureExp<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		if (ClosureExp<OPERATOR_TYPE_MUL_DIV>()) {
			return true;
		}
		return false;
	}
	
	bool PolymorphismPowerRoot::FlatAble(const ExpressionNodes::iterator child) const {
		return m_exp.begin() == child;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismPowerRoot::GetCommonAdpterMulDiv() const {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(ClosureNumber(1), OPERATOR_TYPE_MUL(), m_exp);
		exp.SetOperator(m_exp.Flag());
		return exp;
	}
	OPERATOR_TYPE_FLAG PolymorphismPowerRoot::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}
	OPERATOR_TYPE_FLAG PolymorphismPowerRoot::Flag() const {
		return m_exp.Flag();
	}
	OPERATOR_TYPE_LEVEL PolymorphismPowerRoot::Level() const {
		return OPERATOR_TYPE_LEVEL_POWER_ROOT;
	}
	bool PolymorphismPowerRoot::SymbolExtend() {
		auto symbols = m_exp.GetAll<SymbolWrapper>();
		for (auto& symbol : symbols) {
			if (std::get<SymbolWrapper>(*symbol).ExtendPowerRoot(m_exp)) {
				return true;
			}
		}
		return false;
	}
	ExpressionNodes PolymorphismPowerRoot::BuildPowerRootOriginNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismPowerRoot::BuildPowerRootDriverNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismPowerRoot::BuildLogarithmOriginNodes() const {
		return m_exp.m_nodes;
	}
	ExpressionNodes PolymorphismPowerRoot::BuildMulNodes() const {
		ExpressionNodes nodes;
		nodes.push_back(m_exp);
		return nodes;
	}
	
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismPowerRoot::ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		if (2 > m_exp.Size()) {
			return std::nullopt;
		}
		if (OPERATOR_TYPE_FLAG_NONE == exp.Flag()) {
			if (OPERATOR_TYPE_LEVEL_MUL_DIV == exp.Level()) {
				return ExpandMulDivOrigin(exp);
			}
			else if (OPERATOR_TYPE_LEVEL_ADD_SUB == exp.Level()) {
				return ExpandAddSubOrigin(exp);
			}
		}
		else {
			if (OPERATOR_TYPE_LEVEL_MUL_DIV == exp.Level()) {
				return ExpandMulDivDriver(exp, pos);
			}
			else if (OPERATOR_TYPE_LEVEL_ADD_SUB == exp.Level()) {
				return ExpandAddSubDriver(exp);
			}
		}
		return std::nullopt;
	}

	bool PolymorphismPowerRoot::ExpandExpression() const {
		if (m_exp.ExpandExpression<OPERATOR_TYPE_ADD_SUB>()) {
			return true;
		}
		if (m_exp.ExpandExpression<OPERATOR_TYPE_MUL_DIV>()) {
			return true;
		}
		return false;
	}

	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismPowerRoot::Reduce() const {
		auto& power = std::get<expression::ClosureNumber>(m_exp.Front());
		auto& exponent = std::get<expression::ClosureNumber>(m_exp.Back());
		if (!exponent.IsRoot()) {
			return std::nullopt;
		}
		const std::optional<number::Root>& root = number::Root::CheckReduce(power.Value(), exponent.Value());
		if (!root.has_value()) {
			return std::nullopt;
		}
		const Expression<OPERATOR_TYPE_MUL_DIV>& reductionCoefficient = Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(root.value().ReductionCoefficient());
		if (!root.value().IsFraction()) {
			const Expression<OPERATOR_TYPE_ADD_SUB>& reductionPower = Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(root.value().ReductionPower());
			const Expression<OPERATOR_TYPE_ADD_SUB>& reductionExponent = Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(root.value().ReductionExponent());
			Expression<OPERATOR_TYPE_MUL_DIV> reduction(Expression<OPERATOR_TYPE_MUL_DIV>(reductionCoefficient, MUL,
				Expression<OPERATOR_TYPE_POWER_ROOT>(reductionPower, ROOT, reductionExponent)), OPERATOR_TYPE_FLAG_MUL);
			return Expression<OPERATOR_TYPE_ADD_SUB>(expression::ClosureNumber(0), ADD, reduction);
		}
		else {
			Expression<OPERATOR_TYPE_MUL_DIV> reduction(Expression<OPERATOR_TYPE_MUL_DIV>(reductionCoefficient, MUL,
				expression::ClosureNumber(1)), OPERATOR_TYPE_FLAG_MUL);
			return Expression<OPERATOR_TYPE_ADD_SUB>(expression::ClosureNumber(0), ADD, reduction);
		}
	}
	bool PolymorphismPowerRoot::Signed() {
		return DriversSigned();
	}
	const Node *PolymorphismPowerRoot::Origin() const {
		return Polymorphism::Visit(m_exp.Front());
	}
	template<typename ChildOperatorType>
	bool PolymorphismPowerRoot::ClosureExp() {
		std::vector<ExpressionNodes::iterator> closures = m_exp.GetAll<ClosureNumber>();
		if (closures.empty()) {
			return false;
		}

		std::vector<ExpressionNodes::iterator> exps = m_exp.GetAll<Expression<ChildOperatorType>>();
		if (exps.empty()) {
			return false;
		}

		std::optional<typename Expression<ChildOperatorType>::ExpressionNodes::iterator> exp =
				Polymorphism::template Closures<ChildOperatorType>(closures, exps);
		return exp.has_value();
	}
	bool PolymorphismPowerRoot::IsOriginEqualPositiveOne(const ExpressionNode &node){
		return Polymorphism::Visit(node)->IsNone() && Polymorphism::Visit(node)->EqualPositiveOne();
	}
	bool PolymorphismPowerRoot::IsDriverEqualZero(const ExpressionNode &node){
		return !Polymorphism::Visit(node)->IsNone() && Polymorphism::Visit(node)->EqualZero();
	}
	bool PolymorphismPowerRoot::IsDriverEqualPositiveOne(const ExpressionNode& node) {
		return !Polymorphism::Visit(node)->IsNone() && Polymorphism::Visit(node)->EqualPositiveOne();
	}
	bool PolymorphismPowerRoot::PowerClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_POWER, [](const expression::ClosureNumber& base, const expression::ClosureNumber& exponent) {
			const number::Fraction& power = number::Fraction::Power(base.Value(), exponent.Value());
			return Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(power);
			});
	}
	bool PolymorphismPowerRoot::RootClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_ROOT,
			[](const expression::ClosureNumber& power, const expression::ClosureNumber& exponent) -> std::optional < Expression<OPERATOR_TYPE_MUL_DIV> > {
				const number::Root root(power.Value(), exponent.Value());
				if (root.IsFraction()) {
					const number::Fraction& coefficient = root.ReductionCoefficient();
					return Expression<OPERATOR_TYPE_POWER_ROOT>::Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
	}
	int PolymorphismPowerRoot::DriversSigned() {
		int signedCount = 0;
		auto node = m_exp.begin();
		while (++node != m_exp.end()) {
			if (Polymorphism::Visit(*node)->IsDisplaySigned()) {
				signedCount++;
			}
		}
		if (signedCount > 1) {
			int turnCount = 0;
			node = m_exp.begin();
			while (++node != m_exp.end() && turnCount < (0 == signedCount % 2 ? signedCount : signedCount - 1)) {
				if (Polymorphism::Visit(*node)->PowerRootSigned()) {
					turnCount++;
				}
			}
			return turnCount;
		}
		else {
			return 0;
		}
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::ExpandAddSubOrigin(const Polymorphism& exp) const {
		auto expNodes = exp.BuildPowerRootOriginNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}

		const auto exponentItor = m_exp.GetFirst<ClosureNumber>(
			[](const ClosureNumber& number) {return number.IsPower(); });
		if (!exponentItor.has_value()) {
			return std::nullopt;
		}

		const ClosureNumber& exponent = std::get<ClosureNumber>(*exponentItor.value());

		expression::Expression<OPERATOR_TYPE_ADD_SUB> base;
		for (auto node : expNodes) {
			base.AppendNode(node);
		}

		expression::Expression<OPERATOR_TYPE_MUL_DIV> mul;

		for (number::Natural times = 0; times < exponent.Value().Value(); ++times) {
			base.SetOperator(times > 0 ? OPERATOR_TYPE_FLAG_MUL: OPERATOR_TYPE_FLAG_NONE);
			mul.AppendChild(base);
		}

		expression::Expression<OPERATOR_TYPE_MUL_DIV> newBase = exponent.Value().IsPositive() ? mul : Expression<OPERATOR_TYPE_MUL_DIV>::Reciprocal(mul);
	
		expression::Expression<OPERATOR_TYPE_POWER_ROOT> expand;
		
		expand.AppendNode(newBase);
		
		for (auto driver = ++m_exp.begin(); driver != m_exp.end(); ++driver) {
			if (driver != exponentItor.value()) {
				expand.AppendNode(*driver);
			}
		}
		
		return expand;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::ExpandMulDivOrigin(const Polymorphism& exp) const {
		auto expNodes = exp.BuildPowerRootOriginNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}
		expression::Expression<OPERATOR_TYPE_MUL_DIV> expand;
		for (auto node : expNodes) {
			expression::Expression<OPERATOR_TYPE_POWER_ROOT> cross;

			OPERATOR_TYPE_FLAG flag = Polymorphism::Visit(node)->Flag();

			Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_NONE);
			cross.AppendNode(node);

			for (auto driver = ++m_exp.begin(); driver != m_exp.end(); ++driver) {
				cross.AppendNode(*driver);
			}

			cross.SetOperator(flag);
			expand.AppendChild(cross);
		}

		return expand;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::ExpandAddSubDriver(const Polymorphism& exp) const {
		
		auto expNodes = exp.BuildPowerRootDriverNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}

		expression::Expression<OPERATOR_TYPE_MUL_DIV> expand;

		for (auto node : expNodes) {
			expression::Expression<OPERATOR_TYPE_POWER_ROOT> cross;

			OPERATOR_TYPE_FLAG flag = Polymorphism::Visit(node)->Flag();

			cross.AppendNode(m_exp.Front());

			cross.AppendNode(node);
			Polymorphism::Visit(cross.Back())->SetOperator(OPERATOR_TYPE_FLAG_POWER);

			cross.SetOperator(flag == OPERATOR_TYPE_FLAG_ADD ? OPERATOR_TYPE_FLAG_MUL : OPERATOR_TYPE_FLAG_DIV);
			expand.AppendChild(cross);
		}

		return expand;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismPowerRoot::ExpandMulDivDriver(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		auto expNodes = exp.BuildPowerRootDriverNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}

		expression::Expression<OPERATOR_TYPE_POWER_ROOT> expand;

		expand.AppendNode(m_exp.Front());

		for (auto driver = ++m_exp.begin(); driver != m_exp.end(); ++driver) {
			if (driver != pos) {
				expand.AppendNode(*driver);
			}
		}

		for (auto node : expNodes) {
			expand.AppendNode(node);
		}

		return expand;
	}
	PolymorphismLogarithm::PolymorphismLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp) :
		m_exp(exp) {

	}
	bool PolymorphismLogarithm::Special() {
		return false;
	}
	
	bool PolymorphismLogarithm::Cancel() {
		std::vector<ExpressionNodes::iterator> nodes = m_exp.GetAll();

		for (size_t i = 1; i < nodes.size(); ++i) {
			if (OPERATOR_TYPE_FLAG_LOGARITHM == Polymorphism::Visit(*nodes.at(i))->Flag()) {
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
	std::vector<ExpressionNodes::iterator> PolymorphismLogarithm::GetChildren() {
		return std::vector<ExpressionNodes::iterator>();
	}
	bool PolymorphismLogarithm::CollectCommonChild(std::vector<ExpressionNodes::iterator>& exps, std::vector<ExpressionNodes::iterator>::iterator start) {
		return false;
	}
	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismLogarithm::BuildCommon(const std::vector<ExpressionNodes::const_iterator>& leftChildren,
		const std::vector<ExpressionNodes::const_iterator>& rightChildren, OPERATOR_TYPE_FLAG right, const std::list<ExpressionNode>& commons) {
		return std::nullopt;
	}
	bool PolymorphismLogarithm::Closure(ClosureNumber& closure) {
		return false;
	}
	bool PolymorphismLogarithm::Closure() {
		return LogarithmClosure();
	}

	bool PolymorphismLogarithm::FlatAble(const ExpressionNodes::iterator child) const {
		return m_exp.begin() == child;
	}
	Expression<OPERATOR_TYPE_MUL_DIV> PolymorphismLogarithm::GetCommonAdpterMulDiv() const {
		Expression<OPERATOR_TYPE_MUL_DIV> exp(ClosureNumber(1), OPERATOR_TYPE_MUL(), m_exp);
		exp.SetOperator(m_exp.Flag());
		return exp;
	}
	OPERATOR_TYPE_FLAG PolymorphismLogarithm::FrontDefaultFlag() const {
		return OPERATOR_TYPE_FLAG_NONE;
	}
	OPERATOR_TYPE_FLAG PolymorphismLogarithm::Flag() const {
		return m_exp.Flag();
	}
	OPERATOR_TYPE_LEVEL PolymorphismLogarithm::Level() const {
		return OPERATOR_TYPE_LEVEL_LOGARITHM;
	}
	bool PolymorphismLogarithm::SymbolExtend() {
		auto symbols = m_exp.GetAll<SymbolWrapper>();
		for (auto& symbol : symbols) {
			if (std::get<SymbolWrapper>(*symbol).ExtendLogarithm(m_exp)) {
				return true;
			}
		}
		return false;
	}
	ExpressionNodes PolymorphismLogarithm::BuildPowerRootOriginNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismLogarithm::BuildPowerRootDriverNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismLogarithm::BuildLogarithmOriginNodes() const {
		return ExpressionNodes();
	}
	ExpressionNodes PolymorphismLogarithm::BuildMulNodes() const {
		ExpressionNodes nodes;
		nodes.push_back(m_exp);
		return nodes;
	}

	bool PolymorphismLogarithm::ExpandExpression() const {
		if (m_exp.ExpandExpression<OPERATOR_TYPE_MUL_DIV>()) {
			return true;
		}
		if (m_exp.ExpandExpression<OPERATOR_TYPE_POWER_ROOT>()) {
			return true;
		}
		return false;
	}
	
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismLogarithm::ExpandExpression(const Polymorphism& exp, ExpressionNodes::const_iterator pos) const {
		if (2 > m_exp.Size()) {
			return std::nullopt;
		}
		if (OPERATOR_TYPE_FLAG_NONE == exp.Flag()) {
			if (OPERATOR_TYPE_LEVEL_MUL_DIV == exp.Level()) {
				return ExpandMulDivOrigin(exp);
			}
			else if (OPERATOR_TYPE_LEVEL_POWER_ROOT == exp.Level()) {
				return ExpandPowerRootOrigin(exp);
			}
		}
		else {
			return std::nullopt;
		}
		return std::nullopt;
	}

	std::optional<const Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismLogarithm::Reduce() const {
		auto& power = std::get<expression::ClosureNumber>(m_exp.Front());
		auto& base = std::get<expression::ClosureNumber>(m_exp.Back());
		if (!base.IsLogarithm()) {
			return std::nullopt;
		}
		const std::optional<number::Logarithm>& logarithm = number::Logarithm::CheckReduce(power.Value(), base.Value());
		if (!logarithm.has_value()) {
			return std::nullopt;
		}
		const Expression<OPERATOR_TYPE_MUL_DIV>& reductionCoefficient = Expression<OPERATOR_TYPE_LOGARITHM>::Absorb(logarithm.value().ReductionCoefficient());
		if (!logarithm.value().IsFraction()) {
			const Expression<OPERATOR_TYPE_MUL_DIV>& reductionPower = Expression<OPERATOR_TYPE_LOGARITHM>::Absorb(logarithm.value().ReductionPower());
			const Expression<OPERATOR_TYPE_MUL_DIV>& reductionBase = Expression<OPERATOR_TYPE_LOGARITHM>::Absorb(logarithm.value().ReductionBase());
			Expression<OPERATOR_TYPE_MUL_DIV> reduction(Expression<OPERATOR_TYPE_MUL_DIV>(reductionCoefficient, MUL,
				Expression<OPERATOR_TYPE_LOGARITHM>(reductionPower, LOGARITHM, reductionBase)), m_exp.Flag());
			return Expression<OPERATOR_TYPE_ADD_SUB>(expression::ClosureNumber(0), ADD, reduction);
		}
		else {
			Expression<OPERATOR_TYPE_MUL_DIV> reduction(Expression<OPERATOR_TYPE_MUL_DIV>(reductionCoefficient, MUL,
				expression::ClosureNumber(1)), m_exp.Flag());
			return Expression<OPERATOR_TYPE_ADD_SUB>(expression::ClosureNumber(0), ADD, reduction);
		}
	}
	bool PolymorphismLogarithm::LogarithmClosure() {
		return m_exp.ForeachClosure(OPERATOR_TYPE_FLAG_LOGARITHM,
			[](const expression::ClosureNumber& power, const expression::ClosureNumber& base) -> std::optional < Expression<OPERATOR_TYPE_MUL_DIV> > {
				const number::Logarithm logarithm(power.Value(), base.Value());
				if (logarithm.IsFraction()) {
					const number::Fraction& coefficient = logarithm.ReductionCoefficient();
					return Expression<OPERATOR_TYPE_LOGARITHM>::Absorb(coefficient);
				}
				else {
					return std::nullopt;
				}
			});
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_ADD_SUB>> PolymorphismLogarithm::ExpandMulDivOrigin(const Polymorphism& exp) const {
		if (exp.Level() != OPERATOR_TYPE_LEVEL_MUL_DIV) {
			return std::nullopt;
		}
		
		auto expNodes = exp.BuildLogarithmOriginNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}

		expression::Expression<OPERATOR_TYPE_ADD_SUB> expand;

		for (auto node : expNodes) {

			expression::Expression<OPERATOR_TYPE_LOGARITHM> element;
			element.SetOperator(Polymorphism::Visit(node)->IsDiv() ?
				OPERATOR_TYPE_FLAG_SUB : OPERATOR_TYPE_FLAG_ADD);

			Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_NONE);

			element.AppendNode(node);

			for (auto itor = ++m_exp.begin(); itor != m_exp.end(); ++ itor) {
				element.AppendNode(*itor);
			}

			expand.AppendChild(element);
		}

		return expand;
	}
	std::optional<typename expression::Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismLogarithm::ExpandPowerRootOrigin(const Polymorphism& exp) const {
		if (exp.Level() != OPERATOR_TYPE_LEVEL_POWER_ROOT) {
			return std::nullopt;
		}

		auto expNodes = exp.BuildLogarithmOriginNodes();
		if (expNodes.empty()) {
			return std::nullopt;
		}

		expression::Expression<OPERATOR_TYPE_MUL_DIV> expand;

		expression::Expression<OPERATOR_TYPE_LOGARITHM> element;
		element.AppendNode(expNodes.front());
		{
			for (auto itor = ++m_exp.begin(); itor != m_exp.end(); ++itor) {
				element.AppendNode(*itor);
			}
		}

		expand.AppendChild(element);

		{
			for (auto itor = ++expNodes.begin(); itor != expNodes.end(); ++itor) {
				Polymorphism::Visit(*itor)->SetOperator(
					Polymorphism::Visit(*itor)->IsRoot() ?
					OPERATOR_TYPE_FLAG_DIV : OPERATOR_TYPE_FLAG_MUL);

				expand.AppendNode(*itor);
			}
		}
		
		return expand;
	}

	std::optional<Expression<OPERATOR_TYPE_MUL_DIV>> PolymorphismLogarithm::CancelLogarithm(const ExpressionNode& base, const ExpressionNode& mixture) {
		if (const expression::Expression<OPERATOR_TYPE_POWER_ROOT>* exp =
			std::get_if<expression::Expression<OPERATOR_TYPE_POWER_ROOT>>(&mixture)) {
			std::vector<ExpressionNodes::const_iterator> nodes = exp->GetAll();

			Expression<OPERATOR_TYPE_MUL_DIV> newExponent;
			for (size_t index = 0; index < nodes.size(); ++index) {
				ExpressionNode node(*nodes.at(index));
				if (Polymorphism::Visit(*nodes.at(index))->IsNone())
				{
					if (!Polymorphism::Visit(*nodes.at(index))->IsEqual(
						*Polymorphism::Visit(base), false, true)) {
						return std::nullopt;
					}
				}
				else if (Polymorphism::Visit(*nodes.at(index))->IsPower())
				{
					Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_MUL);
					newExponent.AppendNode(node);
				}
				else
				{
					Polymorphism::Visit(node)->SetOperator(OPERATOR_TYPE_FLAG_DIV);
					newExponent.AppendNode(node);
				}
			}
			return newExponent;
		}
		return std::nullopt;
	}
}