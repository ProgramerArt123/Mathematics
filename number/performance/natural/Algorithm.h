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

			class CorrectExponent {
			public:
				CorrectExponent(size_t exponent, const number::Natural &base);
				CorrectExponent &Increase();
				CorrectExponent &Decrease();
				size_t Exponent() const;
				bool IsIncrease() const;
				const number::Natural Power() const;
				const number::Natural &PointPower() const;
			private:
				const size_t m_begin_exponent = 0;
				size_t m_exponent = 0;
				number::Natural m_power;
				const number::Natural &m_base;
				bool m_increase = false;
			};

		};
	}
}
#endif