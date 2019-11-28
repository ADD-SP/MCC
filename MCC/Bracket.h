#pragma once
#include "Token.h"
class Bracket :
	public Token
{
public:
	static const string typeName;
	Bracket(const char* lexeme);
	Bracket(const string& lexeme);
	Bracket(const Bracket& bracket);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Bracket& bracket) const;
	virtual bool operator==(const Bracket& bracket) const;
	virtual bool operator!=(const Bracket bracket) const;
};


namespace std{
	template<>
	struct hash<Bracket>
	{
		size_t operator()(const Bracket& bracket) const
		{
			return bracket.getHashCode();
		}
	};

	template<>
	struct hash<Bracket*>
	{
		size_t operator()(const Bracket* bracket) const
		{
			return bracket->getHashCode();
		}
	};

	template<>
	struct equal_to<Bracket>
	{
		bool operator()(const Bracket& x, const Bracket& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Bracket*>
	{
		bool operator()(const Bracket* x, const Bracket* y) const
		{
			return *x == *y;
		}
	};
}