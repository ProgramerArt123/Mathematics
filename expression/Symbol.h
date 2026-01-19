#ifndef __EXPRESSION_SYMBOL_H__
#define __EXPRESSION_SYMBOL_H__

#include <optional>
#include <map>
#include <string>
#include <memory>
#include <variant>

#include "Atom.h"

namespace expression {

	template<typename OperatorType> class Expression;

	class Symbol : public Atom {
	public:
		Symbol(const expression::Symbol &prototype);
		Symbol(const expression::Symbol &prototype, OPERATOR_TYPE_FLAG flag);
		Symbol(const std::string &name, bool isUnSigned = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Node& other, bool ignoreSigned = false, bool ignoreOperator = false) const override;

		Symbol operator-() const;

		std::optional<bool> Compare(const Symbol &other) const;

		const std::string &Name() const;

		const Symbol &operator=(const Symbol &right);

		bool operator==(const Symbol &other) const;

		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;

		virtual bool ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB> &exp);
		virtual bool ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV> &exp);
		virtual bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT> &exp);
		virtual bool ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM> &exp);

	public:
		template<typename SubstitutionType>
		void SetSubstitution(const SubstitutionType &substitution) {
			m_substitution = std::make_shared<SubstitutionType>(substitution);
		}

		void SetSubstitution();

		std::shared_ptr<Node> GetSubstitution() const;

	protected:

		std::shared_ptr<Node> m_substitution;

	private:
		std::string m_name;

	};

	class SymbolManager {
	public:
		static SymbolManager &GetInstance();

		template<typename SYMBOL = Symbol>
		Symbol &GetSymbol(const std::string& name) {
			if (m_symbols.find(name) == m_symbols.cend()) {
				m_symbols.insert(std::make_pair(name, std::make_unique<SYMBOL>(name)));
			}
			return *m_symbols[name];
		}
	private:
		SymbolManager() {}
	private:
		std::map<std::string, std::unique_ptr<Symbol>> m_symbols;
	};
}

#define SYMBOL(name) SymbolManager::GetInstance().GetSymbol(name)

#define SYMBOL_A SYMBOL("a")
#define SYMBOL_B SYMBOL("b")
#define SYMBOL_C SYMBOL("c")

#define SYMBOL_X SYMBOL("x")
#define SYMBOL_Y SYMBOL("y")
#define SYMBOL_Z SYMBOL("z")

#endif