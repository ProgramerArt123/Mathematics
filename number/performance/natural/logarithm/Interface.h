#ifndef __PERFORMANCE_NATURAL_LOGARITHM_INTERFACE_H__
#define __PERFORMANCE_NATURAL_LOGARITHM_INTERFACE_H__

#include <utility>
#include "number/Natural.h"

namespace performance {
	namespace natural {
		namespace logarithm {
			class Interface{
			public:
				Interface(const number::Natural &power, const number::Natural &base)
					: m_power(power), m_base(base) {
				}
				std::pair<number::Natural, number::Natural> GetResult() const
				{
					return m_result;
				}
			protected:
				const number::Natural &m_power;
				const number::Natural &m_base;
				std::pair<number::Natural, number::Natural> m_result;
			};
		}
	}
}
#endif