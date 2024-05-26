#ifndef __EXPRESSION_OPERATOR_H__
#define __EXPRESSION_OPERATOR_H__

#include <cstdint>

#include "Output.h"

namespace expression {

	enum OPERATOR_TYPE_FLAG {
		OPERATOR_TYPE_FLAG_NONE,
		OPERATOR_TYPE_FLAG_ADD,
		OPERATOR_TYPE_FLAG_SUB,
		OPERATOR_TYPE_FLAG_MUL,
		OPERATOR_TYPE_FLAG_DIV
	};

	class OPERATOR_TYPE : public Output {
	public:
		virtual OPERATOR_TYPE_FLAG GetFlag() const = 0;
	};

	class OPERATOR_TYPE_0 : public OPERATOR_TYPE {
	public:
		static const uint8_t GetLevel();
	};

	class OPERATOR_TYPE_1 : public OPERATOR_TYPE {
	public:
		static const uint8_t GetLevel();
	};

	class OPERATOR_TYPE_NONE : public OPERATOR_TYPE {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
	};

	class OPERATOR_TYPE_ADD : public OPERATOR_TYPE_0 {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
	};

	class OPERATOR_TYPE_SUB : public OPERATOR_TYPE_0 {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
	};

	class OPERATOR_TYPE_MUL : public OPERATOR_TYPE_1 {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
	};

	class OPERATOR_TYPE_DIV : public OPERATOR_TYPE_1 {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
	};

}

#endif