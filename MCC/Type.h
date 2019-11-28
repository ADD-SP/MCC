#ifndef _TYPE_H_
#define _TYPE_H_ 0

#include "Token.h"
class Type :
	public Token
{
public:
	static const string typeName;
	Type(const char* lexeme);
	Type(const string& lexeme);
	Type(const Type& id);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Type& type) const;
	virtual bool operator==(const Type& type) const;
	virtual bool operator!=(const Type type) const;
};

namespace std
{
	template<>
	struct hash<Type>
	{
		size_t operator()(const Type& type) const
		{
			return type.getHashCode();
		}
	};

	template<>
	struct hash<Type*>
	{
		size_t operator()(const Type* type) const
		{
			return type->getHashCode();
		}
	};

	template<>
	struct equal_to<Type>
	{
		bool operator()(const Type& x, const Type& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Type*>
	{
		bool operator()(const Type* x, const Type* y) const
		{
			return *x == *y;
		}
	};
}


#endif // !_TYPE_H_



