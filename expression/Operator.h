#ifndef __EXPRESSION_OPERATOR_H__
#define __EXPRESSION_OPERATOR_H__

#include <cstdint>

#include <iostream>

#include <memory>

#include "Output.h"

namespace expression {

	enum OPERATOR_TYPE_LEVEL {
		OPERATOR_TYPE_LEVEL_0,
		OPERATOR_TYPE_LEVEL_1,
		OPERATOR_TYPE_LEVEL_2,
		OPERATOR_TYPE_LEVEL_3
	};

	enum OPERATOR_TYPE_FLAG {
		OPERATOR_TYPE_FLAG_ADD,
		OPERATOR_TYPE_FLAG_SUB,
		OPERATOR_TYPE_FLAG_MUL,
		OPERATOR_TYPE_FLAG_DIV,
		OPERATOR_TYPE_FLAG_POWER,
		OPERATOR_TYPE_FLAG_ROOT,
		OPERATOR_TYPE_FLAG_LOGARITHM
	};

	class OPERATOR_TYPE : public Output {
	public:
		static std::unique_ptr<OPERATOR_TYPE> OperatorFactory(OPERATOR_TYPE_FLAG flag);

		virtual const OPERATOR_TYPE_LEVEL GetLevel() const = 0;

		virtual OPERATOR_TYPE_FLAG GetFlag() const = 0;

		virtual std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const = 0;
	};

	class OPERATOR_TYPE_0 : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_0;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_ADD;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;
	};

	class OPERATOR_TYPE_1 : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_1;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_MUL;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;
	};

	class OPERATOR_TYPE_2 : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_2;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_POWER;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;
	};

	class OPERATOR_TYPE_3 : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_3;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_LOGARITHM;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;
	};

	class OPERATOR_TYPE_ADD : public OPERATOR_TYPE_0 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_SUB : public OPERATOR_TYPE_0 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_MUL : public OPERATOR_TYPE_1 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_DIV : public OPERATOR_TYPE_1 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_POWER : public OPERATOR_TYPE_2 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_ROOT : public OPERATOR_TYPE_2 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_LOGARITHM : public OPERATOR_TYPE_3 {
	public:
		const std::string OutPutString() const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};
}

#define ADD OPERATOR_TYPE_ADD()
#define SUB OPERATOR_TYPE_SUB()
#define MUL OPERATOR_TYPE_MUL()
#define DIV OPERATOR_TYPE_DIV()
#define POWER OPERATOR_TYPE_POWER()
#define ROOT OPERATOR_TYPE_ROOT()
#define LOGARITHM OPERATOR_TYPE_LOGARITHM()


#endif