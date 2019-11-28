#ifndef _ID_H_
#define _ID_H_ 0


#include "Token.h"
class Id :
	public Token
{
public:
	static const string typeName;
	Id(const char* lexeme);
	Id(const string& lexeme);
	Id(const Id& id);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Id& id) const;
	virtual bool operator==(const Id& id) const;
	virtual bool operator!=(const Id& id) const;
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

