
#include "Integer.h"
#include "Imaginary.h"
namespace number {
	Imaginary::Imaginary(const Integer &value) :
		m_value(value) {

	}

	Imaginary::Imaginary(const Fraction &value) :
		m_value(value) {

	}

	const std::string Imaginary::GetString(uint8_t radix) const {
		if (!EqualZero()) {
			return m_value.GetString(radix) + "i";
		}
		else {
			return "0";
		}
	}

	bool Imaginary::EqualZero() const {
		return m_value.EqualZero();
	}
	
	void Imaginary::Opposite() {
		m_value.Opposite();
	}
	const std::string Imaginary::GetDecimal(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round) const {
		return m_value.GetDecimal(radix, decimalLength, round) + "i";
	}
	const Fraction &Imaginary::Value() const {
		return m_value;
	}
	Imaginary Imaginary::operator-() const {
		Imaginary negative(*this);
		negative.Opposite();
		return negative;
	}
	bool Imaginary::operator==(const Imaginary &other) const {
		return Value() == other.Value();
	}
	Imaginary Imaginary::operator+(const Imaginary &addition) const {
		return m_value + addition.m_value;
	}
	Imaginary Imaginary::operator-(const Imaginary &subtrahend) const {
		return m_value - subtrahend.m_value;
	}
	Fraction Imaginary::operator*(const Imaginary &multiplier) const {
		return m_value * multiplier.m_value;
	}
	Fraction Imaginary::operator/(const Imaginary &divisor) const {
		return m_value / divisor.m_value;
	}


	Imaginary operator*(const Integer &number, const Imaginary &multiplier) {
		return number * multiplier.m_value;
	}
	Imaginary operator/(const Integer &number, const Imaginary &divisor) {
		return number / divisor.m_value;
	}


	Imaginary operator*(const Imaginary &number, const Integer &multiplier) {
		return multiplier * number;
	}
	Imaginary operator/(const Imaginary &number, const Integer &divisor) {
		return number.m_value / divisor;
	}


	Imaginary operator*(const Fraction &number, const Imaginary &multiplier) {
		return number * multiplier.m_value;
	}
	Imaginary operator/(const Fraction &number, const Imaginary &divisor) {
		return number / divisor.m_value;
	}


	Imaginary operator*(const Imaginary &number, const Fraction &multiplier) {
		return number.m_value * multiplier;
	}
	Imaginary operator/(const Imaginary &number, const Fraction &divisor) {
		return number.m_value / divisor;
	}
}