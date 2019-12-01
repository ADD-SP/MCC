#include "Keyword.h"

const string Keyword::typeName = "Keyword";

Keyword::Keyword(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Keyword::Keyword(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Keyword::Keyword(const Keyword& keyword)
	:Token(keyword.lexeme, keyword.line)
{
}

string Keyword::getType() const
{
	return this->typeName;
}

