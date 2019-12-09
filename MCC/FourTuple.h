#ifndef _FOUR_TUPLE_H_
#define _FOUR_TUPLE_h_ 0

/*
	四元组
*/

#include <iostream>
#include <string>
#include "all_token.h"

using std::string;
using std::ostream;

class FourTuple
{
private:
	bool _isVaild = true;
	bool _isLabel = false;
	bool _isExpr = false;
	bool _isJmp = false;
public:
	// 空操作数，会被忽略
	static const string NOP;
	Operator op = Operator(false);
	string left = NOP;
	string right0 = NOP;
	string right1 = NOP;
	FourTuple();
	FourTuple(bool isVaild);

	// Label
	FourTuple(const char* left);
	FourTuple(const string& left);

	// Jmp
	FourTuple(const char* left, const char* right0);
	FourTuple(const string& left, const string& right0);

	FourTuple(const char* left, const char* right0, const char* right1);
	FourTuple(const string& left, const string& right0, const string& right1);

	// Expr
	FourTuple(const char* left, const Operator& op, const char* right0, const char* right1);
	FourTuple(const string& left, const Operator& op, const string& right0, const string& right1);

	FourTuple(const FourTuple& fourTuple);

	string toString();

	friend ostream& operator<<(ostream& os, const FourTuple& fourTuple);
	
	// 当前类是否有效
	bool isVaild() const;

	// 是否表示一个标签
	bool isLabel() const;

	// 是否表示一个表达式
	bool isExpr() const;

	// 是否表示一个跳转语句，包括条件跳转和无条件跳转
	bool isJmp() const;
};

#endif // !_FOUR_TUPLE_H_

