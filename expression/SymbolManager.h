#ifndef __EXPRESSION_SYMBOL_MANAGER_H__
#define __EXPRESSION_SYMBOL_MANAGER_H__

#include "Symbol.h"

#include "Imaginary.h"
#include "inf/Infinitesimal.h"
#include "inf/Infinity.h"

namespace expression {

	class SymbolManager {
	public:
		static SymbolManager& GetInstance();

		SymbolWrapper& GetSymbol(const std::string& name);

		template<typename SYMBOL = Symbol, typename ...Args>
		SymbolWrapper& SetSymbol(Args &&...args) {
			auto symbol = std::make_shared<SYMBOL>(std::forward<Args>(args)...);
			if (m_symbols.find(symbol->Name()) != m_symbols.cend()) {
				throw std::exception("Please Rename");
			}
			m_symbols.insert(std::make_pair(symbol->Name(), symbol));
			return GetSymbol(symbol->Name());
		}

	private:
		SymbolManager();
	private:
		std::map<std::string, SymbolWrapper> m_symbols;
	};

}

#define GET_SYMBOL(name) expression::SymbolManager::GetInstance().GetSymbol(name)

#define SYMBOL_INFINITY GET_SYMBOL(INFINITY_NAME)
#define SYMBOL_INFINITESIMAL GET_SYMBOL(INFINITESIMAL_NAME)
#define SYMBOL_IMAGINARY GET_SYMBOL(IMAGINARY_NAME)

#define SYMBOL_A GET_SYMBOL("a")
#define SYMBOL_B GET_SYMBOL("b")
#define SYMBOL_C GET_SYMBOL("c")

#define SYMBOL_D GET_SYMBOL("d")
#define SYMBOL_E GET_SYMBOL("e")
#define SYMBOL_F GET_SYMBOL("f")

#define SYMBOL_X GET_SYMBOL("x")
#define SYMBOL_Y GET_SYMBOL("y")
#define SYMBOL_Z GET_SYMBOL("z")

#endif