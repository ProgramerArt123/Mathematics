#include <cassert>
#include "Algorithm.h"

namespace performance {
	namespace natural {

		std::pair<number::Natural, number::Natural> Algorithm::PowerInverseHalf(const number::Natural &power, const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> calculate) {
			char c = number::Natural::GetChar((number::Natural::GetValue(top) + number::Natural::GetValue(bottom)) / 2);
			singles[index] = c;
			const number::Natural value(std::list<char>(singles.cbegin(), singles.cend()));
			const number::Natural guessValue(calculate(factor, value));
			if (guessValue == power) {
				return std::make_pair<number::Natural, number::Natural>(number::Natural(value), number::Natural(0));
			}
			else if (guessValue > power) {
				if (number::Natural::GetValue(c) > number::Natural::GetValue(bottom)) {
					return PowerInverseHalf(power, factor, singles, index, number::Natural::GetChar(number::Natural::GetValue(c) - 1), bottom, calculate);
				}
				else {
					if (index) {
						return PowerInverseHalf(power, factor, singles, index - 1, number::Natural::GetChar(DEFAULT_RADIX - 1), '0', calculate);
					}
					else {
						return std::make_pair<number::Natural, number::Natural>(number::Natural(std::list<char>(singles.cbegin(), singles.cend())), number::Natural(0));
					}
				}
			}
			else {
				if (number::Natural::GetValue(c) < number::Natural::GetValue(top)) {
					if (number::Natural::GetValue(c) < number::Natural::GetValue(top) - 1) {
						return PowerInverseHalf(power, factor, singles, index, top, c, calculate);
					}
					else {
						return PowerInverse(power, factor, singles, index, top, c, calculate);
					}
				}
				else {
					if (index) {
						return PowerInverseHalf(power, factor, singles, index - 1, number::Natural::GetChar(DEFAULT_RADIX - 1), '0', calculate);
					}
					else {
						return std::make_pair<number::Natural, number::Natural>(number::Natural(value), number::Natural(power - guessValue));
					}
				}
			}
		}

		std::pair<number::Natural, number::Natural> Algorithm::PowerInverse(const number::Natural &power, const number::Natural &factor, std::vector<char> &singles, size_t index, char top, char bottom, std::function<number::Natural(const number::Natural&, const number::Natural&)> calculate) {
			char c = top;
			while (number::Natural::GetValue(c) >= number::Natural::GetValue(bottom)) {
				singles[index] = c;
				number::Natural value(std::list<char>(singles.cbegin(), singles.cend()));
				const number::Natural guessValue(calculate(factor, value));
				if (guessValue == power) {
					return std::make_pair<number::Natural, number::Natural>(number::Natural(value), number::Natural(0));
				}
				else if (guessValue < power) {
					if (index) {
						return PowerInverseHalf(power, factor, singles, index - 1, number::Natural::GetChar(DEFAULT_RADIX - 1), '0', calculate);
					}
					else {
						return std::make_pair<number::Natural, number::Natural>(number::Natural(value), number::Natural(power - guessValue));
					}
				}
				else {
					c = number::Natural::GetChar(number::Natural::GetValue(c) - 1);
				}
			}
			assert(0);
			return std::make_pair<number::Natural, number::Natural>(number::Natural(0), number::Natural(0));
		}

	}
}
