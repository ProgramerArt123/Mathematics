#ifndef __PERFORMANCE_FRACTION_LOGARITHM_DISSECTION_H__
#define __PERFORMANCE_FRACTION_LOGARITHM_DISSECTION_H__

#include "Interface.h"

namespace performance {
	namespace fraction {
		namespace logarithm {
			class Dissection : public Interface {
			public:
				Dissection(const number::Fraction &power, const number::Fraction &base, size_t decimalLength);
			private:
				number::Fraction GetApproximation(const number::Integer &power, size_t decimalLength)const;
				number::Fraction GetApproximation(const number::Integer &power, const number::Integer &base, bool point, int approximation)const;
				number::Fraction GetApproximation(const number::Integer &power, const number::Integer &base)const;
			};
		}
	}
}
#endif