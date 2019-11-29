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
	return this->typeName;
}
