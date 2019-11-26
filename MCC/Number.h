#ifndef _NUMBER_H_
#define _NUMBER_H_ 0
#include "Token.h"

#include <string>

using std::string;

class Number :
	public Token
{
public:
	static const string typeName;
	Number(const char* lexeme);
	Number(const string& lexeme);
	Number(const Number& number);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool operator==(const Number& number) const;
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

