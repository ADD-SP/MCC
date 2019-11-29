#ifndef _OPERATOR_H_
#define _OPERATOR_H_ 0
#include "Token.h"

typedef int OperatorType;

class Operator :
	public Token
{
public:
	static const string typeName;
	static const OperatorType plus, minus, star, div, equal, notEqual, no, assign, less, greate, lessEqual, greateEqual, logicalAnd, logicalOr, bitAnd, bitOr;
	OperatorType operatorType;
	Operator(OperatorType operatorType);
	Operator(const Operator& op);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool operator==(const Operator& op) const;
};

namespace std
{
	template<>
	struct hash<Operator>
	{
		size_t operator()(const Operator& op) const
		{
			return op.getHashCode();
		}
	};

	template<>
	struct hash<Operator*>
	{
		size_t operator()(const Operator* op) const
		{
			return op->getHashCode();
		}
	};

	template<>
	struct equal_to<Operator>
	{
		bool operator()(const Operator& x, const Operator& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Operator*>
	{
		bool operator()(const Operator* x, const Operator* y) const
		{
			return *x == *y;
		}
	};
}

#endif

