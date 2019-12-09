#ifndef _GS_H_
#define _GS_H_ 0

/*
	这个类暂时弃用
*/

#include "Token.h"

class GS :
	public Token
{
public:
	static const string typeName;
	GS(const char* lexeme, size_t line);
	GS(const string& lexeme, size_t line);
	GS(const GS& gs);
	virtual string getType() const;
};

namespace std
{
	template<>
	struct hash<GS>
	{
		size_t operator()(const GS& gs) const
		{
			return gs.getHashCode();
		}
	};

	template<>
	struct hash<GS*>
	{
		size_t operator()(const GS* gs) const
		{
			return gs->getHashCode();
		}
	};

	template<>
	struct equal_to<GS>
	{
		bool operator()(const GS& x, const GS& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<GS*>
	{
		bool operator()(const GS* x, const GS* y) const
		{
			return *x == *y;
		}
	};
}

#endif

