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
	return typeName;
}

size_t Number::getHashCode() const
{
	return std::hash<string>()(lexeme);
}

bool Number::operator==(const Number& number) const
{
	if (this->getType() == number.getType())
	{
		return this->lexeme == number.lexeme;
	}
	else
	{
		return false;
	}
}
