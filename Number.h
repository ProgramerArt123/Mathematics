#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <string>
#include <functional>

class NDecimal;

class Number {
public:
	virtual const std::string GetString(uint8_t base = 10) const = 0;
	virtual void SetBase(uint8_t base = 10) = 0;
	virtual uint8_t GetBase() const = 0;
	virtual bool EqualZero() const = 0;
	virtual void SetPositive(bool isPositive) = 0;
	virtual bool IsPositive() const = 0;
	virtual NDecimal GetNDecimal() const = 0;
	
	const std::string GetStringBase(uint8_t base = 10) const;

	friend std::ostream& operator<<(std::ostream& out, const Number &number);

};


#endif