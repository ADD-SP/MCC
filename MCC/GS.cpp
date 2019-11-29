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
	return this->typeName;
}
