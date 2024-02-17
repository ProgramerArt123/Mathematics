#include <map>
#include "Integer.h"
#include "Expression.h"
namespace expression {
	
	const std::string Expression::OutPutString(size_t pos) const {
		std::string output;
		size_t index = 0;
		for (auto fraction : m_fractions) {
			output += fraction->OutPutString(index++);
		}
		return output;
	}

	Expression Expression::Collect(size_t count) const {
		Fraction fraction(number::Integer(0));
		std::list<std::shared_ptr<Fraction>> fractions;
		size_t index = 0;
		for (const auto &i : m_fractions) {
			if (index++ < count) {
				switch (i->m_type)
				{
				case OPERATOR_TYPE_ADD:
					fraction.m_value += i->m_value;
					break;
				case OPERATOR_TYPE_SUB:
					fraction.m_value -= i->m_value;
					break;
				default:
					fraction = *i;
					break;
				}
			}
			else {
				fractions.push_back(i);
			}
		}
		Expression collect(fraction);
		for (const auto &i : fractions) {
			collect.m_fractions.push_back(i);
		}
		return collect;
	}

	bool Expression::Collectable() const {
		return 1 < m_fractions.size();
	}

}