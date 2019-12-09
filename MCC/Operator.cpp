#include "Operator.h"

const string Operator::typeName = "Operator";

const int Operator::plus = 0;
const int Operator::minus = 1;
const int Operator::star = 2;
const int Operator::div = 3;
const int Operator::mod = 4;
const int Operator::equal = 5;
const int Operator::assign = 6;
const int Operator::less = 7;
const int Operator::greate = 8;
const int Operator::lessEqual = 9;
const int Operator::greateEqual = 10;
const int Operator::logicalAnd = 11;
const int Operator::logicalOr = 12;
const int Operator::bitAnd = 13;
const int Operator::bitOr = 14;
const int Operator::notEqual = 15;
const int Operator::no = 16;
const int Operator::inc = 17;
const int Operator::dec = 18;


void Operator::iniMap()
{
	if (_map.size() == 0)
	{
		_map.insert(std::pair<string, OperatorType>("+", plus));
		_map.insert(std::pair<string, OperatorType>("-", minus));
		_map.insert(std::pair<string, OperatorType>("*", star));
		_map.insert(std::pair<string, OperatorType>("/", div));
		_map.insert(std::pair<string, OperatorType>("%", mod));
		_map.insert(std::pair<string, OperatorType>("&", bitAnd));
		_map.insert(std::pair<string, OperatorType>("|", bitOr));
		_map.insert(std::pair<string, OperatorType>("=", assign));
		_map.insert(std::pair<string, OperatorType>("!", no));
		_map.insert(std::pair<string, OperatorType>(">", greate));
		_map.insert(std::pair<string, OperatorType>("<", less));
		_map.insert(std::pair<string, OperatorType>("=", assign));
		_map.insert(std::pair<string, OperatorType>("==", equal));
		_map.insert(std::pair<string, OperatorType>(">=", greateEqual));
		_map.insert(std::pair<string, OperatorType>("<=", less));
		_map.insert(std::pair<string, OperatorType>("!=", notEqual));
		_map.insert(std::pair<string, OperatorType>("&&", logicalAnd));
		_map.insert(std::pair<string, OperatorType>("||", logicalOr));
		_map.insert(std::pair<string, OperatorType>("++", inc));
		_map.insert(std::pair<string, OperatorType>("--", dec));
	}
}

Operator::Operator()
	:Token("", -2), operatorType(-1)
{
	iniMap();
}

Operator::Operator(bool isVaild)
	:Token("", -2), _isVaild(isVaild), operatorType(-1)
{
	iniMap();
}

Operator::Operator(OperatorType operatorType, size_t line)
	:Token("", line), operatorType(operatorType)
{
	iniMap();
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
	case mod:
		lexeme = "%";
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
	case inc:
		lexeme = "++";
		break;
	case dec:
		lexeme = "--";
		break;
	}
}

Operator::Operator(const string& op, size_t line)
	:Token(op, line)
{
	iniMap();
	auto itor = _map.find(op);
	if (itor == _map.end())
	{
		throw exception();
	}
	this->operatorType = itor->second;
}

Operator::Operator(const Operator& op)
	:Token(op.lexeme, op.line), operatorType(op.operatorType), _isVaild(op.isVaild())
{
}

string Operator::getType() const
{
	return this->isVaild() ? this->typeName : "";
}

bool Operator::isVaild() const
{
	return this->_isVaild;
}
