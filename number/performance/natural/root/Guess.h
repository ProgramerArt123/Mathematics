#ifndef __PERFORMANCE_NATURAL_ROOT_GUESS_H__
#define __PERFORMANCE_NATURAL_ROOT_GUESS_H__

#include "Interface.h"

namespace performance {
	namespace natural {
		namespace root {
			class Guess : public Interface {
			public:
				Guess(const number::Natural &number, const number::Natural &exponent);
			private:
				std::pair<number::Natural, number::Natural> PowerInverseHalf(const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> power) const;
				std::pair<number::Natural, number::Natural> PowerInverse(const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> power) const;
		
			};
		}
	}
}
#endif