#include "Integer.h"
#include "Complex.h"

Complex::Complex(const Integer &real, const Integer &image) :
	m_real(new Integer(real)),m_image(image) {

}

const std::string Complex::GetString(uint8_t base) const {
	const std::string &realStr = m_real->GetString(base);
	const std::string &imageStr = m_image.GetString(base);
	if ("0" == realStr && "0i"==imageStr) {
		return "0";
	}
	else if ("0" == realStr) {
		return imageStr;
	}
	else if ("0i" == imageStr) {
		return realStr;
	}
	else {
		if ('-' != imageStr.front()) {
			return realStr + "+" + imageStr;
		}
		else {
			return realStr + imageStr;
		}
	}
}