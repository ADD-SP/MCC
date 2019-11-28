#include "Bracket.h"

const string Bracket::typeName = "Bracket";

Bracket::Bracket(const char* lexeme)
	:Token(lexeme)
{
}

Bracket::Bracket(const string& lexeme)
	:Token(lexeme)
{
}

Bracket::Bracket(const Bracket& bracket)
	:Token(lexeme)
{
}

string Bracket::getType() const
{
	return this->typeName;
}

size_t Bracket::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool Bracket::isEqual(const Bracket& bracket) const
{
	if (this->getType() == bracket.getType())
	{
		return this->lexeme == bracket.lexeme;
	}
	return false;
}

bool Bracket::operator==(const Bracket& bracket) const
{
	if (this->getType() == bracket.getType())
	{
		return this->lexeme == bracket.lexeme;
	}
	return false;
}

bool Bracket::operator!=(const Bracket bracket) const
{
	return !(*this == bracket);
}
