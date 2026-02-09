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

	class SymbolWrapper;

	class Symbol {
	public:
		Symbol(const expression::Symbol& prototype);
		Symbol(const std::string& name);

		virtual const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const;

		virtual bool IsEqual(const Symbol &other) const;

		std::optional<bool> Compare(const Symbol& other) const;

		virtual const std::string& Name() const;

		const Symbol& operator=(const Symbol& right);

		bool operator==(const Symbol& other) const;

		virtual bool ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB>& exp);
		virtual bool ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV>& exp);
		virtual bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT>& exp);
		virtual bool ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp);

		virtual std::shared_ptr<Symbol> GetClone() const;

	public:
		template<typename SubstitutionType>
		void SetSubstitution(const SubstitutionType& substitution) {
			m_substitution = std::make_shared<SubstitutionType>(substitution);
		}

		void SetSubstitution();

		std::shared_ptr<Node> GetSubstitution() const;

		bool IsLock() const;

		void SetLock(bool isLock);

	protected:

		std::shared_ptr<Node> m_substitution;

	private:
		std::string m_name;

		bool m_lock = false;
	};
	
	class SymbolWrapper : public Atom {
	public:
		SymbolWrapper(const SymbolWrapper &prototype);
		SymbolWrapper(const std::shared_ptr<Symbol> inner, OPERATOR_TYPE_FLAG flag);
		SymbolWrapper(const std::shared_ptr<Symbol> inner, bool isUnSigned = true, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Node& other, bool ignoreSigned = false, bool ignoreOperator = false) const override;

		SymbolWrapper operator-() const;

		std::optional<bool> Compare(const SymbolWrapper &other) const;

		const std::string &Name() const;

		const SymbolWrapper& operator=(const SymbolWrapper& right);

		bool operator==(const SymbolWrapper& other) const;

		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;

		size_t AddSubSigned() override;
		size_t MulDivSigned() override;

		bool ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB>& exp);
		bool ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV>& exp);
		bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT>& exp);
		bool ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp);

		template<typename SubstitutionType>
		void SetSubstitution(const SubstitutionType& substitution) {
			m_inner->SetSubstitution(substitution);
		}

		void ResetSubstitution();

		bool IsLock() const;

		void SetLock(bool isLock);

		std::shared_ptr<Node> GetSubstitution() const;

		Symbol& Inner() const;

	public:
		bool Substitution() const;

		static void SetSubstitutionCondition(std::function<bool(const SymbolWrapper&)> condition = std::function<bool(const SymbolWrapper&)>());

	private:
		std::shared_ptr<Symbol> m_inner;

	private:
		static std::function<bool(const SymbolWrapper &)> substitution_condition;
	};

	class LocalSwitch {
	public:
		LocalSwitch(const std::function<void()> on, const std::function<void()> off) :
			m_on(on), m_off(off) {
			m_off();
		}
		~LocalSwitch() {
			m_on();
		}
	private:
		const std::function<void()> m_on;
		const std::function<void()> m_off;
	};
}

#define LOCAL_SYMBOL_SUBSTITUTION_CONDITION(condition) expression::LocalSwitch local_substitution_condition(std::bind(&expression::SymbolWrapper::SetSubstitutionCondition, std::function<bool(const SymbolWrapper&)>()), std::bind(&expression::SymbolWrapper::SetSubstitutionCondition, condition));

#define LOCAL_SYMBOL_SUBSTITUTION(symbol, substitution) expression::LocalSwitch local_substitution_##symbol (std::bind(&expression::SymbolWrapper::ResetSubstitution, &symbol), std::bind(&expression::SymbolWrapper::SetSubstitution<decltype(substitution)>, &symbol, substitution));

#define LOCAL_SYMBOL_LOCK(symbol) expression::LocalSwitch local_lock_##symbol (std::bind(&expression::SymbolWrapper::SetLock, &symbol, false), std::bind(&expression::SymbolWrapper::SetLock, &symbol, true));

#endif