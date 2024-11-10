#ifndef __PERFORMANCE_NATURAL_LOGARITHM_CHANGE_BASE_H__
#define __PERFORMANCE_NATURAL_LOGARITHM_CHANGE_BASE_H__

#include "Interface.h"

#include "number/performance/natural/Algorithm.h"

namespace performance {
	namespace natural {
		namespace logarithm {
			class ChangeBase : public Interface {
			public:
				ChangeBase(const number::Natural &power, const number::Natural &base);
			private:
				std::pair<number::Natural, number::Natural> Correct(Algorithm::CorrectExponent &exponent);
			};
		}
	}
}
#endif