#include "Comma.h"

const string Comma::typeName = "Comma";

Comma::Comma(const char* lexeme)
	:Token(lexeme)
{

}

Comma::Comma(const string& lexeme)
	: Token(lexeme)
{

}

Comma::Comma(const Comma& comma)
	: Token(comma.lexeme)
{

}

string Comma::getType() const
{
	return this->typeName;
}
