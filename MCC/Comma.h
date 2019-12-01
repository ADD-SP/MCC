#ifndef _COMMA_H_
#define _COMMA_H_ 0

#include "Token.h"
class Comma :
	public Token
{
public:
	static const string typeName;
	string lexeme;
	Comma(const char* lexeme, size_t line);
	Comma(const string& lexeme, size_t line);
	Comma(const Comma& comma);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<Comma>
	{
		size_t operator()(const Comma& comma) const
		{
			return comma.getHashCode();
		}
	};

	template<>
	struct hash<Comma*>
	{
		size_t operator()(const Comma* comma) const
		{
			return comma->getHashCode();
		}
	};

	template<>
	struct equal_to<Comma>
	{
		bool operator()(const Comma& x, const Comma& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Comma*>
	{
		bool operator()(const Comma* x, const Comma* y) const
		{
			return x->getType() == y->getType();
		}
	};
}

#endif // !_COMMA_H_

