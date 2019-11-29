#include "Type.h"

const string Type::typeName = "Type";

Type::Type(const char* lexeme)
	:Token(lexeme)
{
}

Type::Type(const string& lexeme)
	:Token(lexeme)
{
}

Type::Type(const Type& id)
	:Token(id.lexeme)
{
}

string Type::getType() const
{
	return this->typeName;
}
