#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <functional>

class Output {
public:
	virtual const std::string OutPutString() const = 0;
	const Output &updatePosition(size_t pos) const;
	friend std::ostream& operator<<(std::ostream& out, const Output &output);
protected:
	mutable size_t m_position = 0;
};

#endif