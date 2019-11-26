#include "EndToken.h"

const string EndToken::typeName = "EndToken";

EndToken::EndToken()
	:Token(typeName)
{
}

EndToken::EndToken(const EndToken& endToken)
	:Token(endToken.lexeme)
{
}

string EndToken::getType() const
{
	return typeName;
}

size_t EndToken::getHashCode() const
{
	return std::hash<string>()(this->lexeme);
}

bool EndToken::isEqual(const EndToken& endToken) const
{
	if (this->getType() == endToken.getType() && this->lexeme == endToken.lexeme)
	{
		return true;
	}
	return false;
}

bool EndToken::operator==(const EndToken& endToken) const
{
	return this->isEqual(endToken);
}
