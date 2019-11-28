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

size_t Type::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool Type::isEqual(const Type& type) const
{
	if (this->getType() == type.getType())
	{
		return this->lexeme == type.lexeme;
	}
	return false;
}

bool Type::operator==(const Type& type) const
{
	if (this->getType() == type.getType())
	{
		return this->lexeme == type.lexeme;
	}
	return false;
}

bool Type::operator!=(const Type type) const
{
	return !(*this == type);
}
