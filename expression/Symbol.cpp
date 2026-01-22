#include <sstream>
#include "Symbol.h"
namespace expression {
	Symbol::Symbol(const expression::Symbol &prototype) {
		*this = prototype;
	}
	Symbol::Symbol(const std::string &name):
		 m_name(name){
	}
	const std::string Symbol::GetString(uint8_t radix) const {
		return Name();
	}
	std::optional<bool> Symbol::Compare(const Symbol &other) const {
		if (Name() == other.Name()) {
			return std::nullopt;
		}
		return Name() < other.Name();
	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return m_name == other.m_name;
	}
	bool Symbol::ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB> &exp) {
		return false;
	}
	bool Symbol::ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV> &exp) {
		return false;
	}
	bool Symbol::ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp) {
		return false;
	}
	bool Symbol::ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp) {
		return false;
	}
	std::shared_ptr<Symbol> Symbol::GetClone() const {
		return std::make_shared<Symbol>(*this);
	}
	void Symbol::SetSubstitution() {
		m_substitution.reset();
	}
	std::shared_ptr<Node> Symbol::GetSubstitution() const {
		return m_substitution;
	}
	SymbolWrapper::SymbolWrapper(const SymbolWrapper &prototype){
		*this = prototype;
	}
	SymbolWrapper::SymbolWrapper(const std::shared_ptr<Symbol> inner, OPERATOR_TYPE_FLAG flag):
		m_inner(inner) {
		SetOperator(flag);
	}
	SymbolWrapper::SymbolWrapper(const std::shared_ptr<Symbol> inner, bool isUnSigned, OPERATOR_TYPE_FLAG flag):
		Atom(flag), m_inner(inner){
		SetUnSigned(isUnSigned);
	}
	const std::string SymbolWrapper::GetString(uint8_t radix) const {
		std::stringstream ss;
		if (IsDisplaySigned()) {
			ss << "-";
		}
		ss << m_inner->GetString();
		if (m_inner->GetSubstitution()) {
			ss << "{" << *m_inner->GetSubstitution() << "}";
		}
		return ss.str();
	}
	bool SymbolWrapper::IsEqual(const Node& other, bool ignoreSigned, bool ignoreOperator) const {
		if (!Node::IsEqual(other, ignoreSigned, ignoreOperator)) {
			return false;
		}
		const SymbolWrapper &otherWrapper = dynamic_cast<const SymbolWrapper&>(other);
		return *m_inner == *otherWrapper.m_inner;
	}
	SymbolWrapper SymbolWrapper::operator-() const {
		SymbolWrapper negative(*this);
		negative.Opposite();
		return negative;
	}
	std::optional<bool> SymbolWrapper::Compare(const SymbolWrapper& other) const {
		return m_inner->Compare(*other.m_inner);
	}
	const std::string &SymbolWrapper::Name() const {
		return m_inner->Name();
	}
	const SymbolWrapper &SymbolWrapper::operator=(const SymbolWrapper& right) {
		Atom::operator=(right);
		m_inner = right.m_inner->GetClone();
		return *this;
	}
	bool SymbolWrapper::operator==(const SymbolWrapper& other) const {
		return Atom::operator==(other) && *m_inner == *other.m_inner;
	}
	bool SymbolWrapper::EqualZero() const {
		return false;
	}
	bool SymbolWrapper::EqualPositiveOne() const {
		return false;
	}
	bool SymbolWrapper::EqualNegativeOne() const {
		return false;
	}
	bool SymbolWrapper::SymbolWrapper::ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB>& exp) {
		return m_inner->ExtendAddSub(exp);
	}
	bool SymbolWrapper::ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV>& exp) {
		return m_inner->ExtendMulDiv(exp);
	}
	bool SymbolWrapper::ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT>& exp) {
		return m_inner->ExtendPowerRoot(exp);
	}
	bool SymbolWrapper::ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp) {
		return m_inner->ExtendLogarithm(exp);
	}
	void SymbolWrapper::SetSubstitution() {
		m_inner->SetSubstitution();
	}
	std::shared_ptr<Node> SymbolWrapper::GetSubstitution() const {
		return m_inner->GetSubstitution();
	}
}