#include "Expression.h"
namespace expression {
	const std::string Expression::OutPutString() const {
		std::string output;
		for (auto node : m_nodes) {
			output += node->OutPutString();
		}
		return output;
	}
}