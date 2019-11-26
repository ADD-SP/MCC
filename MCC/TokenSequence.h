#ifndef _TOKEN_SEQUENCE_H_
#define _TOKEN_SEQUENCE_H_ 0

#include "Token.h"
#include <vector>
#include <cstdarg>

using std::va_list;
using std::vector;

class TokenSequence
{
private:
	vector<Token*> _tokens;
public:
	TokenSequence();
	TokenSequence(size_t num, ...);
	TokenSequence(const TokenSequence& tokenSequence);
	void push_back(size_t num, ...);
	void clear();
	size_t size() const;
	size_t getHashCode() const;
	bool operator==(const TokenSequence& tokenSequence) const;
	Token*& operator[](int index);
	Token* operator[](int index) const;
};

namespace std
{
	template<>
	struct hash<TokenSequence>
	{
		size_t operator()(const TokenSequence& tokenSequence) const
		{
			return tokenSequence.getHashCode();
		}
	};

	template<>
	struct hash<TokenSequence*>
	{
		size_t operator()(const TokenSequence* tokenSequence) const
		{
			return tokenSequence->getHashCode();
		}
	};

	template<>
	struct equal_to<TokenSequence>
	{
		bool operator()(const TokenSequence& x, const TokenSequence& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<TokenSequence*>
	{
		bool operator()(const TokenSequence* x, const TokenSequence* y) const
		{
			return *x == *y;
		}
	};
}


#endif // !_TOKEN_SEQUENCE_H_



