#ifndef __PERFORMANCE_NATURAL_ROOT_GUESS_H__
#define __PERFORMANCE_NATURAL_ROOT_GUESS_H__

#include "Interface.h"

namespace performance {
	namespace natural {
		namespace root {
			class Guess : public Interface {
			public:
				Guess(const number::Natural &power, const number::Natural &exponent);
			private:
				size_t MaxOrders() const;
			};
		}
	}
}
#endif