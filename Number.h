#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <string>

class Number {
public:
	virtual const std::string GetString(uint8_t base = 10) const = 0;

	friend std::ostream& operator<<(std::ostream& out, const Number &number);
};


#endif