#include "Interger.h"

const string Interger::typeName = "Interger";

Interger::Interger(const char* lexeme, size_t line)
	:Number(lexeme, line)
{
}

Interger::Interger(const string& lexeme, size_t line)
	:Number(lexeme, line)
{
}

Interger::Interger(const Interger& interger)
	:Number(interger.lexeme, interger.line)
{
}

string Interger::getType() const
{
	return this->typeName;
}

