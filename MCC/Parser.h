#ifndef _PARSER_H_
#define _PARSER_H_ 0

/*
	语法分析器，语法规则和LL(1)分析表见项目根目录中的syntax文件夹
*/


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
#include "FourTuple.h"


using std::cout;
using std::cin;
using std::endl;
using std::stack;
using std::stoi;
using std::stod;

class Parser
{
private:
	// 一个词法分析器
	Lexer& _lexer;
	// 变量作用域
	Environment envir;
	// 抽象语法树
	Ast _ast;
	// 用来记录最内层循环的结束地址
	stack<string> _loopEndLabel;
	// 用来记录最内层循环的开始地址（包括循环条件判断）
	stack<string> _loopBoolLabel;
	// 字符串分割
	vector<string> _split(const string& str,char pattern);

	// 将三地址码转化为四元组
	void _gen(string str);

	// 按照指定的顺序遍历AstNode
	void _gen(AstNode* root);

	// 判断某个标识符是否声明
	void _isDeclare(Id* id);

	// 暂时弃用
	void _pushValue(AstNode* left, AstNode* right,size_t start);

	/*
		下列函数的命名格式为_parse + 文法符号
		其中下划线代表' ' '（撇），如_E代表E'
		文法符号的意义见项目根目录中的syntax文件夹
	*/
	AstNode* _parsePR();

	AstNode* _parseFE();

	AstNode* _parse_FE(const string& id);

	AstNode* _parseS(bool canGen = true);

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
	// 用来存储生成的四元组
	vector<FourTuple> fourTuples;

	Parser(Lexer& lexer);
};

#endif // !_PARSER_H_



