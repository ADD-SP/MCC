#include "Keyword.h"

const string Keyword::typeName = "Keyword";

Keyword::Keyword(const char* lexeme)
	:Token(lexeme)
{
}

Keyword::Keyword(const string& lexeme)
	:Token(lexeme)
{
}

Keyword::Keyword(const Keyword& keyword)
	:Token(keyword.lexeme)
{
}

string Keyword::getType() const
{
	return this->typeName;
}

