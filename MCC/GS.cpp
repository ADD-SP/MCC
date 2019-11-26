#include "GS.h"

const string GS::typeName = "GS";

GS::GS(const char* lexeme)
	:Token(lexeme)
{
}

GS::GS(const string& lexeme)
	:Token(lexeme)
{
}

string GS::getType() const
{
	return typeName;
}

size_t GS::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool GS::isEqual(const GS& gs) const
{
	if (this->getType() == gs.getType())
	{
		return this->lexeme == gs.lexeme;
	}
	else
	{
		return false;
	}
}

bool GS::operator==(const GS& gs) const
{
	if (this->getType() == gs.getType())
	{
		return this->lexeme == gs.lexeme;
	}
	else
	{
		return false;
	}
}
