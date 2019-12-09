#ifndef _DECIMAL_H_
#define _DECIMAL_H_ 0

/*
	这个Token表示浮点数
*/

#include "Number.h"
class Decimal :
	public Number
{
public:
	static const string typeName;
	Decimal(const char* lexeme, size_t line);
	Decimal(const string& lexeme, size_t line);
	Decimal(const Decimal& decimal);
	virtual string getType() const;
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

