#include "FourTuple.h"

const string FourTuple::NOP = "__@@NOP@@NOP@@NOP@@__";

FourTuple::FourTuple()
{
}

FourTuple::FourTuple(bool isVaild)
	:_isVaild(isVaild)
{
}

FourTuple::FourTuple(const char* left)
	:left(left), _isLabel(true)
{
}

FourTuple::FourTuple(const string& left)
	: left(left), _isLabel(true)
{
}

FourTuple::FourTuple(const char* left, const char* right0)
	:left(left), right0(right0), _isJmp(true)
{
}

FourTuple::FourTuple(const string& left, const string& right0)
	: left(left), right0(right0), _isJmp(true)
{
}

FourTuple::FourTuple(const char* left, const char* right0, const char* right1)
	: left(left), right0(right0), right1(right1), _isJmp(true)
{
}

FourTuple::FourTuple(const string& left, const string& right0, const string& right1)
	: left(left), right0(right0), right1(right1), _isJmp(true)
{
}

FourTuple::FourTuple(const char* left, const Operator& op, const char* right0, const char* right1)
	: left(left), right0(right0), right1(right1), op(op), _isExpr(true)
{
}

FourTuple::FourTuple(const string& left, const Operator& op, const string& right0, const string& right1)
	: left(left), right0(right0), right1(right1), op(op), _isExpr(true)
{
}

FourTuple::FourTuple(const FourTuple& fourTuple)
	: left(fourTuple.left), right0(fourTuple.right0), right1(fourTuple.right1), op(fourTuple.op)
{
	_isJmp = fourTuple._isJmp;
	_isVaild = fourTuple._isVaild;
	_isExpr = fourTuple._isExpr;
	_isLabel = fourTuple._isLabel;
}

string FourTuple::toString()
{
	string ret;
	if (isVaild())
	{
		if (isExpr())
		{
			ret = left + " = " + right0;
			if (op.isVaild() && right1 != FourTuple::NOP)
			{
				ret +=  " " + op.lexeme + " " + right1;
			}
		}
		else if (isJmp())
		{
			if (left != FourTuple::NOP)
			{
				ret = left;
			}
			if (right0 != FourTuple::NOP)
			{
				ret +=  " " + right0;
			}
			if (right1 != FourTuple::NOP)
			{
				ret += " " + right1;
			}
		}
		else if (isLabel())
		{
			ret = left;
		}
		else
		{
			throw exception();
		}
	}
	else
	{
		throw exception();
	}

	return ret;
}

bool FourTuple::isVaild() const
{
	return this->_isVaild;
}

bool FourTuple::isLabel() const
{
	return _isLabel;
}

bool FourTuple::isExpr() const
{
	return _isExpr;
}

bool FourTuple::isJmp() const
{
	return _isJmp;
}

ostream& operator<<(ostream& os, const FourTuple& fourTuple)
{
	if (fourTuple.isVaild())
	{
		if (fourTuple.isExpr())
		{
			os << fourTuple.left << " = " << fourTuple.right0;
			if (fourTuple.op.isVaild() && fourTuple.right1 != FourTuple::NOP)
			{
				os << " " << fourTuple.op.lexeme + " " + fourTuple.right1;
			}
		}
		else if (fourTuple.isJmp())
		{
			if (fourTuple.left != FourTuple::NOP)
			{
				os << fourTuple.left;
			}
			if (fourTuple.right0 != FourTuple::NOP)
			{
				os << " " << fourTuple.right0;
			}
			if (fourTuple.right1 != FourTuple::NOP)
			{
				os << " " << fourTuple.right1;
			}
		}
		else if (fourTuple.isLabel())
		{
			os << fourTuple.left;
		}
		else
		{
			throw exception();
		}
	}
	else
	{
		throw exception();
	}

	return os;
}
