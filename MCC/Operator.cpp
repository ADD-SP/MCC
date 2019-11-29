#include "Operator.h"

const string Operator::typeName = "Operator";

const int Operator::plus = 0;
const int Operator::minus = 1;
const int Operator::star = 2;
const int Operator::div = 3;
const int Operator::equal = 4;
const int Operator::assign = 5;
const int Operator::less = 6;
const int Operator::greate = 7;
const int Operator::lessEqual = 8;
const int Operator::greateEqual = 9;
const int Operator::logicalAnd = 10;
const int Operator::logicalOr = 11;
const int Operator::bitAnd = 12;
const int Operator::bitOr = 13;
const int Operator::notEqual = 14;
const int Operator::no = 15;

Operator::Operator(OperatorType operatorType)
	:Token("")
{
	switch (operatorType)
	{
	case plus:
		lexeme = "+";
		break;
	case minus:
		lexeme = "-";
		break;
	case star:
		lexeme = "*";
		break;
	case div:
		lexeme = "/";
		break;
	case equal:
		lexeme = "==";
		break;
	case assign:
		lexeme = "=";
		break;
	case notEqual:
		lexeme = "!=";
		break;
	case no:
		lexeme = "!";
		break;
	case less:
		lexeme = "<";
		break;
	case greate:
		lexeme = ">";
		break;
	case lessEqual:
		lexeme = "<=";
		break;
	case greateEqual:
		lexeme = ">=";
		break;
	case logicalAnd:
		lexeme = "&&";
		break;
	case logicalOr:
		lexeme = "||";
		break;
	case bitAnd:
		lexeme = "&";
		break;
	case bitOr:
		lexeme = "|";
		break;

	}
	this->operatorType = operatorType;
}

Operator::Operator(const Operator& op)
	:Token(op.lexeme)
{
	this->operatorType = op.operatorType;
}

string Operator::getType() const
{
	return this->typeName;
}
