#include <sstream>

#include <iostream>

#include <cassert>

#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype) {
		*this = prototype;
	}
	ClosureNumber::ClosureNumber(const expression::ClosureNumber &prototype, OPERATOR_TYPE_FLAG flag) {
		*this = prototype;
		SetOperator(flag);
	}
	ClosureNumber::ClosureNumber(const number::Integer &value, OPERATOR_TYPE_FLAG flag) :
		Number(flag), m_value(value) {
	}
	const std::string ClosureNumber::GetString(uint8_t radix) const {
		if (!IsDisplaySigned()) {
			return m_value.Value().GetString(radix);
		}
		else {
			return "-" + m_value.Value().GetString(radix);
		}
	}
	bool ClosureNumber::IsEqual(const Node &other, bool ignoreSigned, bool ignoreOperator) const {
		if (!Node::IsEqual(other, ignoreSigned, ignoreOperator)) {
			return false;
		}
		const ClosureNumber &otherClosure = dynamic_cast<const ClosureNumber&>(other);
		return Value() == otherClosure.Value();
	}
	bool ClosureNumber::EqualZero() const {
		return Value().EqualZero();
	}
	bool ClosureNumber::EqualPositiveOne() const {
		return Value().EqualPositiveOne();
	}
	bool ClosureNumber::EqualNegativeOne() const {
		return Value().EqualNegativeOne();
	}
	bool ClosureNumber::IsDisplaySigned() const {
		int signedCount = (IsUnSigned() ? 0 : 1) + (Value().IsPositive() ? 0 : 1);
		return 1 == signedCount % 2;
	}
	bool ClosureNumber::AddSubSigned() {
		int signedCount = (IsUnSigned() ? 0 : 1) + (Value().IsPositive() ? 0 : 1);
		if (signedCount) {
			if (!Value().IsPositive()) {
				Opposite();
			}
			if (!IsUnSigned()) {
				Opposite();
			}
			if (1 == signedCount) {
				SetOperator(IsAdd() ? OPERATOR_TYPE_FLAG_SUB : OPERATOR_TYPE_FLAG_ADD);
			}
			return true;
		}
		return false;
	}
	bool ClosureNumber::MulDivSigned() {
		int signedCount = (IsUnSigned() ? 0 : 1) + (Value().IsPositive() ? 0 : 1);
		if (signedCount) {
			if (!Value().IsPositive()) {
				Opposite();
			}
			if (!IsUnSigned()) {
				Opposite();
			}
			return true;
		}
		return false;
	}
	void ClosureNumber::Opposite() {
		if (!m_value.IsPositive()) {
			m_value.SetPositive(true);
		}
		else {
			Node::Opposite();
		}
	}
	void ClosureNumber::SetOperator(OPERATOR_TYPE_FLAG flag) {
		Node::SetOperator(flag);
		m_operator->DomainVerification(flag, Value());
	}
	
	std::optional<bool> ClosureNumber::Compare(const ClosureNumber& other) const {
		if (Value() == other.Value()) {
			return std::nullopt;
		}
		return Value() < other.Value();
	}
	const number::Integer &ClosureNumber::Value() const {
		return m_value;
	}
	const ClosureNumber &ClosureNumber::operator=(const ClosureNumber &right) {
		m_value = right.m_value;
		expression::Number::operator=(right);
		return *this;
	}
	bool ClosureNumber::operator==(const ClosureNumber &other) const {
		return IsEqual(other, false);
	}
	ClosureNumber ClosureNumber::operator+(const ClosureNumber &addition) const {
		return m_value + addition.m_value;
	}
	ClosureNumber ClosureNumber::operator-(const ClosureNumber &subtrahend) const {
		return m_value - subtrahend.m_value;
	}
	ClosureNumber ClosureNumber::operator*(const ClosureNumber &multiplier) const {
		return m_value * multiplier.m_value;
	}
	ClosureNumber ClosureNumber::operator/(const ClosureNumber &divisor) const {
		return m_value / divisor.m_value;
	}
	ClosureNumber &ClosureNumber::operator+=(const ClosureNumber &addition) {
		m_value += addition.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator-=(const ClosureNumber &subtrahend) {
		m_value -= subtrahend.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator*=(const ClosureNumber &multiplier) {
		m_value *= multiplier.m_value;
		return *this;
	}
	ClosureNumber &ClosureNumber::operator/=(const ClosureNumber &divisor) {
		m_value /= divisor.m_value;
		return *this;
	}
}