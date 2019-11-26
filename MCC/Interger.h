#ifndef _INTERGER_H_
#define _INTERGER_H_ 0
#include "Number.h"

class Interger :
	public Number
{
public:
	static const string typeName;
	Interger(const char* lexeme);
	Interger(const string& lexeme);
	Interger(const Interger& interger);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Interger& interger) const;
	virtual bool operator==(const Interger& interger) const;
};

namespace std
{
	template<>
	struct hash<Interger>
	{
		size_t operator()(const Interger& interger) const
		{
			return interger.getHashCode();
		}
	};

	template<>
	struct hash<Interger*>
	{
		size_t operator()(const Interger* interger) const
		{
			return interger->getHashCode();
		}
	};

	template<>
	struct equal_to<Interger>
	{
		bool operator()(const Interger& x, const Interger& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Interger*>
	{
		bool operator()(const Interger* x, const Interger* y) const
		{
			return *x == *y;
		}
	};
}

#endif

