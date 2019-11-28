#ifndef _PARSER_H_
#define _PARSER_H_ 0

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

class Parser
{
private:
	 Lexer& _lexer;
	// Ast _ast;

	string _getVar();

	void _gen(string str);

	AstNode* _parseBE();

	AstNode* _parse_BE(string lexeme);

	AstNode* _parseBF();

	AstNode* _parseE();

	AstNode* _parseT();

	AstNode* _parse_E(string number);

	AstNode* _parse_T(string number);

	AstNode* _parseF();
public:
	Parser(Lexer& lexer);

	void parse();
};

#endif // !_PARSER_H_



