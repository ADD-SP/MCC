#ifndef _END_TOKEN_H_
#define _END_TOKEN_H_ 0

#include "Token.h"
class EndToken :
	public Token
{
public:
	static const string typeName;
	EndToken();
	EndToken(const EndToken& endToken);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<EndToken>
	{
		size_t operator()(const EndToken& endToken) const
		{
			return endToken.getHashCode();
		}
	};

	template<>
	struct hash<EndToken*>
	{
		size_t operator()(const EndToken* endToken) const
		{
			return endToken->getHashCode();
		}
	};

	template<>
	struct equal_to<EndToken>
	{
		bool operator()(const EndToken& x, const EndToken& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<EndToken*>
	{
		bool operator()(const EndToken* x, const EndToken* y) const
		{
			return *x == *y;
		}
	};
}

#endif // !_END_TOKEN_H_

