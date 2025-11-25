#include <sstream>
#include "Symbol.h"
namespace expression {
	Symbol::Symbol(const expression::Symbol &prototype) {
		*this = prototype;
	}
	Symbol::Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	Symbol::Symbol(const std::string &name, bool isUnSigned, OPERATOR_TYPE_FLAG flag):
		Atom(flag), m_name(name){
		SetUnSigned(isUnSigned);
	}
	const std::string Symbol::GetString(uint8_t radix) const {
		std::stringstream ss;
		if (IsDisplaySigned()) {
			ss << "-";
		}
		ss << Name();
		if (m_substitution) {
			ss << "{" << *m_substitution << "}";
		}
		return ss.str();
	}
	bool Symbol::IsEqual(const Node& other, bool ignoreSigned, bool ignoreOperator) const {
		if (!Node::IsEqual(other, ignoreSigned, ignoreOperator)) {
			return false;
		}
		const Symbol& otherSymbol = dynamic_cast<const Symbol&>(other);
		return Name() == otherSymbol.Name();
	}
	Symbol Symbol::operator-() const {
		Symbol negative(*this);
		negative.Opposite();
		return negative;
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
	const Symbol &Symbol::operator=(const Symbol &right) {
		Atom::operator=(right);
		m_name = right.m_name;
		m_unsigned = right.m_unsigned;
		m_substitution = right.m_substitution;
		return *this;
	}
	bool Symbol::operator==(const Symbol &other) const {
		return Atom::operator==(other) &&
			m_name == other.m_name &&
			m_unsigned == other.m_unsigned;
	}
	bool Symbol::EqualZero() const {
		return false;
	}
	bool Symbol::EqualPositiveOne() const {
		return false;
	}
	bool Symbol::EqualNegativeOne() const {
		return false;
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
	std::shared_ptr<Node> Symbol::GetSubstitution() const {
		return m_substitution;
	}
	SymbolManager &SymbolManager::GetInstance() {
		static SymbolManager instance;
		return instance;
	}

}