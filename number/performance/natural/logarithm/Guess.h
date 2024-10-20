#ifndef __PERFORMANCE_NATURAL_LOGARITHM_GUESS_H__
#define __PERFORMANCE_NATURAL_LOGARITHM_GUESS_H__

#include "Interface.h"

namespace performance {
	namespace natural {
		namespace logarithm {
			class Guess : public Interface {
			public:
				Guess(const number::Natural &power, const number::Natural &base);
			private:
				size_t MaxOrders() const;
			};
		}
	}
}
#endif