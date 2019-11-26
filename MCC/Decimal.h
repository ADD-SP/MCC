#ifndef _DECIMAL_H_
#define _DECIMAL_H_ 0

#include "Number.h"
class Decimal :
	public Number
{
public:
	static const string typeName;
	Decimal(const char* lexeme);
	Decimal(const string& lexeme);
	Decimal(const Decimal& decimal);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Decimal& decimal) const;
	virtual bool operator==(const Decimal& decimal) const;
};

namespace std
{
	template<>
	struct hash<Decimal>
	{
		size_t operator()(const Decimal& decimal) const
		{
			return decimal.getHashCode();
		}
	};

	template<>
	struct hash<Decimal*>
	{
		size_t operator()(const Decimal* decimal) const
		{
			return decimal->getHashCode();
		}
	};

	template<>
	struct equal_to<Decimal>
	{
		bool operator()(const Decimal& x, const Decimal& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Decimal*>
	{
		bool operator()(const Decimal* x, const Decimal* y) const
		{
			return *x == *y;
		}
	};
}

#endif

