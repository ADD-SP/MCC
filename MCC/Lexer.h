#ifndef _LEXER_H_
#define _LEXER_H_ 0

/*
	这里是词法分析器
*/

#ifndef _WIN64
typedef int Index;
#else
typedef long long Index;
#endif

#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <stack>
#include <unordered_set>
#include "global.h"
#include "all_token.h"
#include "Environment.h"

using std::fstream;
using std::vector;
using std::string;
using std::ios;
using std::stack;
using std::unordered_set;
using std::out_of_range;

class Lexer
{
private:
	// 存储了全部的关键字
	static unordered_set<string> _keywords;
	// 存储了基本类型
	static unordered_set<string> _types;
	// 存储已经分析到的Token
	vector<Token*> _tokens;
	size_t _line = 1;
	Index _index;
	// 初始化关键字和类型集合
	void _iniKeyWordsAndTypes();
	// 处理源代码文件中的Token
	void _handle(const string& filename);
	bool _matchOther(fstream& fs);
	// 匹配算术和关系运算符
	bool _matchOperator(fstream& fs);
	// 匹配整数和浮点数
	bool _matchNumber(fstream& fs);
	// 匹配标识符和关键字
	bool _matchIdOrKeyWord(fstream& fs);
public:

	Lexer(const char* filename);
	Lexer(const string& filename);

	// 获取下一个Token
	Token* nextToken();
	// 前看一个Token，并不会造成指针的移动
	Token* peek(); 
	// 修改Token指针的位置
	void seek(Index offset);
};

#endif

