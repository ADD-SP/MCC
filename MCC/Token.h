#ifndef _TOKEN_H_
#define _TOKEN_H_ 0

#include <string>
#include <stdexcept>

using std::string;
using std::exception;

class Token
{
public:
	static const string typeName;
	string lexeme;
	Token(const char* lexeme);
	Token(const string& lexeme);
	Token(const Token& token);
	virtual string getType() const;
	virtual size_t getHashCode() const;
	virtual bool isEqual(const Token& token) const;
	virtual bool operator==(const Token& token) const;
	virtual bool operator!=(const Token& token) const;
};

namespace std
{
	template<>
	struct hash<Token>
	{
		size_t operator()(const Token& token) const
		{
			return token.getHashCode();
		}
	};

	template<>
	struct hash<Token*>
	{
		size_t operator()(const Token* token) const
		{
			return token->getHashCode();
		}
	};

	template<>
	struct equal_to<Token>
	{
		bool operator()(const Token& x, const Token& y) const
		{
			return x == y;
		}
	};

	template<>
	struct equal_to<Token*>
	{
		bool operator()(const Token* x, const Token* y) const
		{
			return x->getType() == y->getType();
		}
	};
}

#endif
