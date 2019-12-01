#include "Number.h"

const string Number::typeName = "Number";

Number::Number(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Number::Number(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Number::Number(const Number& number)
	:Token(number.lexeme, number.line)
{
}

string Number::getType() const
{
	return this->typeName;
}
