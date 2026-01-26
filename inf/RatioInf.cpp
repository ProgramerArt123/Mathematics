#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "RatioInf.h"

namespace inf {

	RatioInf::RatioInf(const std::string& name, const number::Fraction &degree) :
		Symbol(name) {
		m_degree = Transform(degree);
	}	
	size_t RatioInf::AddSubSigned(expression::SymbolWrapper& wrapper) {
		size_t signedCount = (IsUnSigned() ? 0 : 1) + (m_degree.IsPositive() ? 0 : 1);
		if (signedCount) {
			if (!m_degree.IsPositive()) {
				Opposite(wrapper);
			}
			if (!IsUnSigned()) {
				Opposite(wrapper);
			}
			if (1 == signedCount) {
				wrapper.SetOperator(wrapper.IsAdd() ? 
					expression::OPERATOR_TYPE_FLAG_SUB : 
					expression::OPERATOR_TYPE_FLAG_ADD);
			}
		}
		return signedCount;
	}
	size_t RatioInf::MulDivSigned(expression::SymbolWrapper& wrapper) {
		int signedCount = (IsUnSigned() ? 0 : 1) + (m_degree.IsPositive() ? 0 : 1);
		if (signedCount) {
			if (!m_degree.IsPositive()) {
				Opposite(wrapper);
			}
			if (!IsUnSigned()) {
				Opposite(wrapper);
			}
		}
		return signedCount;
	}
	void RatioInf::Opposite(expression::SymbolWrapper& wrapper) {
		if (!m_degree.IsPositive()) {
			m_degree.SetPositive(true);
		}
		else {
			Symbol::Opposite(wrapper);
		}
	}
	bool RatioInf::operator==(const RatioInf& other) const {
		return m_degree == other.m_degree;
	}

	bool RatioInf::IsPositive() const{
		return m_degree.IsPositive() == IsUnSigned() && !IsZero();
	}
	bool RatioInf::IsNegative() const{
		return m_degree.IsPositive() != IsUnSigned() && !IsZero();
	}
	bool RatioInf::IsZero() const{
		return m_degree.EqualZero();
	}
	bool RatioInf::IsUnit() const {
		return m_degree.EqualPositiveOne();
	}
	bool RatioInf::IsLeft() const {
		return IsNegative();
	}
	bool RatioInf::IsRight() const {
		return IsPositive();
	}
	const number::Fraction & RatioInf::Degree() const {
		return m_degree;
	}
	number::Fraction RatioInf::Transform(const number::Fraction &degree) {
		if (!degree.EqualZero() && degree.GetAbs() < number::Integer(1)) {
			return -degree.GetReciprocal();
		}
		else {
			return degree;
		}
	}
}