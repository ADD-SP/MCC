#ifndef _TOKEN_H_
#define _TOKEN_H_ 0

/*
	基类，从这里派生出各种各样的Token
*/

#include <string>
#include <stdexcept>

using std::string;
using std::exception;

class Token
{
public:
	// 用来记录当前类的名称，主要用于语法分析器Parser
	static const string typeName;
	// 记录当前Token所在行
	size_t line;
	string lexeme;
	Token(const char* lexeme, size_t line);
	Token(const string& lexeme, size_t line);
	Token(const Token& token);
	
	// 获取当前类的类型
	virtual string getType() const;

	// 获取哈希值
	virtual size_t getHashCode() const;

	// 判断是否相等
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
