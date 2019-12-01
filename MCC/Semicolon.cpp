#include "Semicolon.h"

const string Semicolon::typeName = "Semicolon";


Semicolon::Semicolon(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Semicolon::Semicolon(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Semicolon::Semicolon(const Semicolon& semicolon)
	:Token(semicolon.lexeme, semicolon.line)
{
}

string Semicolon::getType() const
{
	return this->typeName;
}
