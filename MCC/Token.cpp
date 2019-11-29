#include "Token.h"

const string Token::typeName = "Token";

Token::Token(const char* lexeme)
{
	this->lexeme = lexeme;
}

Token::Token(const string& lexeme)
{
	this->lexeme = lexeme;
}

Token::Token(const Token& token)
{
	this->lexeme = token.lexeme;
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
