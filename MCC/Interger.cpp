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
	return typeName;
}

size_t Interger::getHashCode() const
{
	return std::hash<string>()(lexeme);
}

bool Interger::isEqual(const Interger& interger) const
{
	if (this->getType() == interger.getType())
	{
		return this->lexeme == interger.lexeme;
	}
	else
	{
		return false;
	}
}

bool Interger::operator==(const Interger& interger) const
{
	if (this->getType() == interger.getType())
	{
		return this->lexeme == interger.lexeme;
	}
	else
	{
		return false;
	}
}
