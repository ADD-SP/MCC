#ifndef _LEXER_H_
#define _LEXER_H_ 0

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
	static unordered_set<string> _keywords;
	static unordered_set<string> _types;
	vector<Token*> _tokens;
	size_t _line = 1;
	Index _index;
	void _iniKeyWordsAndTypes();
	void _handle(const string& filename);
	bool _matchOther(fstream& fs);
	bool _matchOperator(fstream& fs);
	bool _matchNumber(fstream& fs);
	bool _matchIdOrKeyWord(fstream& fs);
public:
	// Environment environment;
	Lexer(const char* filename);
	Lexer(const string& filename);
	Token* nextToken();
	Token* peek(); 
	void seek(Index offset);
};

#endif

