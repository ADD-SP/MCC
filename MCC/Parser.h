#ifndef _PARSER_H_
#define _PARSER_H_ 0

/*
	�﷨���������﷨�����LL(1)���������Ŀ��Ŀ¼�е�syntax�ļ���
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
	// һ���ʷ�������
	Lexer& _lexer;
	// ����������
	Environment envir;
	// �����﷨��
	Ast _ast;
	// ������¼���ڲ�ѭ���Ľ�����ַ
	stack<string> _loopEndLabel;
	// ������¼���ڲ�ѭ���Ŀ�ʼ��ַ������ѭ�������жϣ�
	stack<string> _loopBoolLabel;
	// �ַ����ָ�
	vector<string> _split(const string& str,char pattern);

	// ������ַ��ת��Ϊ��Ԫ��
	void _gen(string str);

	// ����ָ����˳�����AstNode
	void _gen(AstNode* root);

	// �ж�ĳ����ʶ���Ƿ�����
	void _isDeclare(Id* id);

	// ��ʱ����
	void _pushValue(AstNode* left, AstNode* right,size_t start);

	/*
		���к�����������ʽΪ_parse + �ķ�����
		�����»��ߴ���' ' '��Ʋ������_E����E'
		�ķ����ŵ��������Ŀ��Ŀ¼�е�syntax�ļ���
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
	// �����洢���ɵ���Ԫ��
	vector<FourTuple> fourTuples;

	Parser(Lexer& lexer);
};

#endif // !_PARSER_H_



