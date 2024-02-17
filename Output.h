#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <functional>

class Output {
public:
	virtual const std::string OutPutString(size_t pos = 0) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Output &output);
};

#endif