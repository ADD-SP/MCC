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
#include <unordered_set>
#include "Token.h"
#include "EndToken.h"
#include "GS.h"
#include "Number.h"
#include "Interger.h"
#include "Decimal.h"
#include "Operator.h"
#include "Type.h"
#include "Id.h"
#include "Bracket.h"
#include "Semicolon.h"

using std::fstream;
using std::vector;
using std::string;
using std::ios;
using std::unordered_set;
using std::out_of_range;

class Lexer
{
private:
	static unordered_set<string> _keywords;
	vector<Token*> _tokens;
	Index _index;
	void _iniKeyWords();
	void _handle(const string& filename);
	bool _matchOther(fstream& fs);
	bool _matchOperator(fstream& fs);
	bool _matchNumber(fstream& fs);
	bool _matchIdOrKeyWord(fstream& fs);
public:
	Lexer(const char* filename);
	Lexer(const string& filename);
	Token* nextToken();
	Token* peek();
	void seek(Index offset);
};

#endif

