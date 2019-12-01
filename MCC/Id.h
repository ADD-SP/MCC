#ifndef _ID_H_
#define _ID_H_ 0


#include "Token.h"
class Id :
	public Token
{
public:
	static const string typeName;
	Id(const char* lexeme, size_t line);
	Id(const string& lexeme, size_t line);
	Id(const Id& id);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<Id>
	{
		size_t operator()(const Id& id) const
		{
			return id.getHashCode();
		}
	};

	template<>
	struct hash<Id*>
	{
		size_t operator()(const Id* id) const
		{
			return id->getHashCode();
		}
	};

	template<>
	struct equal_to<Id>
	{
		bool operator()(const Id& x, const Id& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Id*>
	{
		bool operator()(const Id* x, const Id* y) const
		{
			return *x == *y;
		}
	};
}
#endif // !_ID_H_

