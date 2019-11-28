#include "Semicolon.h"

const string Semicolon::typeName = "Semicolon";


Semicolon::Semicolon(const char* lexeme)
	:Token(lexeme)
{
}

Semicolon::Semicolon(const string& lexeme)
	:Token(lexeme)
{
}

Semicolon::Semicolon(const Semicolon& semicolon)
	:Token(semicolon.lexeme)
{
}

string Semicolon::getType() const
{
	return this->typeName;
}

size_t Semicolon::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool Semicolon::isEqual(const Semicolon& semicolon) const
{
	if (this->getType() == semicolon.getType())
	{
		return this->lexeme == semicolon.lexeme;
	}
	return false;
}

bool Semicolon::operator==(const Semicolon& semicolon) const
{
	if (this->getType() == semicolon.getType())
	{
		return this->lexeme == semicolon.lexeme;
	}
	return false;
}

bool Semicolon::operator!=(const Semicolon semicolon) const
{
	return !(*this == semicolon);
}
