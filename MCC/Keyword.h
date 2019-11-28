#ifndef _KEY_WORD_H_
#define _KEY_WORD_H_ 0

#include "Token.h"
class Keyword :
	public Token
{
public:
	static const string typeName;
	Keyword(const char* lexeme);
	Keyword(const string& lexeme);
	Keyword(const Keyword& keyword);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Keyword& keyword) const;
	virtual bool operator==(const Keyword& keyword) const;
};

namespace std
{
	template<>
	struct hash<Keyword>
	{
		size_t operator()(const Keyword& keyword) const
		{
			return keyword.getHashCode();
		}
	};

	template<>
	struct hash<Keyword*>
	{
		size_t operator()(const Keyword* keyword) const
		{
			return keyword->getHashCode();
		}
	};

	template<>
	struct equal_to<Keyword>
	{
		bool operator()(const Keyword& x, const Keyword& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Keyword*>
	{
		bool operator()(const Keyword* x, const Keyword* y) const
		{
			return *x == *y;
		}
	};
}



#endif // !_KEY_WORD_H_

