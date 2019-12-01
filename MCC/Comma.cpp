#include "Comma.h"

const string Comma::typeName = "Comma";

Comma::Comma(const char* lexeme, size_t line)
	:Token(lexeme, line)
{

}

Comma::Comma(const string& lexeme, size_t line)
	: Token(lexeme, line)
{

}

Comma::Comma(const Comma& comma)
	: Token(comma.lexeme, comma.line)
{

}

string Comma::getType() const
{
	return this->typeName;
}
