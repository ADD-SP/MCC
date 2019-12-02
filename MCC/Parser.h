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
#include "Environment.h"
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
	 Environment envir;
	 Ast _ast;

	void _gen(string str);

	void _isDeclare(Id* id);

	void _pushValue(AstNode* left, AstNode* right,size_t start);

	void _reGenTAC(AstNode* root);

	AstNode* _parsePR();

	AstNode* _parseS();

	AstNode* _parseSIF();

	AstNode* _parseSLV(const string& id);

	AstNode* _parse_SLV();

	AstNode* _parseVD();

	AstNode* _parse_VD(Type* type, const string& id);

	AstNode* _parseFD();

	AstNode* _parse_FD();

	AstNode* _parsePL();

	AstNode* _parse_PL();

	AstNode* _parseLV();

	AstNode* _parse_LV(const string& id);

	AstNode* _parseRV();

	AstNode* _parse_RV(const string& id);

	AstNode* _parseBE();

	AstNode* _parse_BE(const string& number);

	AstNode* _parseBF();

	AstNode* _parseE();

	AstNode* _parse_E(const string& number);

	AstNode* _parseT();

	AstNode* _parse_T(const string& number);

	AstNode* _parseF();

	AstNode* _parse_F(const string& id);

	AstNode* _parseCL();

	AstNode* _parse_CL();



public:
	Parser(Lexer& lexer);

	void parse();
};

#endif // !_PARSER_H_



