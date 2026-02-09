#include <sstream>
#include "SymbolManager.h"
namespace expression {
	SymbolManager &SymbolManager::GetInstance() {
		static SymbolManager instance;
		return instance;
	}
	SymbolWrapper &SymbolManager::GetSymbol(const std::string& name) {
		return m_symbols.at(name);
	}
	SymbolManager::SymbolManager() {
		SetSymbol<expression::Imaginary>();
		SetSymbol<inf::Infinitesimal>();
		SetSymbol<inf::Infinity>();

		SetSymbol("a");
		SetSymbol("b");
		SetSymbol("c");

		SetSymbol("d");
		SetSymbol("e");
		SetSymbol("f");

		SetSymbol("x");
		SetSymbol("y");
		SetSymbol("z");
	}
}