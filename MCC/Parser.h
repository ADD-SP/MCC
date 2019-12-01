#ifndef _PARSER_H_
#define _PARSER_H_ 0


#include <iostream>
#include <stack>
#include <typeinfo>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include "Lexer.h"
#include "all_token.h"
#include "global.h"
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
	 Ast _ast;

	void _gen(string str);

	AstNode* _parsePR();

	AstNode* _parseS();

	AstNode* _parseSIF();

	AstNode* _parseSLV();

	AstNode* _parse_SLV();

	AstNode* _parseVD();

	AstNode* _parse_VD();

	AstNode* _parseFD();

	AstNode* _parse_FD();

	AstNode* _parseLV();

	AstNode* _parse_LV();

	AstNode* _parseRV();

	AstNode* _parse_RV();

	AstNode* _parseBE();

	AstNode* _parse_BE();

	AstNode* _parseBF();

	AstNode* _parseE();

	AstNode* _parse_E();

	AstNode* _parseT();

	AstNode* _parse_T();

	AstNode* _parseF();

	AstNode* _parse_F();

	AstNode* _parseCL();

	AstNode* _parse_CL();



public:
	Parser(Lexer& lexer);

	void parse();
};

#endif // !_PARSER_H_



