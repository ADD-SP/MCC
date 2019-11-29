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
