#include "Bracket.h"

const string Bracket::typeName = "Bracket";

Bracket::Bracket(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Bracket::Bracket(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Bracket::Bracket(const Bracket& bracket)
	:Token(bracket.lexeme, bracket.line)
{
}

string Bracket::getType() const
{
	return this->typeName;
}
