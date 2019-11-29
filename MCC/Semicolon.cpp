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
