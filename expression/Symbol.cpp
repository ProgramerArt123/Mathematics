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
	bool Symbol::IsEqual(const Symbol& other) const {
		return *this == other;
	}
	std::optional<bool> Symbol::Compare(const Symbol &other) const {
		if (Name() == other.Name()) {
			if (m_unsigned == other.m_unsigned) {
				return std::nullopt;
			}
			return m_unsigned < other.m_unsigned;
		}
		return Name() < other.Name();
	}
	const std::string &Symbol::Name() const {
		return m_name;
	}
	const Symbol& Symbol::operator=(const Symbol& right) {
		m_name = right.m_name;
		m_unsigned = right.m_unsigned;
		m_substitution = right.m_substitution;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return m_name == other.m_name && m_unsigned == other.m_unsigned;
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
	size_t Symbol::AddSubSigned(SymbolWrapper& wrapper) {
		return 0;
	}
	size_t Symbol::MulDivSigned(SymbolWrapper& wrapper) {
		return 0;
	}
	void Symbol::Opposite(SymbolWrapper& wrapper) {
		m_unsigned = !m_unsigned;
		wrapper.SetUnSigned(IsUnSigned());
	}
	bool Symbol::IsUnSigned() const {
		return m_unsigned;
	}
	void Symbol::SetUnSigned(bool isUnSigned) {
		m_unsigned = isUnSigned;
	}
	void Symbol::SetSubstitution() {
		m_substitution.reset();
	}
	std::shared_ptr<Node> Symbol::GetSubstitution() const {
		return m_substitution;
	}
	bool SymbolWrapper::substitution_switch = true;
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
		m_inner->SetUnSigned(IsUnSigned());
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
		if (!Atom::IsEqual(other, ignoreSigned, ignoreOperator)) {
			return false;
		}
		const SymbolWrapper &otherWrapper = dynamic_cast<const SymbolWrapper&>(other);
		return m_inner->IsEqual(*otherWrapper.m_inner);
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
		m_inner->SetUnSigned(IsUnSigned());
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
	size_t SymbolWrapper::AddSubSigned() {
		return m_inner->AddSubSigned(*this);
	}
	size_t SymbolWrapper::MulDivSigned() {
		return m_inner->MulDivSigned(*this);
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
		if (!Substitution()) {
			return nullptr;
		}
		return m_inner->GetSubstitution();
	}
	Symbol &SymbolWrapper::Inner() const {
		return *m_inner;
	}
	bool SymbolWrapper::Substitution() {
		return substitution_switch;
	}
	void SymbolWrapper::SubstitutionOn() {
		substitution_switch = true;
	}
	void SymbolWrapper::SubstitutionOff() {
		substitution_switch = false;
	}
	SymbolManager &SymbolManager::GetInstance() {
		static SymbolManager instance;
		return instance;
	}
}