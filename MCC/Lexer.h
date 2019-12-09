#ifndef _LEXER_H_
#define _LEXER_H_ 0

/*
	�����Ǵʷ�������
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
	// �洢��ȫ���Ĺؼ���
	static unordered_set<string> _keywords;
	// �洢�˻�������
	static unordered_set<string> _types;
	// �洢�Ѿ���������Token
	vector<Token*> _tokens;
	size_t _line = 1;
	Index _index;
	// ��ʼ���ؼ��ֺ����ͼ���
	void _iniKeyWordsAndTypes();
	// ����Դ�����ļ��е�Token
	void _handle(const string& filename);
	bool _matchOther(fstream& fs);
	// ƥ�������͹�ϵ�����
	bool _matchOperator(fstream& fs);
	// ƥ�������͸�����
	bool _matchNumber(fstream& fs);
	// ƥ���ʶ���͹ؼ���
	bool _matchIdOrKeyWord(fstream& fs);
public:

	Lexer(const char* filename);
	Lexer(const string& filename);

	// ��ȡ��һ��Token
	Token* nextToken();
	// ǰ��һ��Token�����������ָ����ƶ�
	Token* peek(); 
	// �޸�Tokenָ���λ��
	void seek(Index offset);
};

#endif

