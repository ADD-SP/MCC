#ifndef _FOUR_TUPLE_H_
#define _FOUR_TUPLE_h_ 0

/*
	��Ԫ��
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
	// �ղ��������ᱻ����
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
	
	// ��ǰ���Ƿ���Ч
	bool isVaild() const;

	// �Ƿ��ʾһ����ǩ
	bool isLabel() const;

	// �Ƿ��ʾһ�����ʽ
	bool isExpr() const;

	// �Ƿ��ʾһ����ת��䣬����������ת����������ת
	bool isJmp() const;
};

#endif // !_FOUR_TUPLE_H_

