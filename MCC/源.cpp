#include <iostream>
#include <stack>
#include <typeinfo>
#include <unordered_map>
#include <cstring>
#include "Lexer.h"
#include "GS.h"
#include "LLTable.h"
#include "Ast.h"
#include "macro.h"


using std::cout;
using std::cin;
using std::endl;
using std::stack;
using std::stoi;
using std::stod;

Lexer lexer("1.txt");

AstNode* parseE();

AstNode* parseT();

AstNode* parse_E(string number);

AstNode* parse_T(string number);

AstNode* parseF();

char* toCStr(string& str);

string getVar();

void gen(string str);

int main()
{

	Ast ast(parseE());

	// cout << GET_VALUE(ast.root, 0) << endl;

	return 0;
}

AstNode* parseE()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Number" || type == "Decimal" || type == "Interger")
	{
		left = parseT();
		right = parse_E(GET_VALUE(left, 0));
		p->push_right(left);
		p->push_right(right);

		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}

	}
	else
	{
		exit(-100);
	}
	return p;
}

AstNode* parseT()
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Number" || type == "Decimal" || type == "Interger")
	{
		left = parseF();
		right = parse_T(GET_VALUE(left, 0));
		p->push_right(left);
		p->push_right(right);
		
		if (right)
		{
			p->push_back(GET_VALUE(right, 0));
		}
		else
		{
			p->push_back(GET_VALUE(left, 0));
		}

	}
	else
	{
		exit(-100);
	}
	return p;
}

AstNode* parse_E(string number)
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Operator")
	{
		if (token->lexeme == "+" || token->lexeme == "-")
		{
			var = getVar();
			token = lexer.nextToken();
			left = parseT();

			gen(var + "=" + number + token->lexeme + GET_VALUE(left, 0));

			right = parse_E(var);
			p->push_right(left);
			p->push_right(right);

			if (right)
			{
				p->push_back(GET_VALUE(right, 0));
			}
			else
			{
				p->push_back(var);
			}

			return p;
		}
	}
	else if (type != "EndToken")
	{
		exit(-100);
	}

	return nullptr;
}

AstNode* parse_T(string number)
{
	AstNode* p = new AstNode();
	AstNode* left = nullptr;
	AstNode* right = nullptr;
	string value;
	string var;
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Operator")
	{
		if (token->lexeme == "*" || token->lexeme == "/")
		{
			var = getVar();
			token = lexer.nextToken();
			left = parseF();

			gen(var + "=" + number + token->lexeme + GET_VALUE(left, 0));

			right = parse_T(var);
			p->push_right(left);
			p->push_right(right);

			if (right)
			{
				p->push_back(GET_VALUE(right, 0));
			}
			else
			{
				p->push_back(var);
			}

			return p;
		}
	}
	else if (type != "EndToken")
	{
		exit(-100);
	}
	return nullptr;
}

AstNode* parseF()
{
	AstNode* p = new AstNode();
	string var;
	Token* token = lexer.peek();
	string type = token->getType();
	if (type == "Interger" || type == "Decimal")
	{
		var = getVar();
		token = lexer.nextToken();
		p->push_back(var);
		p->push_back(token->lexeme);
		gen(var + "=" + GET_VALUE(p, 1));
	}
	else
	{
		exit(-100);
	}
	return p;
}

char* toCStr(string& str)
{
	char* p = new char[str.length() + 1];
	strcpy_s(p, str.length() + 1, str.c_str());
	return p;
}

string getVar()
{
	static char a = 'a';
	string ret;
	ret.push_back(a++);
	return ret;
}

void gen(string str)
{
	cout << str << endl;
}
