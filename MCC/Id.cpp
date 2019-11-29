#include "Id.h"

const string Id::typeName = "Id";

Id::Id(const char* lexeme)
	:Token(lexeme)
{
}

Id::Id(const string& lexeme)
	:Token(lexeme)
{
}

Id::Id(const Id& id)
	:Token(id.lexeme)
{
}

string Id::getType() const
{
	return this->typeName;
}
