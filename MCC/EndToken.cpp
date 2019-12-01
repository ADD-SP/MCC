#include "EndToken.h"

const string EndToken::typeName = "EndToken";

EndToken::EndToken()
	:Token(typeName, 0)
{
}

EndToken::EndToken(const EndToken& endToken)
	:Token(endToken.lexeme, 0)
{
}

string EndToken::getType() const
{
	return this->typeName;
}
