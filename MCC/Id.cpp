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

size_t Id::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool Id::isEqual(const Id& id) const
{
	if (id.getType() == this->getType())
	{
		return this->lexeme == id.lexeme;
	}
	return false;
}

bool Id::operator==(const Id& id) const
{
	if (id.getType() == this->getType())
	{
		return this->lexeme == id.lexeme;
	}
	return false;
}

bool Id::operator!=(const Id& id) const
{
	return !(*this == id);
}
