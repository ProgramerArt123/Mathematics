#include "expression/ClosureNumber.hpp"
#include "expression/Expression.hpp"

#include "RatioInf.h"

namespace inf {

	RatioInf::RatioInf(const std::string& name, const number::Fraction &degree) :
		Symbol(name) {
		m_degree = degree;
	}
	bool RatioInf::operator==(const RatioInf& other) const {
		return m_degree == other.m_degree;
	}
	bool RatioInf::IsPositive() const{
		return m_degree.IsPositive() && !IsZero();
	}
	bool RatioInf::IsNegative() const{
		return !m_degree.IsPositive() && !IsZero();
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
}