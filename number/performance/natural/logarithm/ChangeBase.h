#ifndef __PERFORMANCE_NATURAL_LOGARITHM_CHANGE_BASE_H__
#define __PERFORMANCE_NATURAL_LOGARITHM_CHANGE_BASE_H__

#include "Interface.h"

namespace performance {
	namespace natural {
		namespace logarithm {
			class ChangeBase : public Interface {
			public:
				ChangeBase(const number::Natural &power, const number::Natural &base);
			private:
				std::pair<number::Natural, number::Natural> Correct(size_t exponent, const number::Natural &power, bool up = false);
			};
		}
	}
}
#endif