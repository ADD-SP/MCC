#ifndef _TOKEN_H_
#define _TOKEN_H_ 0

/*
	���࣬���������������ָ�����Token
*/

#include <string>
#include <stdexcept>

using std::string;
using std::exception;

class Token
{
public:
	// ������¼��ǰ������ƣ���Ҫ�����﷨������Parser
	static const string typeName;
	// ��¼��ǰToken������
	size_t line;
	string lexeme;
	Token(const char* lexeme, size_t line);
	Token(const string& lexeme, size_t line);
	Token(const Token& token);
	
	// ��ȡ��ǰ�������
	virtual string getType() const;

	// ��ȡ��ϣֵ
	virtual size_t getHashCode() const;

	// �ж��Ƿ����
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
