#ifndef __EXPRESSION_OPERATOR_H__
#define __EXPRESSION_OPERATOR_H__

#include <cstdint>

#include <iostream>

#include <memory>

#include "Output.h"

#include "number/Integer.h"

namespace expression {

	enum OPERATOR_TYPE_LEVEL {
		OPERATOR_TYPE_LEVEL_NONE,
		OPERATOR_TYPE_LEVEL_ADD_SUB,
		OPERATOR_TYPE_LEVEL_MUL_DIV,
		OPERATOR_TYPE_LEVEL_POWER_ROOT,
		OPERATOR_TYPE_LEVEL_LOGARITHM
	};

	enum OPERATOR_TYPE_FLAG {
		OPERATOR_TYPE_FLAG_NONE,
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

		virtual void DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer &domain) const {}
	};

	class OPERATOR_TYPE_NONE : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_NONE;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_NONE;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;

		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE& other) const override;
	};

	class OPERATOR_TYPE_ADD_SUB : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_ADD_SUB;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_ADD;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;
	};

	class OPERATOR_TYPE_MUL_DIV : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_MUL_DIV;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_MUL;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;

		void DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const override;
	};

	class OPERATOR_TYPE_POWER_ROOT : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_POWER_ROOT;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_POWER;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;

		void DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const override;
	};

	class OPERATOR_TYPE_LOGARITHM : public OPERATOR_TYPE {
	public:
		const static OPERATOR_TYPE_LEVEL LEVEL = OPERATOR_TYPE_LEVEL_LOGARITHM;
		const static OPERATOR_TYPE_FLAG FLAG = OPERATOR_TYPE_FLAG_LOGARITHM;
		const OPERATOR_TYPE_LEVEL GetLevel() const override;

		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE& other) const override;

		void DomainVerification(OPERATOR_TYPE_FLAG flag, const number::Integer& domain) const override;

	};

	class OPERATOR_TYPE_ADD : public OPERATOR_TYPE_ADD_SUB {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_SUB : public OPERATOR_TYPE_ADD_SUB {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_MUL : public OPERATOR_TYPE_MUL_DIV {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_DIV : public OPERATOR_TYPE_MUL_DIV {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_POWER : public OPERATOR_TYPE_POWER_ROOT {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
		OPERATOR_TYPE_FLAG GetFlag() const override;
		std::unique_ptr<OPERATOR_TYPE> Superposition(const OPERATOR_TYPE &other) const override;
	};

	class OPERATOR_TYPE_ROOT : public OPERATOR_TYPE_POWER_ROOT {
	public:
		const std::string OutPutString(size_t pos = 0) const override;
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