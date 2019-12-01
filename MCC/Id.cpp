#include "Id.h"

const string Id::typeName = "Id";

Id::Id(const char* lexeme, size_t line)
	:Token(lexeme, line)
{
}

Id::Id(const string& lexeme, size_t line)
	:Token(lexeme, line)
{
}

Id::Id(const Id& id)
	:Token(id.lexeme, id.line)
{
}

string Id::getType() const
{
	return this->typeName;
}
