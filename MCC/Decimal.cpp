#include "Decimal.h"

const string Decimal::typeName = "Decimal";

Decimal::Decimal(const char* lexeme)
	:Number(lexeme)
{
}

Decimal::Decimal(const string& lexeme)
	:Number(lexeme)
{
}

Decimal::Decimal(const Decimal& decimal)
	:Number(decimal.lexeme)
{
}

string Decimal::getType() const
{
	return typeName;
}

size_t Decimal::getHashCode() const
{
	return std::hash<string>()(lexeme);
}

bool Decimal::isEqual(const Decimal& decimal) const
{
	if (decimal.getType() == this->getType())
	{
		return this->lexeme == decimal.lexeme;
	}

	return false;
}

bool Decimal::operator==(const Decimal& decimal) const
{
	if (decimal.getType() == this->getType())
	{
		return this->lexeme == decimal.lexeme;
	}

	return false;
}
