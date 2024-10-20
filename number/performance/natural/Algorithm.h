#ifndef __PERFORMANCE_NATURAL_ALGORITHM_H__
#define __PERFORMANCE_NATURAL_ALGORITHM_H__

#include <utility>

#include "number/Natural.h"

namespace performance {
	namespace natural {
		class Algorithm {
		public:
			static std::pair<number::Natural, number::Natural> PowerInverseHalf(const number::Natural &power, const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> calculate);
			static std::pair<number::Natural, number::Natural> PowerInverse(const number::Natural &power, const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> calculate);
		};
	}
}
#endif