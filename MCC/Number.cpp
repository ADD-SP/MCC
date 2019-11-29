#include "Number.h"

const string Number::typeName = "Number";

Number::Number(const char* lexeme)
	:Token(lexeme)
{
}

Number::Number(const string& lexeme)
	:Token(lexeme)
{
}

Number::Number(const Number& number)
	:Token(number.lexeme)
{
}

string Number::getType() const
{
	return this->typeName;
}
