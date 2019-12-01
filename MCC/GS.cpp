#include "GS.h"

const string GS::typeName = "GS";

GS::GS(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

GS::GS(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

GS::GS(const GS& gs)
	:Token(gs.lexeme, gs.line)
{
}

string GS::getType() const
{
	return this->typeName;
}
