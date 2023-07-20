#include "Integer.h"
#include "Imaginary.h"
#include "Root.h"

Root::Root(const Integer &base, const Integer &exponent, bool positive): 
	m_positive(positive){
	m_base = std::shared_ptr<Integer>(new Integer(base));
	m_exponent = std::shared_ptr<Integer>(new Integer(exponent));
}

const std::string Root::GetString(uint8_t radix) const {
	return m_base->GetString(radix) + "@" + m_exponent->GetString(radix);
}
void Root::SetRadix(uint8_t radix) {
	m_base->SetRadix(radix);
	m_exponent->SetRadix(radix);
}
uint8_t Root::GetRadix() const {
	return m_base->GetRadix();
}
bool Root::EqualZero() const {
	return m_base->EqualZero();
}
void Root::SetPositive(bool isPositive) {
	m_positive = isPositive;
}
bool Root::IsPositive() const {
	return m_positive;
}

const std::string Root::GetDecimal(uint8_t radix, size_t decimalLength,
	std::function<bool(char)> round) const {
	std::string baseStr = m_base->GetNatural().GetString(radix);
	for (Natural index(1, radix); index <= m_exponent->m_value; ++index) {
		baseStr.append(decimalLength + 1, '0');
	}
	bool isExhaustive = true;
	const Natural &root = Natural(baseStr, radix).Root(m_exponent->m_value, isExhaustive);
	if (m_exponent->IsPositive()) {
		std::string rootStr = root.GetString(radix);
		if (rootStr.length() < decimalLength + 2) {
			rootStr.insert(0, decimalLength + 2 - rootStr.length(), '0');
		}
		std::string denominator = "1";
		denominator.append(decimalLength + 1, '0');
		const Fraction &fraction = Fraction(Integer(Natural(rootStr, radix), IsPositive()) /
			Fraction(Integer(Natural(denominator, radix))));
		if (!(!m_base->IsPositive() && 0 == *m_exponent % Integer(2))) {
			return fraction.GetDecimal(radix, decimalLength, round);
		}
		else {
			return Imaginary(fraction).GetDecimal(radix, decimalLength, round);
		}
	}
	else {
		std::string numerator = "1";
		numerator.insert(numerator.length(), decimalLength + 1, '0');
		const Fraction &fraction = Fraction(Integer(Natural(numerator, radix), IsPositive()), root);
		if (!(!m_base->IsPositive() && 0 == *m_exponent % Integer(2))) {
			return fraction.GetDecimal(radix, decimalLength, round);
		}
		else {
			return Imaginary(-fraction).GetDecimal(radix, decimalLength, round);
		}
	}
}