#include "Type.h"

const string Type::typeName = "Type";

Type::Type(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Type::Type(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Type::Type(const Type& type)
	:Token(type.lexeme, type.line)
{
}

string Type::getType() const
{
	return this->typeName;
}
