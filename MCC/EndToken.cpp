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
	return this->typeName;
}
