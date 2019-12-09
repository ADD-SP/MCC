#ifndef _OPERATOR_H_
#define _OPERATOR_H_ 0

/*
	这个Token包括一些算术运算符和关系运算符
*/

#include <unordered_map>
#include "Token.h"

using std::unordered_map;;

typedef int OperatorType;

class Operator :
	public Token
{
private:
	unordered_map<string, OperatorType> _map;
	bool _isVaild = true;
	void iniMap();
public:
	static const string typeName;
	static const OperatorType plus, minus, star, div, mod, equal, notEqual, no, assign, less, greate, lessEqual, greateEqual, logicalAnd, logicalOr, bitAnd, bitOr, inc, dec;
	OperatorType operatorType;
	Operator();
	Operator(bool isVaild);
	Operator(OperatorType operatorType, size_t line);
	Operator(const string& op, size_t line);
	Operator(const Operator& op);
	virtual string getType() const;
	bool isVaild() const;
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

