#ifndef __PERFORMANCE_FRACTION_ROOT_DISSECTION_H__
#define __PERFORMANCE_FRACTION_ROOT_DISSECTION_H__

#include "Interface.h"

namespace performance {
	namespace fraction {
		namespace root {
			class Dissection : public Interface {
			public:
				Dissection(const number::Fraction &power, const number::Fraction &exponent, size_t decimalLength);
			private:
				std::pair<number::Fraction, number::Fraction> GetApproximation(const number::Integer &base, size_t decimalLength)const;
			};
		}
	}
}
#endif