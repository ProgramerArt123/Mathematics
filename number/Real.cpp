#include "Real.h"

namespace number {
	void Real::SetPositive(bool isPositive)
	{
		m_positive = isPositive;
	}
	bool Real::IsPositive() const
	{
		return m_positive;
	}
	void Real::Opposite()
	{
		if (!EqualZero()) {
			SetPositive(!IsPositive());
		}
	}
}

