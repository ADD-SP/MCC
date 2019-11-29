#ifndef _SEMICOLON_H_
#define _SEMICOLON_H_ 0

#include "Token.h"
class Semicolon :
	public Token
{
public:
	static const string typeName;
	Semicolon(const char* lexeme);
	Semicolon(const string& lexeme);
	Semicolon(const Semicolon& semicolon);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<Semicolon>
	{
		size_t operator()(const Semicolon& semicolon) const
		{
			return semicolon.getHashCode();
		}
	};

	template<>
	struct hash<Semicolon*>
	{
		size_t operator()(const Semicolon* semicolon) const
		{
			return semicolon->getHashCode();
		}
	};

	template<>
	struct equal_to<Semicolon>
	{
		bool operator()(const Semicolon& x, const Semicolon& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Semicolon*>
	{
		bool operator()(const Semicolon* x, const Semicolon* y) const
		{
			return *x == *y;
		}
	};
}


#endif // !_SEMICOLON_H_
