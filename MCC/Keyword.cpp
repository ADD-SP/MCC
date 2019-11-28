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
	return Keyword::typeName;
}

size_t Keyword::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool Keyword::isEqual(const Keyword& keyword) const
{
	if (this->getType() == keyword.getType())
	{
		return this->lexeme == keyword.lexeme;
	}
	else
	{
		return false;
	}
}

bool Keyword::operator==(const Keyword& keyword) const
{
	if (this->getType() == keyword.getType())
	{
		return this->lexeme == keyword.lexeme;
	}
	else
	{
		return false;
	}
}
