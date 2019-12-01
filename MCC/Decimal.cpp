#include "Decimal.h"

const string Decimal::typeName = "Decimal";

Decimal::Decimal(const char* lexeme, size_t line)
	:Number(lexeme, line)
{
}

Decimal::Decimal(const string& lexeme, size_t line)
	:Number(lexeme, line)
{
}

Decimal::Decimal(const Decimal& decimal)
	:Number(decimal.lexeme, decimal.line)
{
}

string Decimal::getType() const
{
	return this->typeName;
}
