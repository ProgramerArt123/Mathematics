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

		bool operator==(const Symbol& other) const;

		virtual bool ExtendAddSub(Expression<OPERATOR_TYPE_ADD_SUB>& exp);
		virtual bool ExtendMulDiv(Expression<OPERATOR_TYPE_MUL_DIV>& exp);
		virtual bool ExtendPowerRoot(Expression<OPERATOR_TYPE_POWER_ROOT>& exp);
		virtual bool ExtendLogarithm(Expression<OPERATOR_TYPE_LOGARITHM>& exp);

		virtual std::shared_ptr<Symbol> GetClone() const;

		virtual size_t AddSubSigned(SymbolWrapper &wrapper);
		virtual size_t MulDivSigned(SymbolWrapper& wrapper);

		virtual void Opposite(SymbolWrapper& wrapper);

		bool IsUnSigned() const;

		void SetUnSigned(bool isUnSigned);

	public:
		template<typename SubstitutionType>
		void SetSubstitution(const SubstitutionType& substitution) {
			m_substitution = std::make_shared<SubstitutionType>(substitution);
		}

		void SetSubstitution();

		std::shared_ptr<Node> GetSubstitution() const;

	protected:

		std::shared_ptr<Node> m_substitution;

	private:
		std::string m_name;

		bool m_unsigned = true;
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

		void SetSubstitution();

		std::shared_ptr<Node> GetSubstitution() const;

		Symbol& Inner() const;

	public:
		static bool Substitution();

		static void SubstitutionOn();

		static void SubstitutionOff();

	private:
		std::shared_ptr<Symbol> m_inner;

	private:
		static bool substitution_switch;
	};

}

#define SYMBOL_A expression::SymbolWrapper(std::make_shared<expression::Symbol>("a"))
#define SYMBOL_B expression::SymbolWrapper(std::make_shared<expression::Symbol>("b"))
#define SYMBOL_C expression::SymbolWrapper(std::make_shared<expression::Symbol>("c"))

#define SYMBOL_X expression::SymbolWrapper(std::make_shared<expression::Symbol>("x"))
#define SYMBOL_Y expression::SymbolWrapper(std::make_shared<expression::Symbol>("y"))
#define SYMBOL_Z expression::SymbolWrapper(std::make_shared<expression::Symbol>("z"))

#endif