#ifndef __NUMBER_REAL_H__
#define __NUMBER_REAL_H__

#include "Number.h"
namespace number {
	class Real : public Number {
	public:
		virtual bool EqualPositiveOne() const = 0;
		virtual bool EqualNegativeOne() const = 0;
		virtual void SetPositive(bool isPositive);
		virtual bool IsPositive() const;
		void Opposite() override;
	private:
		bool m_positive = true;
	};
}
#endif