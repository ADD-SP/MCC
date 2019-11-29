#include "Interger.h"

const string Interger::typeName = "Interger";

Interger::Interger(const char* lexeme)
	:Number(lexeme)
{
}

Interger::Interger(const string& lexeme)
	:Number(lexeme)
{
}

Interger::Interger(const Interger& interger)
	:Number(interger.lexeme)
{
}

string Interger::getType() const
{
	return this->typeName;
}

