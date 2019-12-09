#ifndef _NUMBER_H_
#define _NUMBER_H_ 0


/*
	这个Token表示数字，包括整数和浮点数。
*/

#include "Token.h"
#include <string>

using std::string;

class Number :
	public Token
{
public:
	static const string typeName;
	Number(const char* lexeme, size_t line);
	Number(const string& lexeme, size_t line);
	Number(const Number& number);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<Number>
	{
		size_t operator()(const Number& number) const
		{
			return number.getHashCode();
		}
	};

	template<>
	struct hash<Number*>
	{
		size_t operator()(const Number* number) const
		{
			return number->getHashCode();
		}
	};

	template<>
	struct equal_to<Number>
	{
		bool operator()(const Number& x, const Number& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Number*>
	{
		bool operator()(const Number* x, const Number* y) const
		{
			return *x == *y;
		}
	};
}

#endif

