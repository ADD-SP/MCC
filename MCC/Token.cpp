#include "Token.h"

const string Token::typeName = "Token";

Token::Token(const char* lexeme, size_t line)
	:lexeme(lexeme), line(line)
{
}

Token::Token(const string& lexeme, size_t line)
	:lexeme(lexeme), line(line)
{
}

Token::Token(const Token& token)
	:lexeme(token.lexeme), line(token.line)
{
}

string Token::getType() const
{
	return this->typeName;
}

size_t Token::getHashCode() const
{
	throw exception();
}

bool Token::isEqual(const Token& token) const
{
	if (this->getType() == token.getType())
	{
		return this->lexeme == token.lexeme;
	}
	else
	{
		return false;
	}
}

bool Token::operator==(const Token& token) const
{
	if (this->getType() == token.getType())
	{
		return this->lexeme == token.lexeme;
	}
	else
	{
		return false;
	}
}

bool Token::operator!=(const Token& token) const
{
	return !(*this == token);
}
